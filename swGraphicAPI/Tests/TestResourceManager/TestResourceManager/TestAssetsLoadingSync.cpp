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
TEST_CASE( "GraphicAPI.ResourceManager.LoadGeneric.SimpleLoading", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	MockAssetLoadInfo info;

	auto resource = rm->LoadGeneric( "../TestAssets/mock/example.mock", &info, TypeID::get< MockAsset >() );
	
	REQUIRE( resource.IsValid() == true );
	REQUIRE( resource.Get() != nullptr );
	CHECK( static_cast< MockAsset* >( resource.Get().Ptr() )->GetContent() == "Example");
}
