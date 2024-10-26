#pragma once
/**
@file FreeType.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#undef FTERRORS_H_
#define FT_ERROR_START_LIST     switch ( error_code ) {
#define FT_ERRORDEF( e, v, s )    case v: return s;
#define FT_ERROR_END_LIST       }


#include <ft2build.h>
#include FT_FREETYPE_H


#include "swCommonLib/Common/Exceptions/Nullable.h"

namespace sw
{

/**FT_Library object is not multithreaded, so the new one must be created for each new
loading operation. This class serves as RAII guard to free resources after loading is done.*/
class FreeTypeLibrary
{
protected:
    FT_Library  Library;
    FT_Face     Face;

public:
    explicit		FreeTypeLibrary	( FT_Library library ) : Library( library ) {}
    ~FreeTypeLibrary();
public:
    static Nullable<FreeTypeLibrary>   Create();

public:
    ReturnResult    CreateFace		( const LoadPath& filePath );
};


}
