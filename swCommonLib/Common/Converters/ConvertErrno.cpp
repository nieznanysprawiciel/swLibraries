/**
@file ConvertErrno.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Convert.h"




// ================================ //
//
std::string             Convert::ErrnoToString          ( int err )
{
    /// @todo This version is unsafe. Possible issueas with multithreading.
    /// Find safe solution and reimplement this function.
    return std::strerror( errno );
}



