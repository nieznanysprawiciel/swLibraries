#pragma once
/**
@file FontAsset.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/RTTR.h"
#include "swGraphicAPI/Resources/Textures/Texture.h"

#include "swGraphicAPI/Assets/TextAsset/Loader/FontAssetInitData.h"
#include "swGraphicAPI/Assets/TextAsset/Glyph.h"


namespace sw
{

/**@defgroup Text Text

@brief Classes describing text and fonts.

@ingroup Assets
*/



/**@brief Class describes Font.

@ingroup Assets
@ingroup Text
*/
class FontAsset : public Resource
{
	RTTR_ENABLE( Resource );
    RTTR_REGISTRATION_FRIEND;
protected:

    TexturePtr			m_fontAtlas;
	uint32				m_fontSize;

    FontLayout          m_layout;


public:
	explicit			FontAsset		( AssetPath filePath, FontInitData&& initData );

    std::string			FontName		() const { return GetAssetPath().GetFile().GetFileName(); }
    uint32              FontSize		() const { return m_fontSize; }

    const Glyph&		GetGlyph		( wchar_t character ) const;
    float				GetKerning		( wchar_t first, wchar_t second ) const;

	const std::map< wchar_t, Glyph >&		GetGlyphs	() const;
    const std::map< KerningPair, float >&	GetKerning	() const;

    const TexturePtr&						GetFontAtlas() const { return m_fontAtlas; }
private:
	~FontAsset() = default;
};

DEFINE_RESOURCE_PTR_TYPE( FontAsset );

}	// sw
