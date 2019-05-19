#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestAssetsLoadingSync.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/nResourceManager.h"


#include "swGraphicAPI/Tests/TestResourceManager/Utils/MockAsset/MockAssetCreator.h"
#include "swGraphicAPI/Tests/TestResourceManager/Utils/MockAsset/MockAsset.h"
#include "swGraphicAPI/Tests/TestResourceManager/Utils/MockAsset/MockAssetLoader.h"

#include "swGraphicAPI/Tests/TestResourceManager/Utils/Utils.h"

#include "swCommonLib/Common/Multithreading/ThreadsBarrier.h"


using namespace sw;



// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.LoadGeneric.SimpleLoading", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	MockAssetLoadInfo info;

	auto resource = rm->LoadGeneric( "../TestAssets/mock/example.mock", &info, TypeID::get< MockAsset >() );
	
	REQUIRE( resource.IsValid() == true );
	REQUIRE( resource.Get() != nullptr );
	CHECK( static_cast< MockAsset* >( resource.Get().Ptr() )->GetContent() == "Example");

	// This will hang if assets locks aren't released properly.
	auto resource2 = rm->LoadGeneric( "../TestAssets/mock/example.mock", &info, TypeID::get< MockAsset >() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.LoadGeneric.LoadNotExisting", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	MockAssetLoadInfo info;

	auto resource = rm->LoadGeneric( "../TestAssets/mock/example-notexists.mock", &info, TypeID::get< MockAsset >() );

	REQUIRE( resource.IsValid() == false );

	// This will hang if assets locks aren't released properly.
	auto resource2 = rm->LoadGeneric( "../TestAssets/mock/example.mock", &info, TypeID::get< MockAsset >() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.LoadGeneric.NotRegisteredLoader", "[GraphicAPI]" )
{
	std::unique_ptr< nResourceManager > rm = std::make_unique< nResourceManager >();

	MockAssetLoadInfo info;
	auto resource = rm->LoadGeneric( "../TestAssets/mock/example.mock", &info, TypeID::get< MockAsset >() );

	REQUIRE( resource.IsValid() == false );

	// This will hang if assets locks aren't released properly.
	auto resource2 = rm->LoadGeneric( "../TestAssets/mock/example.mock", &info, TypeID::get< MockAsset >() );
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
		threadResource = rm->LoadGeneric( "../TestAssets/mock/example.mock", &info, TypeID::get< MockAsset >() );
	} );

	// Wait for second thread initialization.
	barrier.ArriveAndWait();
	auto resource = rm->LoadGeneric( "../TestAssets/mock/example.mock", &info, TypeID::get< MockAsset >() );

	thread.join();

	REQUIRE( resource.IsValid() == true );
	REQUIRE( threadResource.IsValid() == true );

	CHECK( resource.Get() == threadResource.Get() );
}

