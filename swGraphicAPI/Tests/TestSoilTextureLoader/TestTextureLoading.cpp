#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestTextureLoading.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/Loaders/TextureLoadInfo.h"
#include "swGraphicAPI/ResourceManager/Exceptions/LoaderException.h"

#include "swGraphicAPI/MockAssets/Utils.h"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"

#include "swCommonLib/Common/Exceptions/Common/FileNotFoundException.h"


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.SoilTextureLoader.FileDoesntExists", "[GraphicAPI][SoilTextureLoader]" )
{
	auto rm = CreateRMWithDefaultsMocksSoil();

	TextureLoadInfo loadInfo;

	auto resource = rm->LoadGeneric( "../TestAssets/texture/NotExisting.png", &loadInfo, TypeID::get< Texture >() );
	REQUIRE( resource.IsValid() == false );

	CHECK( resource.GetError() != nullptr );
	CHECK( resource.GetError()->get_type() == TypeID::get< FileNotFoundException >() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.SoilTextureLoader.Load.png", "[GraphicAPI][SoilTextureLoader]" )
{
	auto rm = CreateRMWithDefaultsMocksSoil();

	TextureLoadInfo loadInfo;

	auto resource = rm->LoadGeneric( "../TestAssets/texture/random-pixels.png", &loadInfo, TypeID::get< Texture >() );
	REQUIRE_IS_VALID( resource );

	TexturePtr texture = static_cast< Texture* >( resource.Get().Ptr() );
	auto desc = texture->GetDescriptor();

	CHECK( desc.Height == 4 );
	CHECK( desc.Width == 4 );

	CHECK( desc.Format == ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM );
}


// ================================ //
// Forcing format is not supported.
TEST_CASE( "GraphicAPI.DX11.SoilTextureLoader.Load.ForceFormat", "[GraphicAPI][SoilTextureLoader]" )
{
	auto rm = CreateRMWithDefaultsMocksSoil();

	TextureLoadInfo loadInfo;
	loadInfo.Processing.ForceFormat = true;
	loadInfo.Processing.TargetFormat = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;

	auto resource = rm->LoadGeneric( "../TestAssets/texture/random-pixels.png", &loadInfo, TypeID::get< Texture >() );
	REQUIRE( resource.IsValid() == false );

	CHECK( resource.GetError() != nullptr );
	CHECK( resource.GetError()->get_type() == TypeID::get< LoaderException >() );
}





