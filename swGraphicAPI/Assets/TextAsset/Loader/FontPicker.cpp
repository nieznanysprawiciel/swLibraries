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

    rttr::registration::class_< sw::FontMetadata >( "sw::FontMetadata" )
        .property( "Family", &sw::FontMetadata::Family )
        .property( "StyleName", &sw::FontMetadata::StyleName )
        .property( "Style", &sw::FontMetadata::Style )
        .property( "Weight", &sw::FontMetadata::Weight );
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
        if( variant.Metadata.Weight == weight && variant.Metadata.Style == style )
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
            auto meta = GetFontMetadata( pm, file );
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

Nullable< FontSearchEntry >                 FontPicker::GetFontMetadata( PathsManager* pm, const fs::Path& path ) const
{
    auto freeType = FreeTypeLibrary::Create();
    ReturnIfInvalid( freeType );

    auto loadPath = LoadPath( AssetPath( path, "" ), pm );
    ReturnIfInvalid( freeType.Get().CreateFace( loadPath, 3 ) );

    auto meta = QueryMetadata( freeType.Get() );

    return FontSearchEntry
    { 
        meta,
        loadPath
    };
}

// ================================ //

FontMetadata                            FontPicker::QueryMetadata( FreeTypeLibrary& freeType )
{
    auto ftMeta = freeType.Metadata();

    auto style = ParseFontStyle( ftMeta.StyleName );
    auto weight = ParseFontWeight( ftMeta.StyleName );

    auto meta = ::sw::FontMetadata();
    meta.Family = std::move( ftMeta.Family );
    meta.StyleName = std::move( ftMeta.StyleName );
    meta.Weight = weight.IsValid() ? weight.Get() : ftMeta.IsBold ? FontWeight::Bold : FontWeight::Normal;
    meta.Style = style.IsValid() ? style.Get() : ftMeta.IsItalic ? FontStyle::Italic : FontStyle::Normal;

    return meta;
}

// ================================ //

template< typename EnumType >
Nullable< std::vector< EnumType > >     ExtractEnum( const std::string& styleName )
{
    std::string style = styleName;
    for( auto& c : style )
        c = std::tolower( c );

    auto enumType = TypeID::get< EnumType >().get_enumeration();
    if( !enumType.is_valid() )
        return fmt::format( "Enum {} is not registered.", TypeID::get< EnumType >().get_name().to_string() );

    std::vector< EnumType > candidates;
    for( auto variant : enumType.get_names() )
    {
        auto name = variant.to_string();
        for( auto& c : name )
            c = std::tolower( c );

        if( style.find( name ) != std::string::npos )
            candidates.push_back( enumType.name_to_value( variant ).get_value< EnumType >() );
    }

    return candidates;
}

// ================================ //

Nullable< FontWeight >              FontPicker::ParseFontWeight( const std::string& styleName )
{
    auto candidates = ExtractEnum< FontWeight >( styleName );
    ReturnIfInvalid( candidates );

    switch( candidates.Get().size() )
    {
        case 0:
            return FontWeight::Normal;
        case 1:
            return candidates.Get().front();
        default:
            std::sort( candidates.Get().begin(), candidates.Get().end() );
            return candidates.Get().back();
    }
}

// ================================ //

Nullable< FontStyle >               FontPicker::ParseFontStyle( const std::string& styleName )
{
    auto candidates = ExtractEnum< FontStyle >( styleName );
    ReturnIfInvalid( candidates );

    switch( candidates.Get().size() )
    {
        case 0:
            return FontStyle::Normal;
        case 1:
            return candidates.Get().front();
        default:
            std::sort( candidates.Get().begin(), candidates.Get().end() );
            return candidates.Get().back();
    }
}

}  // sw
