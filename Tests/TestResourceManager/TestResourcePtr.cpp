#include "swGraphicAPI/Tests/TestResourceManager/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestResourcePtr.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/ResourcePtr.h"

#include "swGraphicAPI/MockAssets/Utils.h"


using namespace sw;



// ================================ //
// 
TEST_CASE( "GraphicAPI.ResourcePtr.Construct.FromPtr", "[GraphicAPI]" )
{
	auto asset = new MockCompositeAsset( "::TestResourcePtr", {}, {} );

	uint32 numRefs = 0;

	{
		MockCompositeAssetPtr ptr1( asset );

		CHECK( ptr1->CanDelete( numRefs ) == false );
		CHECK( numRefs == 1 );

		MockCompositeAssetPtr ptr2( asset );

		CHECK( ptr1->CanDelete( numRefs ) == false );
		CHECK( numRefs == 2 );
	}

	CHECK( asset->CanDelete( numRefs ) == true );
	CHECK( numRefs == 0 );
}


