/**
@file FreeTypeLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Assets/TextAsset/stdafx.h"

#include "FontLoader.h"

#include <swGraphicAPI/ResourceManager/Loaders/Tools/CanLoad.h>
#include "swGraphicAPI/ResourceManager/Exceptions/LoaderException.h"

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"
#include "swGraphicAPI/Assets/TextAsset/Loader/FreeType.h"


namespace sw
{

// ================================ //
// 
Nullable< std::map<wchar_t, Glyph> >            BuildGlyphs( const FreeTypeLibrary& freeType, const std::wstring& charset )
{
    ErrorsCollector collector;
    std::map<wchar_t, Glyph> glyphs;

    for( auto character : charset )
    {
        auto glyph = freeType.LoadGlyph( character );
        if( collector.Success( glyph ) )
            glyphs[ character ] = glyph.Get();
    }

    return collector.Return( glyphs );
}

// ================================ //
// 
Nullable< std::map<KerningPair, float> >        BuildKerning( const FreeTypeLibrary& freeType, const std::wstring& charset )
{
    ErrorsCollector collector;
    std::map<KerningPair, float> kerning;

    for( auto first : charset )
    {
        for( auto second : charset )
        {
            auto kern = freeType.Kerning( first, second );
            if( collector.Success( kern ) )
                kerning[ std::make_pair( first, second ) ] = kern.Get();
        }
    }

    return collector.Return( kerning );
}


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

    return DefaultCanLoad( filePath, resourceType, allowedExtensions, allowedTypes );
}

// ================================ //
// 
LoadingResult       FreeTypeLoader::Load( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI context )
{
    if( assetDesc == nullptr )
        return LoaderException::Create( "FreeTypeLoader", "Asset descriptor is null.", filePath, resourceType );

    if( assetDesc->get_type() != TypeID::get< FontLoaderData >() )
        return LoaderException::Create( "FreeTypeLoader", "Unsupported descriptor type [ " + assetDesc->get_type().get_name().to_string() + " ].", filePath, resourceType );

    auto loadInfo = static_cast< const FontLoaderData* >( assetDesc );

    auto freeType = FreeTypeLibrary::Create();
    ReturnIfInvalid( freeType );
    ReturnIfInvalid( freeType.Get().CreateFace( filePath, loadInfo->FontSize ) );

    FontInitData fontDesc( loadInfo->FontSize );

    fontDesc.Glyphs = BuildGlyphs( freeType.Get(), loadInfo->CharacterSet ).Get();
    fontDesc.Kerning = BuildKerning( freeType.Get(), loadInfo->CharacterSet ).Get();

    auto result = context.CreateGenericAsset( filePath.GetOriginalPath(), loadInfo->GetAssetType(), std::move( fontDesc ) );
    if( result.IsValid() )
        return LoadingResult( result.Get() );
    else
        return LoadingResult( result.GetError() );
}

// ================================ //
// 
ReturnResult        FreeTypeLoader::Prefetch( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
    return ReturnResult( fmt::format( "Prefetch operation not supported" ) );
}

// ================================ //
// FreeTypeLibrary implementation


const auto FT_PrecisionMult = 6;

// ================================ //
// 
Nullable<FreeTypeLibrary>   FreeTypeLibrary::Create()
{
    FT_Library library;
    auto error = FT_Init_FreeType( &library );
    if( error )
        return Nullable< FreeTypeLibrary >::FromError( fmt::format( "Failed to initialize FreeType library." ) );
    return FreeTypeLibrary( library );
}

// ================================ //
// 
ReturnResult                FreeTypeLibrary::CreateFace( const LoadPath& filePath, uint32 fontSize )
{
    FT_Error error = FT_New_Face( this->Library, filePath.GetFile().String().c_str(), 0, &this->Face);
    if( error != FT_Err_Ok )
    {
        return ReturnResult( fmt::format( "Failed to create face from font file: {}, error: {}",
            filePath.GetFile().String(), ftErrorString( error ) ) );
    }

    FT_Error error2 = FT_Set_Pixel_Sizes( this->Face, (FT_UInt)fontSize, (FT_UInt)fontSize );
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
    FT_UInt gindex = FT_Get_Char_Index( this->Face, character );
    
    auto result = FT_Load_Glyph( this->Face, gindex, FT_LOAD_NO_BITMAP );
    if( result != FT_Err_Ok )
        return std::make_shared< RuntimeException> ( fmt::format("Error loading glyph for character '{}': {}",
            Convert::ToString( character ), ftErrorString( result ) ) );

    auto newGlyph = Glyph();

    newGlyph.CharCode = character;
    newGlyph.GlyphIdx = gindex;
    newGlyph.Width = this->Face->glyph->metrics.height;
    newGlyph.Height = this->Face->glyph->metrics.width;

    newGlyph.BearingX = this->Face->glyph->metrics.horiBearingX >> FT_PrecisionMult;
    newGlyph.BearingY = this->Face->glyph->metrics.horiBearingY >> FT_PrecisionMult;
    newGlyph.AdvanceX = this->Face->glyph->advance.x >> FT_PrecisionMult;
    newGlyph.AdvanceY = this->Face->glyph->advance.y >> FT_PrecisionMult;

    return Nullable<Glyph>( newGlyph );
}

// ================================ //
// 
Nullable<float>             FreeTypeLibrary::Kerning( wchar_t first, wchar_t second ) const
{
    FT_Vector kerning;

    auto leftGlyphIdx = FT_Get_Char_Index( this->Face, first );
    auto rightGlyphIdx = FT_Get_Char_Index( this->Face, second );

    auto result = FT_Get_Kerning( this->Face,
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

}
