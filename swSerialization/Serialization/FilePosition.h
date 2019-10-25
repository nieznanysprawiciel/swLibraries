#pragma once

#include "swCommonLib/Common/TypesDefinitions.h"


namespace sw
{

// ***********************
//
struct FilePosition
{
    Size			Line;
    Size			CharPosition;

    // ***********************
    //
    FilePosition()
        : Line( 0 )
        , CharPosition( 0 )
    {}
};



}	// bv
