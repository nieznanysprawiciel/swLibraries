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
#include "swGeometrics/GeometricsCore/Types/Math/Types.h"

namespace sw
{

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
};


}
