#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestAssetsLoadingAsync.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/AsyncLoad/RMAsyncThread.h"


#include "swGraphicAPI/MockAssets/MockAssetCreator.h"
#include "swGraphicAPI/MockAssets/MockAsset.h"
#include "swGraphicAPI/MockAssets/MockAssetLoader.h"

#include "swGraphicAPI/MockAssets/Utils.h"

#include "swCommonLib/Common/Multithreading/ThreadsBarrier.h"


using namespace sw;



// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.LoadGenericAsync.SimpleLoading", "[GraphicAPI][ResourceManager]" )
{
	auto rm = CreateResourceManagerWithMocks();
	RMAsyncThread rmThread( rm.get() );

	ResourcePointer resource;
	ThreadsBarrier barier( 2 );

	rmThread.LoadGenericAsync( "../TestAssets/mock/example.mock", nullptr, TypeID::get< MockAsset >(),
							   [ & ]( AssetLoadResponse& response )
	{
		resource = response.Resource;
		barier.ArriveAndWait();
	}, nullptr );

	barier.ArriveAndWait();

	REQUIRE( resource != nullptr );
}

// ================================ //
// If loading of asset fails, onFailed handler should be called.
TEST_CASE( "GraphicAPI.ResourceManager.LoadGenericAsync.LoadFails", "[GraphicAPI][ResourceManager]" )
{
	auto rm = CreateResourceManagerWithMocks();
	RMAsyncThread rmThread( rm.get() );

	ResourcePointer resource;
	ExceptionPtr error;
	ThreadsBarrier barier( 2 );

	rmThread.LoadGenericAsync( "../TestAssets/mock/example-not-existing.mock", nullptr, TypeID::get< MockAsset >(),
							   nullptr,
							   [ & ]( AssetLoadResponse& response, ExceptionPtr exception )
	{
		resource = response.Resource;
		error = exception;

		barier.ArriveAndWait();
	} );

	barier.ArriveAndWait();

	REQUIRE( resource == nullptr );
	CHECK( error != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.LoadGenericAsync.Load2Assets", "[GraphicAPI][ResourceManager]" )
{
	auto rm = CreateResourceManagerWithMocks();
	RMAsyncThread rmThread( rm.get() );

	ResourcePointer resource1;
	ResourcePointer resource2;
	ThreadsBarrier barier( 2 );

	rmThread.LoadGenericAsync( "../TestAssets/mock/example.mock", nullptr, TypeID::get< MockAsset >(),
							   [ & ]( AssetLoadResponse& response )
	{
		resource1 = response.Resource;
		barier.ArriveAndWait();
	}, nullptr );

	rmThread.LoadGenericAsync( "../TestAssets/mock/example1.mock", nullptr, TypeID::get< MockAsset >(),
							   [ & ]( AssetLoadResponse& response )
	{
		resource2 = response.Resource;
		barier.ArriveAndWait();
	}, nullptr );

	// Wait for assets to be loaded.
	barier.ArriveAndWait();
	barier.ArriveAndWait();

	REQUIRE( resource1 != nullptr );
	REQUIRE( resource2 != nullptr );
}
