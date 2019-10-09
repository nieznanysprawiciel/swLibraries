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


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourceManager.RegisterLoader", "[GraphicAPI]" )
{
	auto loader = std::make_shared< MockAssetLoader >();

	ResourceManager rm;
	bool registerResult = rm.RegisterLoader( loader );

	REQUIRE( registerResult == true );

	auto loaders = rm.ListLoaders();

    // RM registers 2 loaders by itself.
	REQUIRE( loaders.size() == 3 );
	CHECK( std::find( loaders.begin(), loaders.end(), loader ) != loaders.end() );
}


