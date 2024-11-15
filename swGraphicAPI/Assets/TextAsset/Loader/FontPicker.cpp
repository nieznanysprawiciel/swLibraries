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


RTTR_REGISTRATION
{
    rttr::registration::enumeration< sw::FontWeight >( "sw::FontWeight" )(
        rttr::value( "Light", sw::FontWeight::Light ),
        rttr::value( "Normal", sw::FontWeight::Normal ),
        rttr::value( "UltraBold", sw::FontWeight::UltraBold ) );

    rttr::registration::enumeration< sw::FontStyle >( "sw::FontStyle" )(
        rttr::value( "Normal", sw::FontStyle::Normal ),
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
    return Nullable< FontSearchEntry >();
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
    return Nullable< std::vector< FontSearchEntry > >();
}

// ================================ //

Nullable< FontSearchEntry >                 FontPicker::FontMetadata( PathsManager* pm, const fs::Path& path ) const
{
    auto freeType = FreeTypeLibrary::Create();
    ReturnIfInvalid( freeType );

    auto loadPath = LoadPath( AssetPath( path, "" ), pm );
    ReturnIfInvalid( freeType.Get().CreateFace( loadPath, 3 ) );

    auto meta = freeType.Get().Metadata();
    return FontSearchEntry
    { 
        meta,
        meta.IsBold ? FontWeight::UltraBold : FontWeight::Normal,
        meta.IsItalic ? FontStyle::Italic : FontStyle::Normal,
        loadPath
    };
}

}  // sw
