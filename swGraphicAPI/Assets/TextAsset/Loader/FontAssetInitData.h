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
#include "swGraphicAPI/Assets/TextAsset/Loader/FontPicker.h"

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
    Image< float >                      Kerning;

    /**Padding around glyph in texture atlas. It's used to prevent texture bleeding.*/
    uint32                              Padding;

public:
    explicit FontLayout( std::map< wchar_t, Glyph > glyphs, Image< float > kerning )
        : Padding( 1 )
        , Glyphs( std::move( glyphs ) )
        , Kerning( std::move( kerning ) )
    {}

    FontLayout( FontLayout&& other ) = default;
    FontLayout& operator=( FontLayout&& other ) = default;

public:
    uint32      GetMaxHeight() const;
    uint32      GetMaxWidth() const;
    uint32      GetMaxBearingY() const;
    uint32      GetMaxHeightWithPadding() const;
    uint32      GetMaxWidthWithPadding() const;
    uint32      GetMaxHightAboveBaseline() const;  //< Allow to compute how much font sticks out above baseline.
    uint32      GetMaxHightBelowBaseline() const;  //< Allow to compute how much font sticks out below baseline.

    ImageRect   GetGlyphCoords( wchar_t character ) const;
    float       GetKerning( wchar_t first, wchar_t second ) const;

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
    FontMetadata        Metadata;

    FontLayout          Layout;

public:
    explicit FontInitData( FontLayout&& layout, FontSizeType fontSize )
        : FontAtlas( nullptr )
        , FontSize( fontSize )
        , Layout( std::move( layout ) )
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

/**@brief Load font by providing parameters which will be resolved by FontPicker.
@ingroup Text*/
struct ChooseFontLoadData : public FontLoaderData
{
    RTTR_ENABLE( FontLoaderData );
public:

    std::string FontFamily;
    FontWeight  FontWeight;
    FontStyle   FontStyle;
    bool        MatchExact;

public:
    explicit ChooseFontLoadData( const std::string& fontFamuly, FontSizeType fontSize )
        : FontLoaderData( fontSize )
        , FontFamily( fontFamuly )
        , FontWeight( FontWeight::Normal )
        , FontStyle( FontStyle::Normal )
        , MatchExact( true )
    {}

public:
    virtual std::string ResourceKey() const override;
};



}	// sw

