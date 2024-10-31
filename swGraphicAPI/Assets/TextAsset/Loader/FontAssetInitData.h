#pragma once
/**
@file FontAssetInitData.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"

#include "swGraphicAPI/Assets/TextAsset/Glyph.h"

namespace sw
{

class FontAsset;
class ResourceManager;

typedef std::pair< wchar_t, wchar_t > KerningPair;


/**@brief Struct contains describing individual characters in font.
@ingroup Text*/
struct FontLayout
{
    /**Stores information how to render and layout each character*/
    std::map< wchar_t, Glyph >			Glyphs;

    /**Each character pair can be shifted individually to give text better look in terms of spacing. */
    std::map< KerningPair, float >		Kerning;

public:
    uint32      GetMaxHeight() const;
    uint32      GetMaxWidth() const;
};


/**@brief Struct contains data needed to initialize font.
@ingroup Text*/
struct FontInitData : public IAssetCreateInfo
{
    RTTR_ENABLE( IAssetCreateInfo );
public:

    TexturePtr          FontAtlas;
    uint32              FontSize;

    FontLayout          Layout;

public:
    explicit FontInitData	( uint32 fontSize )
        : FontAtlas( nullptr )
        , FontSize( fontSize )
    {}

public:
    /**Returns type of asset that can be created using this structure.*/
    virtual TypeID		GetAssetType	    () const override;
};



/**@brief Struct describing font to load.
@ingroup Text*/
struct FontLoaderData : public IAssetLoadInfo
{
    RTTR_ENABLE( IAssetLoadInfo );
public:

    /**Characters that will be rendered to texture atlas.*/
    std::wstring        CharacterSet;
    uint32              FontSize;
    bool                GenerateMipmaps;

public:
	explicit FontLoaderData	( uint32 fontSize )
        : FontSize( fontSize )
        , GenerateMipmaps( false )
        , CharacterSet( DefaultCharacterSet() )
    {}

public:

    static std::wstring DefaultCharacterSet ();

public:
    /**Returns type of asset that can be created using this structure.*/
    virtual TypeID		GetAssetType	    () const override;
};




}	// sw

