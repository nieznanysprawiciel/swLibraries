/**
@file FontAsset.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/Assets/TextAsset/stdafx.h"

#include "FontAsset.h"



RTTR_REGISTRATION
{
    rttr::registration::class_< sw::FontAsset >( "sw::FontAsset" )
        .property( "FontSize", &sw::FontAsset::m_fontSize )
        .property( "Metadata", &sw::FontAsset::m_metadata ) BIND_AS_REF;
}

namespace sw
{

// ================================ //

FontAsset::FontAsset( AssetPath filePath, FontInitData&& initData )
    : Resource( filePath )
    , m_fontSize( initData.FontSize )
    , m_fontAtlas( initData.FontAtlas )
    , m_layout( std::move( initData.Layout) )
    , m_metadata( initData.Metadata )
{}

// ================================ //

const Glyph&        FontAsset::GetGlyph( wchar_t character ) const
{
    return this->m_layout.Glyphs.at( character );
}

// ================================ //

float               FontAsset::GetKerning( wchar_t first, wchar_t second ) const
{
    return this->m_layout.GetKerning( first, second );
}

}    // sw


