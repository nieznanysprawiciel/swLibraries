#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestConverters.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Converters/Convert.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Enums/TriStateEnum.h"

using namespace sw;


//====================================================================================//
//			Test enum conversions	
//====================================================================================//


// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Enum", "[Nullable]" )
{
    auto result1 = Convert::FromString< TriStateEnum >( "Middle" );
    auto result2 = Convert::FromString< TriStateEnum >( "Up" );
    auto result3 = Convert::FromString< TriStateEnum >( "Down" );
    REQUIRE_IS_VALID( result1 );
    REQUIRE_IS_VALID( result2 );
    REQUIRE_IS_VALID( result3 );

    CHECK( result1.Get() == TriStateEnum::Middle );
    CHECK( result2.Get() == TriStateEnum::Up );
    CHECK( result3.Get() == TriStateEnum::Down );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Enum.InvalidString", "[Nullable]" )
{
    auto result = Convert::FromString< TriStateEnum >( "bad" );
    REQUIRE_FALSE( result.IsValid() );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Enum.InvalidString.Default", "[Nullable]" )
{
    TriStateEnum result = Convert::FromString< TriStateEnum >( "bad", TriStateEnum::Middle );
    CHECK( result == TriStateEnum::Middle );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.ToString.Enum", "[Nullable]" )
{
    auto str = Convert::ToString( TriStateEnum::Middle );
    CHECK( str == "Middle" );
}

