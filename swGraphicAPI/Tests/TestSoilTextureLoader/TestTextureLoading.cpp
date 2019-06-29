#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestTextureLoading.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/nResourceManager.h"
#include "swGraphicAPI/ResourceManager/Loaders/TextureLoadInfo.h"

#include "swGraphicAPI/MockAssets/Utils.h"

#include "swCommonLib/Common/Exceptions/Common/FileNotFoundException.h"


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.SoilTextureLoader.FileDoesntExists", "[GraphicAPI][SoilTextureLoader]" )
{
	auto rm = CreateResourceManagerWithMocksAndDefaults();

	TextureLoadInfo loadInfo;

	auto resource = rm->LoadGeneric( "../TestAssets/texture/NotExisting.png", &loadInfo, TypeID::get< Texture >() );
	REQUIRE( resource.IsValid() == false );

	CHECK( resource.GetError() != nullptr );
	CHECK( resource.GetError()->get_type() == TypeID::get< FileNotFoundException >() );
}








