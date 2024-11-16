/**
@file FontPicker.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/Assets/TextAsset/stdafx.h"

#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/System/Dir.h"
#include "swGraphicAPI/Assets/TextAsset/Loader/FreeType.h"

#include "FontPicker.h"

#include <sstream>


RTTR_REGISTRATION
{
    rttr::registration::enumeration< sw::FontWeight >( "sw::FontWeight" )(
        rttr::value( "Bold", sw::FontWeight::Bold ),
        rttr::value( "DemiBold", sw::FontWeight::DemiBold ),
        rttr::value( "SemiBold", sw::FontWeight::SemiBold ),
        rttr::value( "Light", sw::FontWeight::Light ),
        rttr::value( "Medium", sw::FontWeight::Medium ),
        rttr::value( "Normal", sw::FontWeight::Normal ),
        rttr::value( "Regular", sw::FontWeight::Regular ),
        rttr::value( "Thin", sw::FontWeight::Thin ),
        rttr::value( "Black", sw::FontWeight::Black ),
        rttr::value( "Heavy", sw::FontWeight::Heavy ),
        rttr::value( "ExtraBlack", sw::FontWeight::ExtraBlack ),
        rttr::value( "UltraBlack", sw::FontWeight::UltraBlack ),
        rttr::value( "ExtraBold", sw::FontWeight::ExtraBold ),
        rttr::value( "UltraBold", sw::FontWeight::UltraBold ),
        rttr::value( "ExtraLight", sw::FontWeight::ExtraLight ),
        rttr::value( "UltraLight", sw::FontWeight::UltraLight ) );

    rttr::registration::enumeration< sw::FontStyle >( "sw::FontStyle" )(
        rttr::value( "Normal", sw::FontStyle::Normal ),
        rttr::value( "Oblique", sw::FontStyle::Oblique ),
        rttr::value( "Italic", sw::FontStyle::Italic ) );
}

namespace sw
{
// ================================ //

void                            FontPicker::RegisterSearchPath( const fs::Path& path )
{
    m_searchPaths.push_back( path );
}

// ================================ //

Nullable< FontSearchEntry >     FontPicker::FindFontFile( PathsManager* pm, const std::string& fontFamily,
                                                          FontWeight weight, FontStyle style ) const
{
    auto varaints = ListFontVariants( pm, fontFamily );
    ReturnIfInvalid( varaints );

    for( auto& variant : varaints.Get() )
    {
        if( variant.Weight == weight && variant.Style == style )
            return variant;
    }

    return fmt::format( "Non of {} {} variants matches the chosen one.", varaints.Get().size(), fontFamily );
}

// ================================ //

Nullable< std::vector< FontSearchEntry > >  FontPicker::ListFonts( PathsManager* pm ) const
{
    std::vector< FontSearchEntry > entries;

    for( auto path : m_searchPaths )
    {
        auto dir = pm->Translate( path );
        auto files = fs::Dir::ListFiles( dir );
        for( auto& file : files )
        {
            auto meta = FontMetadata( pm, file );
            if( meta.IsValid() )
                entries.push_back( meta.Get() );
        }
    }

    return entries;
}

// ================================ //

Nullable< std::vector< FontSearchEntry > >  FontPicker::ListFontVariants( PathsManager* pm, const std::string& fontFamily ) const
{
    auto allFonts = ListFonts( pm );
    ReturnIfInvalid( allFonts );

    std::vector< FontSearchEntry > variants;
    for( auto& font : allFonts.Get() )
    {
        if( font.Metadata.Family == fontFamily )
            variants.push_back( font );
    }

    return variants;
}

// ================================ //

Nullable< FontSearchEntry >                 FontPicker::FontMetadata( PathsManager* pm, const fs::Path& path ) const
{
    auto freeType = FreeTypeLibrary::Create();
    ReturnIfInvalid( freeType );

    auto loadPath = LoadPath( AssetPath( path, "" ), pm );
    ReturnIfInvalid( freeType.Get().CreateFace( loadPath, 3 ) );

    auto meta = freeType.Get().Metadata();
    auto style = ParseFontStyle( meta.StyleName );
    auto weight = ParseFontWeight( meta.StyleName );

    return FontSearchEntry
    { 
        meta,
        weight.IsValid() ? weight.Get() : FontWeight::Normal,
        style.IsValid() ? style.Get() : FontStyle::Normal,
        loadPath
    };
}

// ================================ //
template< typename EnumType >
Nullable< EnumType >            ExtractEnum( const std::string& styleName )
{
    auto enumType = TypeID::get< EnumType >().get_enumeration();
    if( !enumType.is_valid() )
        return fmt::format( "Enum {} is not registered.", TypeID::get< EnumType >().get_name().to_string() );

    std::vector< EnumType > candidates;
    for( auto variant : enumType.get_names() )
    {
        auto name = variant.to_string();
        if( styleName.find( name ) != std::string::npos )
            candidates.push_back( enumType.name_to_value( name ).get_value< EnumType >() );
    }

    if( candidates.empty() )
        return fmt::format( "No matching enum value for {}.", styleName );

    return candidates[ 0 ];
}

// ================================ //

Nullable< FontWeight >              FontPicker::ParseFontWeight( const std::string& styleName )
{
    return ExtractEnum< FontWeight >( styleName );
}

// ================================ //

Nullable< FontStyle >               FontPicker::ParseFontStyle( const std::string& styleName )
{
    return ExtractEnum< FontStyle >( styleName );
}

}  // sw
