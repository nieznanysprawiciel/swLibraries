#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestFilesLoading.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/nResourceManager.h"
#include "swGraphicAPI/ResourceManager/Loaders/TextureLoadInfo.h"

#include "swGraphicAPI/MockAssets/GraphicAPI.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.SoilTextureLoader.Load.png", "[GraphicAPI][SoilTextureLoader]" )
{
	auto rm = CreateResourceManagerWithDefaults();

	TextureLoadInfo loadInfo;

	auto resource = rm->LoadGeneric( "../TestAssets/texture/random-pixels.png", &loadInfo, TypeID::get< Texture >() );
	REQUIRE_IS_VALID( resource );

	TexturePtr texture = static_cast< Texture* >( resource.Get().Ptr() );
	auto desc = texture->GetDescriptor();

	CHECK( desc.Height == 4 );
	CHECK( desc.Width == 4 );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.SoilTextureLoader.Load.jpg", "[GraphicAPI][SoilTextureLoader]" )
{
	auto rm = CreateResourceManagerWithDefaults();

	TextureLoadInfo loadInfo;

	auto resource = rm->LoadGeneric( "../TestAssets/texture/random-pixels.jpg", &loadInfo, TypeID::get< Texture >() );
	REQUIRE_IS_VALID( resource );

	TexturePtr texture = static_cast<Texture*>(resource.Get().Ptr());
	auto desc = texture->GetDescriptor();

	CHECK( desc.Height == 4 );
	CHECK( desc.Width == 4 );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.SoilTextureLoader.Load.bmp", "[GraphicAPI][SoilTextureLoader]" )
{
	auto rm = CreateResourceManagerWithDefaults();

	TextureLoadInfo loadInfo;

	auto resource = rm->LoadGeneric( "../TestAssets/texture/random-pixels.bmp", &loadInfo, TypeID::get< Texture >() );
	REQUIRE_IS_VALID( resource );

	TexturePtr texture = static_cast<Texture*>(resource.Get().Ptr());
	auto desc = texture->GetDescriptor();

	CHECK( desc.Height == 4 );
	CHECK( desc.Width == 4 );
}







