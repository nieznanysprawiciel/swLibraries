#include "swGraphicAPI/Tests/TestResources.DX11/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestBufferCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Buffers/BufferCreator.h"
#include "swGraphicAPI/Resources/Buffers/BufferInitData.h"

#include "swCommonLib/Common/Buffers/BufferTyped.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


using namespace sw;


// ================================ //
//
struct Struct16Bytes
{
	float	x, y, z, w;
};


// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.BufferCreator.ConstantBuffer.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	BufferTyped< Struct16Bytes > buffer( 10 );
	
	ConstantBufferInitData init;
	init.ElementSize = (uint32)buffer.ElementSize();
	init.NumElements = (uint32)buffer.ElementsCount();
	init.Data = buffer.GetRawData();

	auto result = factory.CreateAsset( "::/BufferFromMemory/Constants", TypeID::get< Buffer >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );

	Buffer* bufferPtr = static_cast< Buffer* >( result.Get() );

	CHECK( bufferPtr->GetElementSize() == sizeof( Struct16Bytes ) );
	CHECK( bufferPtr->GetElementCount() == 10 );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.BufferCreator.IndexBuffer.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	BufferTyped< Index16 > buffer( 10 );
	
	IndexBufferInitData init;
	init.ElementSize = (uint32)buffer.ElementSize();
	init.NumElements = (uint32)buffer.ElementsCount();
	init.Data = buffer.GetRawData();

	auto result = factory.CreateAsset( "::/BufferFromMemory/Index", TypeID::get< Buffer >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );

	Buffer* bufferPtr = static_cast< Buffer* >( result.Get() );

	CHECK( bufferPtr->GetElementSize() == sizeof( Index16 ) );
	CHECK( bufferPtr->GetElementCount() == 10 );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.BufferCreator.VertexBuffer.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	BufferTyped< Struct16Bytes > buffer( 10 );
	
	VertexBufferInitData init;
	init.ElementSize = (uint32)buffer.ElementSize();
	init.NumElements = (uint32)buffer.ElementsCount();
	init.Data = buffer.GetRawData();

	auto result = factory.CreateAsset( "::/BufferFromMemory/Vertex", TypeID::get< Buffer >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );

	Buffer* bufferPtr = static_cast< Buffer* >( result.Get() );

	CHECK( bufferPtr->GetElementSize() == sizeof( Struct16Bytes ) );
	CHECK( bufferPtr->GetElementCount() == 10 );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.BufferCreator.ConstantBuffer.Create.NullptrInit", "[GraphicAPI]" )
{
    AssetsFactory factory;

    ConstantBufferInitData init;
    init.ElementSize = 16;
    init.NumElements = 2;
    init.Data = nullptr;

    auto result = factory.CreateAsset( "::/BufferFromMemory/Constants", TypeID::get< Buffer >(), std::move( init ) );
    REQUIRE_IS_VALID( result );

    REQUIRE( result.Get() != nullptr );

    Buffer* bufferPtr = static_cast< Buffer* >( result.Get() );

    CHECK( bufferPtr->GetElementSize() == 16 );
    CHECK( bufferPtr->GetElementCount() == 2 );
}

