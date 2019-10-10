#include "swGraphicAPI/Tests/TestResourceManager/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestMockCompositeAsset.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/ResourceManager.h"

#include "swGraphicAPI/MockAssets/Utils.h"


using namespace sw;


// ================================ //
// Check if MockCompositeAssetLoader creates good assets hierarchy.
TEST_CASE( "GraphicAPI.TestUtils.MockCompositeAsset.Hierarchy", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	auto nestedLevel3_1 = MockCompositeAssetLoadInfo::Create( {}, { "../TestAssets/mock/example1.mock", } );
	auto nestedLevel3_2 = MockCompositeAssetLoadInfo::Create( {}, { "../TestAssets/mock/example2.mock", } );

	auto nestedLevel2_1 = MockCompositeAssetLoadInfo::Create( { nestedLevel3_1, nestedLevel3_2 }, { "../TestAssets/mock/example3.mock", } );

	auto nestedLevel1_1 = MockCompositeAssetLoadInfo::Create( { nestedLevel2_1, nestedLevel2_1 }, { "../TestAssets/mock/example.mock", } );

	auto resource = rm->LoadGeneric( "::MockCompositeAsset/Hierarchy", nestedLevel1_1.get(), TypeID::get< MockCompositeAsset >() );
	REQUIRE( resource.IsValid() == true );

	auto asset = static_cast< MockCompositeAsset* >( resource.Get().Ptr() );

	auto subassets1 = asset->GetSubAssets();
	REQUIRE( subassets1.size() == 1 );
	CHECK( subassets1[ 0 ]->GetContent() == "Example" );
	CHECK( subassets1[ 0 ]->GetAssetPath() == "../TestAssets/mock/example.mock" );

	// nestedLevel1_1
	auto composites1 = asset->GetCompositeSubAssets();
	REQUIRE( composites1.size() == 2 );
	CHECK( composites1[ 0 ]->GetAssetPath() == "::MockCompositeAsset/Hierarchy/0" );	// This is how MockCompositeAsset builds paths of nested assets.
	CHECK( composites1[ 1 ]->GetAssetPath() == "::MockCompositeAsset/Hierarchy/1" );

	// nestedLevel2_1
	REQUIRE( composites1[ 0 ]->GetSubAssets().size() == 1 );
	CHECK( composites1[ 0 ]->GetSubAssets()[ 0 ]->GetAssetPath() == "../TestAssets/mock/example3.mock" );
	CHECK( composites1[ 0 ]->GetSubAssets()[ 0 ]->GetContent() == "example3" );

	REQUIRE( composites1[ 1 ]->GetSubAssets().size() == 1 );
	CHECK( composites1[ 1 ]->GetSubAssets()[ 0 ]->GetAssetPath() == "../TestAssets/mock/example3.mock" );
	CHECK( composites1[ 1 ]->GetSubAssets()[ 0 ]->GetContent() == "example3" );

	// nestedLevel3_1 and nestedLevel3_2
	auto composites1_1 = composites1[ 0 ]->GetCompositeSubAssets();
	auto composites1_2 = composites1[ 1 ]->GetCompositeSubAssets();

	REQUIRE( composites1_1.size() == 2 );
	REQUIRE( composites1_2.size() == 2 );

	CHECK( composites1_1[ 0 ]->GetAssetPath() == "::MockCompositeAsset/Hierarchy/0/0" );
	CHECK( composites1_1[ 1 ]->GetAssetPath() == "::MockCompositeAsset/Hierarchy/0/1" );

	CHECK( composites1_2[ 0 ]->GetAssetPath() == "::MockCompositeAsset/Hierarchy/1/0" );
	CHECK( composites1_2[ 1 ]->GetAssetPath() == "::MockCompositeAsset/Hierarchy/1/1" );

	CHECK( composites1_1[ 0 ]->GetCompositeSubAssets().size() == 0 );
	CHECK( composites1_1[ 1 ]->GetCompositeSubAssets().size() == 0 );
	CHECK( composites1_2[ 0 ]->GetCompositeSubAssets().size() == 0 );
	CHECK( composites1_2[ 1 ]->GetCompositeSubAssets().size() == 0 );

	CHECK( composites1_1[ 0 ]->GetSubAssets().size() == 1 );
	CHECK( composites1_1[ 1 ]->GetSubAssets().size() == 1 );
	CHECK( composites1_2[ 0 ]->GetSubAssets().size() == 1 );
	CHECK( composites1_2[ 1 ]->GetSubAssets().size() == 1 );

	CHECK( composites1_1[ 0 ]->GetSubAssets()[ 0 ]->GetContent() == "example1" );
	CHECK( composites1_1[ 1 ]->GetSubAssets()[ 0 ]->GetContent() == "example2" );
	CHECK( composites1_2[ 0 ]->GetSubAssets()[ 0 ]->GetContent() == "example1" );
	CHECK( composites1_2[ 1 ]->GetSubAssets()[ 0 ]->GetContent() == "example2"  );
}


