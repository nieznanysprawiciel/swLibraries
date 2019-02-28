#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestBufferCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Buffers/BufferCreator.h"
#include "swGraphicAPI/Resources/IBuffer.h"

#include "swCommonLib/Common/Buffers/BufferTyped.h"


using namespace sw;



// ================================ //
//
struct Buffer8Bytes
{
	float x, y;
};


// ================================ //
// Creator shouldn't create buffer, that hasn't size that is multiply of 16 bytes.
TEST_CASE( "GraphicAPI.AssetsCreators.BufferCreator.ConstantBuffer.NotAligned", "[GraphicAPI][AssetsCreators]" )
{
	BufferCreator creator;
	BufferTyped< Buffer8Bytes > buffer( 1 );
	
	ConstantBufferInitData init;
	init.ElementSize = (uint32)buffer.ElementSize();
	init.NumElements = (uint32)buffer.ElementsCount();
	init.Data = buffer.GetRawData();

	auto result = creator.Create( "::Buffer::NotAligned", std::move( init ) );
	REQUIRE( result.IsValid() == false );

	CHECK( result.GetError() != nullptr );
}

