#pragma once
/**
@file FontPicker.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"

#include "swGraphicAPI/ResourceManager/PathTranslators/PathsManager.h"

#include <vector>
#include <ostream>


namespace sw
{

/**@brief Font style.
Not all types are supported by all fonts.

@ref FontStyle::Condensed is additional variant that is not present in WPF.
@ingroup Text*/
enum class FontStyle : u8
{
    Normal = 0,
    Italic = 3,
    Oblique = 1,
    Condensed = 2,
};

/**@brief Font thickness.
Not all types are supported by all fonts.
Compatible with WPF types.
@ingroup Text*/
enum class FontWeight : u8
{
    // u8 representation reflects order of precendens when chosing which weight to use.
    Thin = 1,

    Light = 2,

    // ExtraLight and UltraLight are eqivalent.
    ExtraLight = 3,
    UltraLight = 4,

    // Normal and Regular are eqivalent.
    Normal = 5,
    Regular = 6,

    Medium = 7,

    Bold = 8,

    // DemiBold and SemiBold are eqivalent.
    DemiBold = 9,
    SemiBold = 10,

    // Black and Heavy are eqivalent.
    Black = 11,
    Heavy = 12,

    // ExtraBlack and UltraBlack are eqivalent.
    ExtraBlack = 13,
    UltraBlack = 14,

    // ExtraBold and UltraBold are eqivalent.
    ExtraBold = 15,
    UltraBold = 16
};

/**@brief Structure storing Font metadata.

Weight and Style are extracted from StyleName, which can contain more details about style
than enums can represent. The closest match is chosen.
@ingroup Text*/
struct FontMetadata
{
    std::string Family;
    std::string StyleName;  //< String name of the style retrieved from font metadata.

    FontWeight  Weight;
    FontStyle   Style;
};

/**@brief Data structure returned by @ref FontPicker.
@ingroup Text*/
struct FontSearchEntry
{
    FontMetadata    Metadata;
    LoadPath        Path;
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

public:
    static Nullable< FontWeight >          ParseFontWeight( const std::string& styleName );
    static Nullable< FontStyle >           ParseFontStyle( const std::string& styleName );
};


// Formatting for Catch display
inline std::ostream& operator<<( std::ostream& stream, const FontStyle& value )
{
    stream << Convert::ToString( value );
    return stream;
}

inline std::ostream& operator<<( std::ostream& stream, const FontWeight& value )
{
    stream << Convert::ToString( value );
    return stream;
}

/**@brief Sorting helps determine which version should be chosen if there are multiple candidates.*/
inline bool operator>( const FontWeight& left, const FontWeight& right )
{
    return static_cast< u8 >( left ) > static_cast< u8 >( right );
}

/**@brief Sorting helps determine which version should be chosen if there are multiple candidates.*/
inline bool operator>( const FontStyle& left, const FontStyle& right )
{
    return static_cast< u8 >( left ) > static_cast< u8 >( right );
}

}	// sw

DEFINE_FMT_FORMATTER_ENUM( sw::FontWeight );
DEFINE_FMT_FORMATTER_ENUM( sw::FontStyle );

