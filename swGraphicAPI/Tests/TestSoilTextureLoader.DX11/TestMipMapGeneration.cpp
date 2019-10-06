#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestMipMapsGeneration.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/Loaders/TextureLoadInfo.h"

#include "swGraphicAPI/MockAssets/GraphicAPI.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


using namespace sw;




// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.SoilTextureLoader.Load.GenerateMipMaps", "[GraphicAPI][SoilTextureLoader]" )
{
	auto rm = CreateRMWithDefaultsSoil();

	TextureLoadInfo loadInfo;
	loadInfo.MipMaps.GenerateMipMaps = true;
	loadInfo.MipMaps.Filter = MipMapFilter::Box;

	auto resource = rm->LoadGeneric( "../TestAssets/texture/random-pixels.png", &loadInfo, TypeID::get< Texture >() );
	REQUIRE_IS_VALID( resource );

	TexturePtr texture = static_cast< Texture* >( resource.Get().Ptr() );
	auto desc = texture->GetDescriptor();

	CHECK( desc.Height == 4 );
	CHECK( desc.Width == 4 );

	CHECK( desc.GenerateMipMaps == true );
	CHECK( desc.MipMapLevels == 3 );
}


