/**
@file FreeTypeLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Assets/TextAsset/stdafx.h"

#include "FontLoader.h"

#include "swCommonLib/Common/Buffers/ImageRegion.h"

#include "swGraphicAPI/ResourceManager/Loaders/Tools/CanLoad.h"
#include "swGraphicAPI/ResourceManager/Exceptions/LoaderException.h"
#include "swGeometrics/GeometricsCore/Math/Math.h"

#include "swGraphicAPI/Loaders/SoilTextureLoader/SoilTextureLoader.h"
#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"
#include "swGraphicAPI/Assets/TextAsset/Loader/FreeType.h"
#include <swGraphicAPI/Resources/Textures/TextureInitData.h>


namespace sw
{

// ================================ //
// 
Nullable< std::map<wchar_t, Glyph> >            BuildGlyphs( const FreeTypeLibrary& freeType, const std::wstring& charset )
{
    ErrorsCollector collector;
    std::map<wchar_t, Glyph> glyphs;

    for( Size idx = 0; idx < charset.length(); idx++ )
    {
        auto character = charset[ idx ];
        auto glyph = freeType.LoadGlyph( character );
        if( collector.Success( glyph ) )
        {
            glyphs[ character ] = glyph.Get();
            glyphs[ character ].GlyphIdx = (uint16)idx;
        }
    }

    return collector.Return( glyphs );
}

// ================================ //
// 
Nullable< Image< float > >                      BuildKerning( const FreeTypeLibrary& freeType, const std::wstring& charset )
{
    ErrorsCollector collector;
    Image< float >  kerning( (uint32)charset.length(), (uint32)charset.length() );

    for( uint32 y = 0; y < charset.length(); y++ )
    {
        for( uint32 x = 0; x < charset.length(); x++ )
        {
            auto kern = freeType.Kerning( charset[ x ], charset[ y ] );
            if( collector.Success( kern ) )
                kerning( x, y ) = kern.Get();
        }
    }

    return collector.Return( std::move( kerning ) );
}

// ================================ //

FreeTypeLoader::FreeTypeLoader( FontPicker&& picker ) : m_fontPicker( std::move( picker ) ) {}

// ================================ //
// 
bool                FreeTypeLoader::CanLoad( const AssetPath& filePath, TypeID resourceType )
{
    std::string allowedExtensions[] =
    {
        ".ttf",
        ".otf",
    };

    TypeID allowedTypes[] =
    {
        TypeID::get< FontAsset >(),
        TypeID::get< Resource >()
    };

    // Variant for ChooseFontLoadData descriptor.
    if( filePath.GetFile().IsEmpty() )
        return CanLoadType( resourceType, allowedTypes );
    else
        return DefaultCanLoad( filePath, resourceType, allowedExtensions, allowedTypes );
}

// ================================ //
// 
LoadingResult       FreeTypeLoader::Load( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI context )
{
    if( assetDesc == nullptr )
        return LoaderException::Create( "FreeTypeLoader", "Asset descriptor is null.", filePath, resourceType );

    if( assetDesc->get_type() != TypeID::get< FontLoaderData >()
        && assetDesc->get_type() != TypeID::get< ChooseFontLoadData >() )
    {
        return LoaderException::Create(
            "FreeTypeLoader", "Unsupported descriptor type [ " + assetDesc->get_type().get_name().to_string() + " ].",
            filePath, resourceType );
    }

    LoadPath fontPath = filePath;
    if( assetDesc->get_type() == TypeID::get< ChooseFontLoadData >() )
    {
        auto loadInfo = static_cast< const ChooseFontLoadData* >( assetDesc );
        auto chosen =
            m_fontPicker.ChooseFontFile( context.GetPathsManager(), loadInfo->FontFamily, loadInfo->FontWeight, loadInfo->FontStyle, loadInfo->MatchExact );
        ReturnIfInvalid( chosen );

        fontPath = chosen.Get().Path;
    }

    auto loadInfo = static_cast< const FontLoaderData* >( assetDesc );

    // Note: ResourceKey is taken from parent descriptor, because since we have exact file path, we don't need to distinguish
    // between different styles and weights. The goal of havinf internal path is to avoid duplicate loading of the same font.
    AssetPath atlasPath =
        AssetPath( fontPath.GetFileTranslated(), fmt::format( "/Atlas{}", loadInfo->FontLoaderData::ResourceKey() ) );
    AssetPath fontAssetPath = AssetPath( fontPath.GetFileTranslated(), loadInfo->FontLoaderData::ResourceKey() );

    auto cached = context.GetCachedGeneric( fontAssetPath, resourceType );
    if( cached )
        return LoadingResult( cached );

    auto freeType = FreeTypeLibrary::Create();
    ReturnIfInvalid( freeType );
    ReturnIfInvalid( freeType.Get().CreateFace( fontPath, loadInfo->FontSize ) );

    try
    {
        auto glyphs = BuildGlyphs( freeType, loadInfo->CharacterSet ).Get();
        auto kerning = BuildKerning( freeType, loadInfo->CharacterSet ).Get();

        FontLayout fontLayout( glyphs, std::move( kerning ) );
        fontLayout.Padding = 1;

        FontInitData fontDesc( std::move( fontLayout ), loadInfo->FontSize );
        fontDesc.FontAtlas = RenderAtlas( freeType, atlasPath, fontDesc.Layout, context ).Get();
        fontDesc.Metadata = FontPicker::QueryMetadata( freeType );

        auto result = context.CreateGenericAsset( fontAssetPath, loadInfo->GetAssetType(), std::move( fontDesc ) );
        return LoadingResult( result.Get() );
    }
    catch( const RuntimeException& ex )
    {
        return LoaderException::Create( "FreeTypeLoader", ex.ErrorMessage(), fontPath, resourceType );
    }
}

// ================================ //
// 
ReturnResult                FreeTypeLoader::Prefetch( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
    return ReturnResult( fmt::format( "Prefetch operation not supported" ) );
}

// ================================ //
// 
Nullable< TexturePtr >      FreeTypeLoader::RenderAtlas( const FreeTypeLibrary& freeType, const AssetPath& filePath, FontLayout& fontLayout, RMLoaderAPI factory )
{
    auto cached = factory.GetCached< Texture >( filePath );
    if( cached )
        return cached;

    auto glyphsPerRow = (u32)std::ceil( sqrt( (float)fontLayout.Glyphs.size() ) );

    uint32 padding = 1;
    auto maxWidth = fontLayout.GetMaxWidthWithPadding();
    auto maxHeight = fontLayout.GetMaxHeightWithPadding();

    auto altlasWidth = maxWidth * glyphsPerRow;
    auto altlasHeight = maxHeight * glyphsPerRow;

    altlasWidth = RoundUpToPowerOfTwo( maxWidth * glyphsPerRow );
    altlasHeight = RoundUpToPowerOfTwo( maxHeight * glyphsPerRow );

    auto image = RenderAtlasToBuffer( freeType, fontLayout, altlasWidth, altlasHeight );

    //auto file = sw::fs::Path::WorkingDirectory() / filePath.GetFile().ChangeExtension( ".png" ).GetFileName();
    //SoilTextureLoader::Save( file, image.ToRGBAImage() );

    TextureInitData texInfo( std::move( image ) );
    texInfo.MipMaps = MipMapsInfo();
    texInfo.TextureUsage = TextureUsageInfo();
    texInfo.Format = ResourceFormat::RESOURCE_FORMAT_A8_UNORM;

    return factory.CreateAsset< Texture >( filePath, std::move(texInfo));
}

// ================================ //
// 
Image< u8 >                 FreeTypeLoader::RenderAtlasToBuffer( const FreeTypeLibrary& freeType, FontLayout& fontLayout, uint32 width, uint32 height )
{
    // Some fonts contain for example emoticons, which use rgb channels.
    // In future we should handle this case.
    auto image = Image< u8 >( width, height );
    image.ZeroMemory();

    uint8* currAddress = image.GetRawData();

    auto glyphsIter = fontLayout.Glyphs.begin();
    auto maxWidth = fontLayout.GetMaxWidthWithPadding();
    auto maxHeight = fontLayout.GetMaxHeightWithPadding();

    uint32 curX = 0;
    uint32 curY = 0;

    for( auto& [wchar, glyph] : fontLayout.Glyphs )
    {
        // Adjust rectangle to keep padding around glyph.
        ImageRect rect =
        { 
            curX + fontLayout.Padding, 
            curY + fontLayout.Padding, 
            glyph.Width, 
            glyph.Height
        };
        auto region = ImageRegion< u8 >::From( image, rect ).Get();

        freeType.RenderGlyph( glyph, region );

        glyph.TextureX = rect.X;
        glyph.TextureY = rect.Y;

        curX += maxWidth;
        // No more space in current row, move to next.
        if( curX + maxWidth >= width )
        {
            curX = 0;
            curY += maxHeight;
        }
    }

    return image;
}


// ================================ //
// FreeTypeLibrary implementation


const auto FT_PrecisionMult = 6;

// ================================ //

FreeTypeLibrary::~FreeTypeLibrary()
{
    if( this->FT )
    {
        if( this->FT->Face )
        {
            FT_Done_Face( this->FT->Face );
            this->FT->Face = nullptr;
        }

        if( this->FT->Library )
        {
            FT_Done_FreeType( this->FT->Library );
            this->FT->Library = nullptr;
        }
    }
}

// ================================ //

ReturnResult            FreeTypeLibrary::CreateLibrary()
{
    auto error = FT_Init_FreeType( &this->FT->Library );
    if( error )
        return fmt::format( "Failed to initialize FreeType library. Error: {}", ftErrorString( error ) );
    return Success::True;
}

// ================================ //
// 
Nullable<FreeTypeLibrary>   FreeTypeLibrary::Create()
{
    FreeTypeLibrary freeType;
    ReturnIfInvalid( freeType.CreateLibrary() );
    return freeType;
}

// ================================ //
// 
ReturnResult                FreeTypeLibrary::CreateFace( const LoadPath& filePath, uint32 fontSize )
{
    FT_Error error = FT_New_Face( this->FT->Library, filePath.GetFile().String().c_str(), 0, &this->FT->Face);
    if( error != FT_Err_Ok )
    {
        return ReturnResult( fmt::format( "Failed to create face from font file: {}, error: {}",
            filePath.GetFile().String(), ftErrorString( error ) ) );
    }

    FT_Error error2 = FT_Set_Pixel_Sizes( this->FT->Face, (FT_UInt)fontSize, (FT_UInt)fontSize );
    if( error2 != FT_Err_Ok )
    {
        return ReturnResult( fmt::format( "Failed to set pixel size: {}, error: {}",
            filePath.GetFile().String(), ftErrorString( error2 ) ) );
    }

    return Success::True;
}

// ================================ //
// 
Nullable<Glyph>             FreeTypeLibrary::LoadGlyph( wchar_t character ) const
{
    FT_UInt gindex = FT_Get_Char_Index( this->FT->Face, character );
    
    auto result = FT_Load_Glyph( this->FT->Face, gindex, FT_LOAD_NO_BITMAP );
    if( result != FT_Err_Ok )
        return std::make_shared< RuntimeException> ( fmt::format("Error loading glyph for character '{}': {}",
            Convert::ToString( character ), ftErrorString( result ) ) );

    auto newGlyph = Glyph();

    newGlyph.CharCode = character;
    newGlyph.FtIdx = gindex;
    newGlyph.GlyphIdx = 0;
    newGlyph.Height = this->FT->Face->glyph->metrics.height >> FT_PrecisionMult;
    newGlyph.Width = this->FT->Face->glyph->metrics.width >> FT_PrecisionMult;

    newGlyph.BearingX = this->FT->Face->glyph->metrics.horiBearingX >> FT_PrecisionMult;
    newGlyph.BearingY = this->FT->Face->glyph->metrics.horiBearingY >> FT_PrecisionMult;
    newGlyph.AdvanceX = this->FT->Face->glyph->advance.x >> FT_PrecisionMult;
    newGlyph.AdvanceY = this->FT->Face->glyph->advance.y >> FT_PrecisionMult;

    return Nullable<Glyph>( newGlyph );
}

// ================================ //
// 
Nullable<float>             FreeTypeLibrary::Kerning( wchar_t first, wchar_t second ) const
{
    FT_Vector kerning;

    auto leftGlyphIdx = FT_Get_Char_Index( this->FT->Face, first );
    auto rightGlyphIdx = FT_Get_Char_Index( this->FT->Face, second );

    auto result = FT_Get_Kerning( this->FT->Face,
        leftGlyphIdx,
        rightGlyphIdx,
        FT_KERNING_DEFAULT,
        &kerning );

    if( result != FT_Err_Ok )
        return std::make_shared< RuntimeException> ( fmt::format( "Error loading kerning for '{}' and '{}': {}",
            Convert::ToString( first ),
            Convert::ToString( second ),
            ftErrorString( result ) ) );

    return Nullable<float>( float( kerning.x >> FT_PrecisionMult ) );
}

// ================================ //
// 
void                        FreeTypeLibrary::RenderGlyph( const Glyph& glyph, ImageRegion< u8 >& image ) const
{
    FT_Load_Glyph( this->FT->Face, glyph.FtIdx, FT_LOAD_RENDER );

    FT_Bitmap* bitmap = &this->FT->Face->glyph->bitmap;
    
    for( uint32 y = 0; y < image.GetHeight(); y++ )
    {
        for( uint32 x = 0; x < image.GetWidth(); x++ )
        {
            auto pixel = bitmap->buffer[ y * bitmap->width + x ];
            image( x, y ) = (u8)pixel;
        }
    }
}

// ================================ //

FTFontMetadata              FreeTypeLibrary::Metadata() const
{
    return FTFontMetadata {
        this->FT->Face->family_name, this->FT->Face->style_name,
        bool( this->FT->Face->style_flags & FT_STYLE_FLAG_ITALIC ),
        bool( this->FT->Face->style_flags & FT_STYLE_FLAG_BOLD )
    };
}

}

