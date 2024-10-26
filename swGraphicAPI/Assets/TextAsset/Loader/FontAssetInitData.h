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

/**@brief Struct contains data needed to initialize font.
@ingroup Text*/
struct FontInitData : public IAssetCreateInfo
{
    RTTR_ENABLE( IAssetCreateInfo );
public:

    TexturePtr											FontAtlas;
    uint32												FontSize;

    /**Stores information how to render and layout each character*/
    std::map< wchar_t, Glyph >							Glyphs;

    /**Each character pair can be shifted indiidually to give text better look in terms of spacing. */
    std::map< std::pair< wchar_t, wchar_t >, float >	Kerning;

public:
    explicit FontInitData	() {}

public:
    /**Returns type of asset that can be created using this structure.*/
    virtual TypeID		GetAssetType	    () const override { return TypeID::get< FontAsset >(); }
};



/**@brief Struct describing font to load.
@ingroup Text*/
struct FontLoaderData : public IAssetLoadInfo
{
    RTTR_ENABLE( IAssetLoadInfo );
public:

    AssetPath           FontPath;
    /**Characters that will be rendered to texture atlas.*/
    std::wstring        CharacterSet;
    uint32              FontSize;
    bool                GenerateMipmaps;

public:
	explicit FontLoaderData	() {}

public:


public:
    /**Returns type of asset that can be created using this structure.*/
    virtual TypeID		GetAssetType	    () const override { return TypeID::get< FontAsset >(); }
};




}	// sw

