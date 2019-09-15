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

// ================================ //
//
TEST_CASE( "Common.Helpers.Version.FromString.InvalidString", "[Version]" )
{
    auto result = Version::From( "bla.1.4.3344" );
    REQUIRE_FALSE( result.IsValid() );
    
    result = Version::From( "4.-2.0.2" );
    REQUIRE_FALSE( result.IsValid() );
}

// ================================ //
// ToString produces string that can be used to create Version object.
TEST_CASE( "Common.Helpers.Version.ToString", "[Version]" )
{
    auto result = Version::From( Version( 0, 1, 4, 3344 ).ToString() );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == Version( 0, 1, 4, 3344 ) );
}



