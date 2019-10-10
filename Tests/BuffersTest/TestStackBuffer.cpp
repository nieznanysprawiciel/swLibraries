#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestStackBuffer.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Buffers/StackBuffer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructWithSimpleTypes.h"



using namespace sw;


// ================================ //
//
struct Struct8Bytes
{
    double	x, y;
};

// ================================ //
//
struct Struct12Bytes
{
    float	x, y, z;
};

// ================================ //
//
struct Struct16Bytes
{
    float	x, y, z, w;
};

// ================================ //
//
struct Struct24Bytes
{
    float	x, y, z, w;
    float   u;
};

// ================================ //
//
struct Struct32Bytes
{
    double	x, y, z, w;
};


// ================================ //
//
TEST_CASE( "Common.Buffers.StackBuffer.Alignment" )
{
    CHECK( impl::ComputePadding< Struct16Bytes, 16 >() == 0 );


    CHECK( sizeof( StackBufferA< Struct8Bytes > ) == 16 );
    CHECK( sizeof( StackBufferA< Struct12Bytes > ) == 16 );
    CHECK( sizeof( StackBufferA< Struct16Bytes > ) == 16 );
    CHECK( sizeof( StackBufferA< Struct24Bytes > ) == 32 );
    CHECK( sizeof( StackBufferA< Struct32Bytes > ) == 32 );

}


