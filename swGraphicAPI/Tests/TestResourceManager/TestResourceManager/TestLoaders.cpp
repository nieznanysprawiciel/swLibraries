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


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.RegisterLoader", "[GraphicAPI]" )
{
	auto loader = std::make_shared< MockAssetLoader >();

	nResourceManager rm;
	bool registerResult = rm.RegisterLoader( loader );

	REQUIRE( registerResult == true );

	auto loaders = rm.ListLoaders();

	REQUIRE( loaders.size() == 1 );
	CHECK( loaders[ 0 ] == loader );
}

