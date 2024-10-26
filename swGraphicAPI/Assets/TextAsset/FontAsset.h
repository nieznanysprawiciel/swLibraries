#pragma once
/**
@file FontAsset.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

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

    TexturePtr											m_fontAtlas;
	
	uint32												m_fontSize;

	/**Stores information how to render and layout each character*/
	std::map< wchar_t, Glyph >							m_glyphs;

	/**Each character pair can be shifted indiidually to give text better look in terms of spacing. */
	std::map< std::pair< wchar_t, wchar_t >, float >	m_kerning;


public:
	explicit			FontAsset		( AssetPath filePath, FontInitData&& initData );

    std::string			FontName		() const { return GetAssetPath().GetFile().GetFileName(); }
    uint32              FontSize		() const { return m_fontSize; }

private:
	~FontAsset();
};

DEFINE_RESOURCE_PTR_TYPE( FontAsset );

}	// sw