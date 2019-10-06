#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestListAssets.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/ResourceManager.h"

#include "swGraphicAPI/MockAssets/Utils.h"


using namespace sw;


// ================================ //
// FreeUnusedAssets must properly free all dependent assets.
TEST_CASE( "GraphicAPI.ResourceManager.ListAssets", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();
	auto info = MockCompositeAssetLoadInfo::Create( {}, { "../TestAssets/mock/example1.mock", "../TestAssets/mock/example2.mock", "../TestAssets/mock/example3.mock" } );

	auto resource = rm->LoadGeneric( "::GraphicAPI/ResourceManager/AssetsRemoval/FreeUnusedAssets", info.get(), TypeID::get< MockCompositeAsset >() );
	REQUIRE( resource.IsValid() == true );
	REQUIRE( resource.Get() != nullptr );

	auto mockAssetsList = rm->ListAssets( TypeID::get< MockAsset >() );
	auto mockCompositeAssetsList = rm->ListAssets( TypeID::get< MockCompositeAsset >() );

	CHECK( mockAssetsList.size() == 3 );
	CHECK( mockCompositeAssetsList.size() == 1 );
}


