#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestAssetsCreation.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/nResourceManager.h"


#include "swGraphicAPI/Resources/Buffers/BufferInitData.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"



using namespace sw;


// ================================ //
//
struct RandomStruct
{
	float	x, y, z, w;
};




// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.CreateAsset.", "[GraphicAPI]" )
{
	nResourceManager rm;

	BufferTyped< RandomStruct > buffer( 10 );
	
	ConstantBufferInitData init;
	init.ElementSize = (uint32)buffer.ElementSize();
	init.NumElements = (uint32)buffer.ElementsCount();
	init.Data = buffer.GetRawData();

	auto result = rm.CreateGenericAsset( "::RandomBuffer", TypeID::get< Buffer >(), std::move( init ) );
	REQUIRE( result.IsValid() );

	CHECK( result.Get() != nullptr );
	CHECK( rm.GetGeneric( "::RandomBuffer", TypeID::get< Buffer >() ) != nullptr );
}


