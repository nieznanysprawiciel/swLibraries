#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestAssetsLoadingSync.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/nResourceManager.h"


#include "swGraphicAPI/MockAssets/MockAssetCreator.h"
#include "swGraphicAPI/MockAssets/MockAsset.h"
#include "swGraphicAPI/MockAssets/MockAssetLoader.h"

#include "swGraphicAPI/MockAssets/Utils.h"


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


