#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestPathAliases.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/nResourceManager.h"

#include "swGraphicAPI/MockAssets/Utils.h"
#include "swCommonLib/Common/Multithreading/ThreadsBarrier.h"


using namespace sw;


// ================================ //
// Developer can use path aliases to load resource.
TEST_CASE( "GraphicAPI.ResourceManager.PathAliases.Loading", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	MockAssetLoadInfo info;
	auto resource = rm->LoadGeneric( "$(MocksDir)/example.mock", &info, TypeID::get< MockAsset >() );
	REQUIRE_IS_VALID( resource );

	// Resource file name should contain alias.
	CHECK( resource.Get()->GetFilePath() == "$(MocksDir)/example.mock" );

	// Resource can be found using alias path.
	auto resourceByMockAlias = rm->Get< MockAsset >( "$(MocksDir)/example.mock" );
	REQUIRE_IS_VALID( resource );

	// Resource can be found using absolute path.
	auto resourceByAbsolutePath = rm->Get< MockAsset >( "../TestAssets/mock/example.mock" );
	REQUIRE_IS_VALID( resource );
}


// ================================ //
// Loading the same file pointed by two different path aliases, should load the same asset.
TEST_CASE( "GraphicAPI.ResourceManager.PathAliases.Loading.SamePathDifferentAliases", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	MockAssetLoadInfo info;
	auto resource1 = rm->LoadGeneric( "$(MocksDir)/example.mock", &info, TypeID::get< MockAsset >() );
	REQUIRE_IS_VALID( resource1 );

	auto resource2 = rm->LoadGeneric( "$(TestAssets)/mock/example.mock", &info, TypeID::get< MockAsset >() );
	REQUIRE_IS_VALID( resource2 );

	CHECK( resource1.Get() == resource2.Get() );
}


// ================================ //
// Load resource from two threads at the same time using two diferent path aliases.
// Only one resource should be loaded. 
TEST_CASE( "GraphicAPI.ResourceManager.PathAliases.Loading.TwoThreadsSameAsset", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	MockAssetLoadInfo info;
	ThreadsBarrier barrier( 2 );

	Nullable< ResourcePointer > threadResource;

	std::thread thread( [ & ]()
	{
		barrier.ArriveAndWait();
		threadResource = rm->LoadGeneric( "$(MocksDir)/example.mock", &info, TypeID::get< MockAsset >() );
	} );

	// Wait for second thread initialization.
	barrier.ArriveAndWait();
	auto resource = rm->LoadGeneric( "$(TestAssets)/mock/example.mock", &info, TypeID::get< MockAsset >() );

	thread.join();

	REQUIRE( resource.IsValid() == true );
	REQUIRE( threadResource.IsValid() == true );

	CHECK( resource.Get() == threadResource.Get() );
}
