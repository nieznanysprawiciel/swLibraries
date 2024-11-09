#pragma once
/**
@file FontAssetInitData.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <optional>

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Buffers/ImageRegion.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"

#include "swGraphicAPI/Assets/TextAsset/Loader/Glyph.h"

namespace sw
{

class FontAsset;
class ResourceManager;

typedef std::pair< wchar_t, wchar_t > KerningPair;
typedef uint8                         FontSizeType;

/**@brief Struct contains describing individual characters in font.
@ingroup Text*/
struct FontLayout
{
    /**Stores information how to render and layout each character*/
    std::map< wchar_t, Glyph >			Glyphs;

    /**Each character pair can be shifted individually to give text better look in terms of spacing. */
    std::map< KerningPair, float >		Kerning;

    /**Padding around glyph in texture atlas. It's used to prevent texture bleeding.*/
    uint32                              Padding;

public:
    explicit FontLayout()
        : Padding( 1 )
    {}

public:
    uint32      GetMaxHeight() const;
    uint32      GetMaxWidth() const;
    uint32      GetMaxHeightWithPadding() const;
    uint32      GetMaxWidthWithPadding() const;

    ImageRect   GetGlyphCoords( wchar_t character ) const;

    float       SpaceWidth() const;
    float       NewLineSize() const;
};


/**@brief Struct contains data needed to initialize font.
@ingroup Text*/
struct FontInitData : public IAssetCreateInfo
{
    RTTR_ENABLE( IAssetCreateInfo );
public:

    TexturePtr          FontAtlas;
    FontSizeType        FontSize;

    FontLayout          Layout;

public:
    explicit FontInitData( FontSizeType fontSize )
        : FontAtlas( nullptr )
        , FontSize( fontSize )
    {}

public:
    /**Returns type of asset that can be created using this structure.*/
    virtual TypeID		    GetAssetType	    () const override;
    virtual std::string		ResourceKey		    () const override;
};



/**@brief Struct describing font to load.
@ingroup Text*/
struct FontLoaderData : public IAssetLoadInfo
{
    RTTR_ENABLE( IAssetLoadInfo );
public:

    /**Characters that will be rendered to texture atlas.*/
    std::wstring        CharacterSet;
    FontSizeType        FontSize;
    bool                GenerateMipmaps;

public:
    explicit FontLoaderData( FontSizeType fontSize )
        : FontSize( fontSize )
        , GenerateMipmaps( false )
        , CharacterSet( DefaultCharacterSet() )
    {}

public:

    static std::wstring DefaultCharacterSet ();

public:
    /**Returns type of asset that can be created using this structure.*/
    virtual TypeID		    GetAssetType	    () const override;
    virtual std::string		ResourceKey		    () const override;

};




}	// sw

