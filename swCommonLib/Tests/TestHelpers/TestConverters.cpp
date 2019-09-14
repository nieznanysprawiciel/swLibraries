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


//====================================================================================//
//				Test wstring conversions
//====================================================================================//

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.wstring", "[Nullable]" )
{
    auto result1 = Convert::FromString< std::wstring >( "Middle" );
    REQUIRE_IS_VALID( result1 );

    CHECK( result1.Get() == L"Middle" );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.ToString.wstring", "[Nullable]" )
{
    auto str = Convert::ToString( std::wstring( L"Middle" ) );
    CHECK( str == "Middle" );
}


//====================================================================================//
//				Test Arithmetic conversions
//====================================================================================//

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.uint32", "[Nullable]" )
{
    auto result1 = Convert::FromString< uint32 >( "3" );
    auto result2 = Convert::FromString< uint32 >( "1445" );
    auto result3 = Convert::FromString< uint32 >( "2547483647" );
    REQUIRE_IS_VALID( result1 );
    REQUIRE_IS_VALID( result2 );
    REQUIRE_IS_VALID( result3 );

    CHECK( result1.Get() == 3 );
    CHECK( result2.Get() == 1445 );
    CHECK( result3.Get() == 2547483647 );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.uint32.ExceedsLimits", "[Nullable]" )
{
    auto result1 = Convert::FromString< uint32 >( "-3" );
    auto result2 = Convert::FromString< uint32 >( "4294967296" );
    REQUIRE_FALSE( result1.IsValid() );
    REQUIRE_FALSE( result2.IsValid() );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.int", "[Nullable]" )
{
    auto result1 = Convert::FromString< int32 >( "3" );
    auto result2 = Convert::FromString< int32 >( "1445" );
    auto result3 = Convert::FromString< int32 >( "2047483647" );
    REQUIRE_IS_VALID( result1 );
    REQUIRE_IS_VALID( result2 );
    REQUIRE_IS_VALID( result3 );

    CHECK( result1.Get() == 3 );
    CHECK( result2.Get() == 1445 );
    CHECK( result3.Get() == 2047483647 );
}

