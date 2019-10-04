#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestMacros.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Macros/ForEach.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"




#define APPEND_TEST(X) test##X
#define MAKE_STRING(X) #X

// This macro will first evaluate expression, so it can be converted to string.
#define STR(X) MAKE_STRING(X)

// ================================ //
//
TEST_CASE( "Common.Helpers.Macros.FOR_EACH", "[Version]" )
{
    CHECK( STR( FOR_EACH( APPEND_TEST, x, y, z ) ) == "testx,testy,testz" );
    CHECK( STR( FOR_EACH( APPEND_TEST, x, y, z, u, v ) ) == "testx,testy,testz,testu,testv" );
}

