#include "swGraphicAPI/Tests/TestResourceManager/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestAssetsLoadingSync.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/ResourceManager.h"


#include "swGraphicAPI/MockAssets/MockAssetCreator.h"
#include "swGraphicAPI/MockAssets/MockAsset.h"
#include "swGraphicAPI/MockAssets/MockAssetLoader.h"

#include "swGraphicAPI/MockAssets/Utils.h"

#include "swCommonLib/Common/Multithreading/ThreadsBarrier.h"


using namespace sw;



// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.LoadGeneric.SimpleLoading", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	MockAssetLoadInfo info;

	auto resource = rm->LoadGeneric( "$(TestAssets)/mock/example.mock", &info, TypeID::get< MockAsset >() );
	
	REQUIRE( resource.IsValid() == true );
	REQUIRE( resource.Get() != nullptr );
	CHECK( static_cast< MockAsset* >( resource.Get().Ptr() )->GetContent() == "Example");

	// This will hang if assets locks aren't released properly.
	auto resource2 = rm->LoadGeneric( "$(TestAssets)/mock/example.mock", &info, TypeID::get< MockAsset >() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.LoadGeneric.LoadNotExisting", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	MockAssetLoadInfo info;

	auto resource = rm->LoadGeneric( "$(TestAssets)/mock/example-notexists.mock", &info, TypeID::get< MockAsset >() );

	REQUIRE( resource.IsValid() == false );

	// This will hang if assets locks aren't released properly.
	auto resource2 = rm->LoadGeneric( "$(TestAssets)/mock/example.mock", &info, TypeID::get< MockAsset >() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.LoadGeneric.NotRegisteredLoader", "[GraphicAPI]" )
{
	std::unique_ptr< ResourceManager > rm = std::make_unique< ResourceManager >();

	MockAssetLoadInfo info;
	auto resource = rm->LoadGeneric( "$(TestAssets)/mock/example.mock", &info, TypeID::get< MockAsset >() );

	REQUIRE( resource.IsValid() == false );

	// This will hang if assets locks aren't released properly.
	auto resource2 = rm->LoadGeneric( "$(TestAssets)/mock/example.mock", &info, TypeID::get< MockAsset >() );
}

// ================================ //
// Load resource from two threads at the same time. Only one resource should
// be loaded.
TEST_CASE( "GraphicAPI.ResourceManager.LoadGeneric.TwoThreadsSameAsset", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	MockAssetLoadInfo info;
	ThreadsBarrier barrier( 2 );

	Nullable< ResourcePointer > threadResource;

	std::thread thread( [ & ]()
	{
		barrier.ArriveAndWait();
		threadResource = rm->LoadGeneric( "$(TestAssets)/mock/example.mock", &info, TypeID::get< MockAsset >() );
	} );

	// Wait for second thread initialization.
	barrier.ArriveAndWait();
	auto resource = rm->LoadGeneric( "$(TestAssets)/mock/example.mock", &info, TypeID::get< MockAsset >() );

	thread.join();

	REQUIRE( resource.IsValid() == true );
	REQUIRE( threadResource.IsValid() == true );

	CHECK( resource.Get() == threadResource.Get() );
}

// ================================ //
// We first load asset and then try to load it again. We should get the same asset object.
TEST_CASE( "GraphicAPI.ResourceManager.LoadGeneric.LoadSameAfterLoad", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	MockAssetLoadInfo info;

	auto resource = rm->LoadGeneric( "$(TestAssets)/mock/example.mock", &info, TypeID::get< MockAsset >() );

	REQUIRE( resource.IsValid() == true );
	REQUIRE( resource.Get() != nullptr );

	// This will hang if assets locks aren't released properly.
	auto resource2 = rm->LoadGeneric( "$(TestAssets)/mock/example.mock", &info, TypeID::get< MockAsset >() );

	CHECK( resource.Get() == resource2.Get() );
}

