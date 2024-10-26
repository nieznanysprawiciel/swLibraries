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

FontAsset::~FontAsset()
{}

}    // sw


