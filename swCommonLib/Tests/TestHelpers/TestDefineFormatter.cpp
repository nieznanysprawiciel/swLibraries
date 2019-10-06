#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestDefineFormatter.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Macros/ForEach.h"
#include "swCommonLib/Common/Macros/DefineFmtFormatter.h"
#include "swCommonLib/External/fmt/format.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


//====================================================================================//
//			Test helper classes	
//====================================================================================//

// ================================ //
//
struct Test1
{
    std::string     str;

// ================================ //
//
    std::string     ToString    () const    { return str; }
};
DEFINE_FMT_FORMATTER( Test1, "{}", ToString() );


// ================================ //
//
struct Test2
{
    int x;
    int y;
    int z;
};
DEFINE_FMT_FORMATTER( Test2, "{}.{}.{}", x, y, z );


// ================================ //
//
struct Test3
{
    int x;
    int y;
    int z;
};
DEFINE_DEFAULT_FMT_STRUCT_FORMATTER( Test3, x, y, z );


//====================================================================================//
//			Test cases	
//====================================================================================//

// ================================ //
//
TEST_CASE( "Common.Helpers.Macros.DEFINE_FMT_FORMATTER.UseMemberFunction", "[Version]" )
{
    Test1 test = { "Test passed" };
    CHECK( fmt::format( "{}", test ) == "Test passed" );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Macros.DEFINE_FMT_FORMATTER.UseMember", "[Version]" )
{
    Test2 test = { 1, 2, 3 };
    CHECK( fmt::format( "{}", test ) == "1.2.3" );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Macros.DEFINE_DEFAULT_FMT_STRUCT_FORMATTER", "[Version]" )
{
    Test3 test = { 1, 2, 3 };
    CHECK( fmt::format( "{}", test ) == "[ x=1, y=2, z=3 ]" );
}
