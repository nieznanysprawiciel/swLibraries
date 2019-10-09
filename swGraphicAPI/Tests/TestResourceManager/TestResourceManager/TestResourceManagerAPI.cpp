#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestResourceManagerAPI.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"

#include "swGraphicAPI/MockAssets/MockAssetCreator.h"
#include "swGraphicAPI/MockAssets/MockAsset.h"
#include "swGraphicAPI/MockAssets/MockAssetLoader.h"

#include "swGraphicAPI/MockAssets/Utils.h"


using namespace sw;


// ================================ //
//
struct Struct16Bytes
{
    float	x, y, z, w;
};



// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.API.Buffer.FromStackBuffer", "[GraphicAPI]" )
{
    auto rm = CreateResourceManagerWithMocks();
    auto api = ResourceManagerAPI( rm.get() );
    
    auto buffer = api.CreateConstantsBuffer( "::/Buffer/FromStackBuffer", StackBufferA< Struct16Bytes >() );
    REQUIRE_IS_VALID( buffer );

    CHECK( buffer.Get()->GetElementSize() == sizeof( Struct16Bytes ) );
    CHECK( buffer.Get()->GetElementCount() == 1 );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.API.Buffer.FromBufferRange.EmptyBufferRange", "[GraphicAPI]" )
{
    auto rm = CreateResourceManagerWithMocks();
    auto api = ResourceManagerAPI( rm.get() );

    auto range = BufferRange( nullptr, 0 );

    auto buffer = api.CreateConstantsBuffer( "::/Buffer/FromBufferRange/EmptyBufferRange/Constants", range );
    REQUIRE( !buffer.IsValid() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.API.Buffer.FromBufferRange.ElementSize=0", "[GraphicAPI]" )
{
    auto rm = CreateResourceManagerWithMocks();
    auto api = ResourceManagerAPI( rm.get() );

    auto data = StackBufferA< Struct16Bytes >();

    auto buffer = api.CreateVertexBuffer( "::/VertexBuffer/FromBufferRangw/EmptyBufferRange", data.GetView(), 0 );
    REQUIRE( !buffer.IsValid() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.API.VertexBuffer.FromBufferRange.EmptyBufferRange", "[GraphicAPI]" )
{
    auto rm = CreateResourceManagerWithMocks();
    auto api = ResourceManagerAPI( rm.get() );

    auto range = BufferRange( nullptr, 0 );

    auto buffer = api.CreateVertexBuffer( "::/VertexBuffer/FromBufferRangw/EmptyBufferRange", range, 0 );
    REQUIRE( !buffer.IsValid() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.API.IndexBuffer.FromBufferRange.EmptyBufferRange", "[GraphicAPI]" )
{
    auto rm = CreateResourceManagerWithMocks();
    auto api = ResourceManagerAPI( rm.get() );

    auto data = StackBufferA< Struct16Bytes >();

    auto buffer = api.CreateVertexBuffer( "::/IndexBuffer/FromBufferRangw/EmptyBufferRange", data.GetView(), 0 );
    REQUIRE( !buffer.IsValid() );
}

