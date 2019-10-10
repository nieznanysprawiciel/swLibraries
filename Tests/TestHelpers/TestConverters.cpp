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
TEST_CASE( "Common.Helpers.Converters.FromString.Enum", "[Converters]" )
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
TEST_CASE( "Common.Helpers.Converters.FromString.Enum.InvalidString", "[Converters]" )
{
    auto result = Convert::FromString< TriStateEnum >( "bad" );
    REQUIRE_FALSE( result.IsValid() );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Enum.InvalidString.Default", "[Converters]" )
{
    TriStateEnum result = Convert::FromString< TriStateEnum >( "bad", TriStateEnum::Middle );
    CHECK( result == TriStateEnum::Middle );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.ToString.Enum", "[Converters]" )
{
    auto str = Convert::ToString( TriStateEnum::Middle );
    CHECK( str == "Middle" );
}


//====================================================================================//
//				Test wstring conversions
//====================================================================================//

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.wstring", "[Converters]" )
{
    auto result1 = Convert::FromString< std::wstring >( "Middle" );
    REQUIRE_IS_VALID( result1 );

    CHECK( result1.Get() == L"Middle" );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.ToString.wstring", "[Converters]" )
{
    auto str = Convert::ToString( std::wstring( L"Middle" ) );
    CHECK( str == "Middle" );
}


//====================================================================================//
//				Test Arithmetic conversions
//====================================================================================//

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.uint32", "[Converters]" )
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
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.uint32.ExceedsLimits", "[Converters]" )
{
    auto result1 = Convert::FromString< uint32 >( "-3" );
    auto result2 = Convert::FromString< uint32 >( "4294967296" );
    REQUIRE_FALSE( result1.IsValid() );
    REQUIRE_FALSE( result2.IsValid() );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.int32", "[Converters]" )
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

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.int32.ExceedsLimits", "[Converters]" )
{
    auto result1 = Convert::FromString< int32 >( "2547483647" );
    auto result2 = Convert::FromString< int32 >( "-2147483649" );
    REQUIRE_FALSE( result1.IsValid() );
    REQUIRE_FALSE( result2.IsValid() );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.uint64", "[Converters]" )
{
    auto result1 = Convert::FromString< uint64 >( "3" );
    auto result2 = Convert::FromString< uint64 >( "1445" );
    auto result3 = Convert::FromString< uint64 >( "18446744073709551614" );
    REQUIRE_IS_VALID( result1 );
    REQUIRE_IS_VALID( result2 );
    REQUIRE_IS_VALID( result3 );

    CHECK( result1.Get() == 3 );
    CHECK( result2.Get() == 1445 );
    CHECK( result3.Get() == 18446744073709551614 );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.uint64.ExceedsLimits", "[Converters]" )
{
    auto result1 = Convert::FromString< uint64 >( "-1" );
    auto result2 = Convert::FromString< uint64 >( "18446744073709551617" );
    REQUIRE_FALSE( result1.IsValid() );
    REQUIRE_FALSE( result2.IsValid() );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.bool", "[Converters]" )
{
    auto result1 = Convert::FromString< bool >( "true" );
    auto result2 = Convert::FromString< bool >( "false" );
    REQUIRE_IS_VALID( result1 );
    REQUIRE_IS_VALID( result2 );

    CHECK( result1.Get() == true );
    CHECK( result2.Get() == false );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.bool.InvalidString", "[Converters]" )
{
    auto result1 = Convert::FromString< bool >( "not-bool" );
    auto result2 = Convert::FromString< bool >( "3709551617" );
    REQUIRE_FALSE( result1.IsValid() );
    REQUIRE_FALSE( result2.IsValid() );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.FromString.Arithmetic.float", "[Converters]" )
{
    auto result1 = Convert::FromString< float >( "0.5342" );
    auto result2 = Convert::FromString< float >( "-0.111" );
    REQUIRE_IS_VALID( result1 );
    REQUIRE_IS_VALID( result2 );

    CHECK( result1.Get() == 0.5342f );
    CHECK( result2.Get() == -0.111f );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Converters.ToString.Type", "[Converters]" )
{
    auto str = Convert::ToString< TriStateEnum >();
    CHECK( str == "TriStateEnum" );
}
