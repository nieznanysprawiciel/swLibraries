#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestAssetsLoadingSync.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/nResourceManager.h"

#include "swGraphicAPI/Tests/TestResourceManager/Utils/Utils.h"


using namespace sw;



// ================================ //
// FreeUnusedAssets must properly free all dependent assets.
TEST_CASE( "GraphicAPI.ResourceManager.AssetsRemoval.FreeUnusedAssets", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	auto nestedLevel3 = MockCompositeAssetLoadInfo::Create( {}, { "../TestAssets/mock/example1.mock", "../TestAssets/mock/example.mock" } );
	auto nestedLevel2 = MockCompositeAssetLoadInfo::Create( { nestedLevel3 }, { "../TestAssets/mock/example2.mock", } );
	auto nestedLevel1 = MockCompositeAssetLoadInfo::Create( { nestedLevel2 }, { "../TestAssets/mock/example3.mock", } );

	auto resource = rm->LoadGeneric( "::/AssetsRemoval/FreeUnusedAssets", nestedLevel1.get(), TypeID::get< MockCompositeAsset >() );
	REQUIRE( resource.IsValid() == true );
	REQUIRE( resource.Get() != nullptr );
	
	{
		// Make sure rm holds as many assets as we expect.
		auto mockAssetsList = rm->ListAssets( TypeID::get< MockAsset >() );
		auto mockCompositeAssetsList = rm->ListAssets( TypeID::get< MockCompositeAsset >() );

		CHECK( mockAssetsList.size() == 4 );
		CHECK( mockCompositeAssetsList.size() == 3 );
	}

	// Free reference to top level resource. This is necessary because FreeUnusedAssets
	// removes only assets without references.
	resource.Get().ReleaseResource();

	// Free all assets.
	rm->FreeUnusedAssets();

	// Check if all assets were removed.
	{
		auto mockAssetsList = rm->ListAssets( TypeID::get< MockAsset >() );
		auto mockCompositeAssetsList = rm->ListAssets( TypeID::get< MockCompositeAsset >() );

		CHECK( mockAssetsList.size() == 0 );
		CHECK( mockCompositeAssetsList.size() == 0 );
	}
}

// ================================ //
// Checks if FreeUnusedAssets doesn't remove referenced assets.
TEST_CASE( "GraphicAPI.ResourceManager.AssetsRemoval.FreeUnusedAssets.DontFreeUsedAsset", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	auto usedAssetInfo = MockCompositeAssetLoadInfo::Create( {}, { "../TestAssets/mock/example1.mock" } );
	auto unusedAssetInfo = MockCompositeAssetLoadInfo::Create( {}, { "../TestAssets/mock/example2.mock" } );

	auto usedRes = rm->LoadGeneric( "::/AssetsRemoval/FreeUnusedAssets/DontFreeUsedAsset/Used", usedAssetInfo.get(), TypeID::get< MockCompositeAsset >() );
	auto unusedRes = rm->LoadGeneric( "::/AssetsRemoval/FreeUnusedAssets/DontFreeUsedAsset/NotUsed", unusedAssetInfo.get(), TypeID::get< MockCompositeAsset >() );

	REQUIRE( usedRes.IsValid() == true );
	REQUIRE( unusedRes.IsValid() == true );

	// Release only one resource.
	unusedRes.Get().ReleaseResource();

	rm->FreeUnusedAssets();

	// Check if all expected assets were removed.
	{
		auto mockAssetsList = rm->ListAssets( TypeID::get< MockAsset >() );
		auto mockCompositeAssetsList = rm->ListAssets( TypeID::get< MockCompositeAsset >() );

		CHECK( mockAssetsList.size() == 1 );
		CHECK( mockCompositeAssetsList.size() == 1 );
	}

	auto usedAsset2 = rm->GetGeneric( "::/AssetsRemoval/FreeUnusedAssets/DontFreeUsedAsset/Used", TypeID::get< MockCompositeAsset >() );
	CHECK( usedAsset2.Ptr() != nullptr );

	auto internalReferenced = rm->GetGeneric( "../TestAssets/mock/example1.mock", TypeID::get< MockAsset >() );
	CHECK( internalReferenced.Ptr() != nullptr );
}


