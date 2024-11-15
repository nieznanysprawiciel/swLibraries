#pragma once
/**
@file FontPicker.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"

#include "swGraphicAPI/ResourceManager/PathTranslators/PathsManager.h"

#include <vector>


namespace sw
{

/**@brief Font style.
@ingroup Text*/
enum class FontStyle : u8
{
    Normal,
    Italic,
    // Oblique
};

/**@brief Font thickness.
@ingroup Text*/
enum class FontWeight : u8
{
    Light,
    Normal,
    UltraBold,
};

/**@brief Structure storing Font metadata.
@ingroup Text*/
struct FontMetadata
{
    std::string Family;
    std::string StyleName;  //< String name of the style retrieved from font metadata.

    /**@brief Indicates that Font is italic. Note that StyleName can contain more details about style.*/
    bool        IsItalic;
    /**@brief Indicates that Font is bold. Note that StyleName can contain more details about different
    styles of bold. Those 3 fields should be mapped to @ref FontWeight and @ref FontStyle enums.*/
    bool        IsBold;
};

/**@brief Data structure returned by @ref FontPicker.
@ingroup Text*/
struct FontSearchEntry
{
    FontMetadata Metadata;

    FontWeight  Weight;
    FontStyle   Style;

    LoadPath    Path;
};


/**@brief Finds @ref Font file that fits best to given parameters.

There are 2 reasons for existance of this class:
1) We want to be able to search Fonts in different directories, in system directories among others.
In most cases we don't know path of the file, we know only font family, weight and style.
2) There is non trivial mapping between font family, weight and style to file path. File name can't be
derived from those parameters. We have to search through directories and check file metadata to match
desired font.

@ingroup Text*/
class FontPicker
{
private:

    std::vector< fs::Path >     m_searchPaths;

protected:
public:
    explicit FontPicker() = default;
    ~FontPicker() = default;

    void        RegisterSearchPath( const fs::Path& path );

public:
    Nullable< FontSearchEntry >                 FindFontFile( PathsManager* pm, const std::string& fontFamily, FontWeight weight, FontStyle style ) const;
    Nullable< std::vector< FontSearchEntry > >  ListFonts( PathsManager* pm ) const;
    Nullable< std::vector< FontSearchEntry > >  ListFontVariants( PathsManager* pm, const std::string& fontFamily ) const;
    Nullable< FontSearchEntry >                 FontMetadata( PathsManager* pm, const fs::Path& path ) const;
};



}	// sw
