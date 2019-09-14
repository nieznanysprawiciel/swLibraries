#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestVersion.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Version.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


using namespace sw;



// ================================ //
//
TEST_CASE( "Common.Helpers.Version.FromString", "[Version]" )
{
    auto result = Version::From( "0.1.4.3344" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == Version( 0, 1, 4, 3344 ) );

    result = Version::From( "4.2.0.2" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == Version( 4, 2, 0, 2 ) );
}



