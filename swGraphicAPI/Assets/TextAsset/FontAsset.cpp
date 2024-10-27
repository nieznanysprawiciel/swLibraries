/**
@file FontAsset.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/Assets/TextAsset/stdafx.h"

#include "FontAsset.h"



namespace sw
{

FontAsset::FontAsset( AssetPath filePath, FontInitData&& initData )
    : Resource( filePath )
    , m_fontSize( initData.FontSize )
    , m_fontAtlas( initData.FontAtlas )
    , m_glyphs( std::move( initData.Glyphs ) )
    , m_kerning( std::move( initData.Kerning ) )
{}

const Glyph&        FontAsset::GetGlyph( wchar_t character ) const
{
    return this->m_glyphs.at( character );
}

float               FontAsset::GetKerning( wchar_t first, wchar_t second ) const
{
    return this->m_kerning.at( std::make_pair( first, second ) );
}

const std::map<wchar_t, Glyph>&         FontAsset::GetGlyphs() const
{
    return this->m_glyphs;
}

const std::map<KerningPair, float>&     FontAsset::GetKerning() const
{
    return this->m_kerning;
}

}    // sw


