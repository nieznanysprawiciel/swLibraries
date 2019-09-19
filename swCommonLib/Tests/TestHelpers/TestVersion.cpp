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


//====================================================================================//
//			Compatibility	
//====================================================================================//

// ================================ //
//
TEST_CASE( "Common.Helpers.Version.Compatibility.BetaStage", "[Version]" )
{
    CHECK( Version( 0, 1, 5 ).IsBackwardCompatibileWith( Version( 0, 1, 5 ) ) );    // Equal versions are compatibile.
    CHECK( Version( 0, 1, 5 ).IsBackwardCompatibileWith( Version( 0, 1, 3 ) ) );    // Patch version shouldn't break compatibility.
    CHECK( !Version( 0, 1, 5 ).IsBackwardCompatibileWith( Version( 0, 2, 3 ) ) );   // In beta stage Minor version changes can break compatibility.
    CHECK( !Version( 0, 2, 5 ).IsBackwardCompatibileWith( Version( 0, 1, 3 ) ) );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Version.Compatibility.BetaStageVsStable", "[Version]" )
{
    CHECK( !Version( 0, 1, 5 ).IsBackwardCompatibileWith( Version( 1, 1, 5 ) ) );
    CHECK( !Version( 1, 1, 5 ).IsBackwardCompatibileWith( Version( 0, 1, 3 ) ) );
    CHECK( !Version( 0, 1, 5 ).IsBackwardCompatibileWith( Version( 0, 2, 3 ) ) );
    CHECK( !Version( 0, 2, 5 ).IsBackwardCompatibileWith( Version( 0, 1, 3 ) ) );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Version.Compatibility.Stable", "[Version]" )
{
    CHECK( Version( 1, 1, 5 ).IsBackwardCompatibileWith( Version( 1, 1, 3 ) ) );    // Patch version change doesn't break compatibility.

    CHECK( !Version( 2, 1, 5 ).IsBackwardCompatibileWith( Version( 1, 1, 5 ) ) );   // Major change breaks compatibility.
    CHECK( !Version( 1, 1, 5 ).IsBackwardCompatibileWith( Version( 2, 1, 5 ) ) );   // Older version is incompatibile with newer version.

    CHECK( Version( 1, 2, 0 ).IsBackwardCompatibileWith( Version( 1, 1, 5 ) ) );    // Minor version change should preserve compatibility.
    CHECK( !Version( 1, 1, 0 ).IsBackwardCompatibileWith( Version( 1, 2, 5 ) ) );   // Older version is incompatibile with newer version.
    
}

