#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestAssetsLoadingSync.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/nResourceManager.h"

#include "swGraphicAPI/Tests/TestResourceManager/Utils/Utils.h"


using namespace sw;



//// ================================ //
//// FreeUnusedAssets must properly free all dependent assets.
//TEST_CASE( "GraphicAPI.ResourceManager.AssetsRemoval.FreeUnusedAssets", "[GraphicAPI]" )
//{
//	auto rm = CreateResourceManagerWithMocks();
//
//	auto nestedLevel3 = MockCompositeAssetLoadInfo::Create( {}, { "../TestAssets/mock/example1.mock", } );
//
//	MockCompositeAssetLoadInfo info(;
//
//	auto resource = rm->LoadGeneric( "../TestAssets/mock/example.mock", &info, TypeID::get< MockAsset >() );
//
//	REQUIRE( resource.IsValid() == true );
//	REQUIRE( resource.Get() != nullptr );
//	CHECK( static_cast<MockAsset*>(resource.Get().Ptr())->GetContent() == "Example" );
//}
