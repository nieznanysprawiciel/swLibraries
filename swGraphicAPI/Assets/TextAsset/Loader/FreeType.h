#pragma once
/**
@file FreeType.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


static const char* ftErrorString( FT_Error error )
{
#undef FTERRORS_H_
#define FT_ERRORDEF(error_code, value, string) case error_code: return string;
#define FT_ERROR_START_LIST switch(error) {
#define FT_ERROR_END_LIST default: return "Unknown error"; }
#include FT_ERRORS_H
}

#include <ft2build.h>
#include FT_FREETYPE_H


#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/Buffers/ImageRegion.h"
#include "swGeometrics/GeometricsCore/Math/Types.h"
#include "swGraphicAPI/Assets/TextAsset/Loader/FontPicker.h"


namespace sw
{

/**@brief Structure storing Font metadata.
@ingroup Text*/
struct FTFontMetadata
{
    std::string Family;
    std::string StyleName;  //< String name of the style retrieved from font metadata.

    /**@brief Indicates that Font is italic. Note that StyleName can contain more details about style.*/
    bool IsItalic;
    /**@brief Indicates that Font is bold. Note that StyleName can contain more details about different
    styles of bold. Those 3 fields should be mapped to @ref FontWeight and @ref FontStyle enums.*/
    bool IsBold;
};


/**FT_Library object is not multithreaded, so the new one must be created for each new
loading operation. This class serves as RAII guard to free resources after loading is done.*/
class FreeTypeLibrary
{
public:
    FT_Library  Library;
    FT_Face     Face;

public:
    explicit		FreeTypeLibrary	( FT_Library library ) : Library( library ), Face( nullptr ) {}
                    ~FreeTypeLibrary() = default;
public:
    static Nullable<FreeTypeLibrary>   Create();

public:
    ReturnResult        CreateFace		( const LoadPath& filePath, uint32 fontSize );

    Nullable< Glyph >   LoadGlyph		( wchar_t character ) const;
    Nullable< float >   Kerning         ( wchar_t first, wchar_t second ) const;

    /**Renders Glyph to bitmap in selected rectangle.*/
    void                RenderGlyph		( const Glyph& glyph, ImageRegion< u32 >& image ) const;

    FTFontMetadata      Metadata() const;
};


}
