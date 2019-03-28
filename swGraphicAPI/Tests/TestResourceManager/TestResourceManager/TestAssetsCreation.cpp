#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestAssetsCreation.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/nResourceManager.h"


#include "swGraphicAPI/Resources/Buffers/BufferInitData.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"

#include "swGraphicAPI/Tests/TestResourceManager/Utils/MockAsset/MockAssetCreator.h"
#include "swGraphicAPI/Tests/TestResourceManager/Utils/MockAsset/MockAsset.h"



using namespace sw;


// ================================ //
//
struct RandomStruct
{
	float	x, y, z, w;
};



// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.RegisterAssetCreator", "[GraphicAPI]" )
{
	auto creator = MockAssetCreator::CreateCreator();		// Creator must live longer then ResourceManager since it tracks references of created assets.

	nResourceManager rm;
	
	bool regResult = rm.RegisterAssetCreator( creator );
	REQUIRE( regResult == true );

	MockAssetCreateInfo init;

	auto result = rm.CreateGenericAsset( "::RegisterAssetCreator::Check", TypeID::get< MockAsset >(), std::move( init ) );
	REQUIRE( result.IsValid() );

	CHECK( rm.GetGeneric( "::RegisterAssetCreator::Check", TypeID::get< MockAsset >() ) != nullptr );
}


// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.CreateAsset.SingleAsset", "[GraphicAPI]" )
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

// ================================ //
// Can't create second asset with the same name.
TEST_CASE( "GraphicAPI.ResourceManager.CreateAsset.TwoAssetsSameName", "[GraphicAPI]" )
{
	auto creator = MockAssetCreator::CreateCreator();		// Creator must live longer then ResourceManager since it tracks references of created assets.
	nResourceManager rm;		rm.RegisterAssetCreator( creator );

	MockAssetCreateInfo init;
	
	auto result = rm.CreateGenericAsset( "::CreateAsset::TwoAssetsSameName", TypeID::get< MockAsset >(), std::move( init ) );
	REQUIRE( result.IsValid() );

	MockAssetCreateInfo init2;

	result = rm.CreateGenericAsset( "::CreateAsset::TwoAssetsSameName", TypeID::get< MockAsset >(), std::move( init2 ) );
	REQUIRE( !result.IsValid() );

	// One asset should still be alive in ResourceManager. Second asset shouldn't be created or should be properly destroyed.
	CHECK( creator->CountLivingAssets() == 1 );
}
