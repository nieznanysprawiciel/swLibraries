#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestTextureCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Textures/TextureCreator.h"
#include "swGraphicAPI/Resources/Textures/TextureInitData.h"

#include "swGraphicAPI/ImageGenerators/CheckerboardGenerator.h"

#include "swCommonLib/Common/Buffers/BufferTyped.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"

using namespace sw;





// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.TextureCreator.Create.GenerateMipmaps", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	CheckerboardGenerator checker( 8, 8 );
	auto buffer = checker.Generate();

	TextureInitData init( std::move( buffer ) );
	init.Height = 8;
	init.Width = 8;
	init.GenerateMipMaps = true;
	init.MipMapFilter = MipMapFilter::Box;
	init.Format = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;

	auto result = factory.CreateAsset( "::/Texture/Checkerboard/Mipmaps", TypeID::get< Texture >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );

	Texture* textureRes = static_cast< Texture* >( result.Get() );

	CHECK( textureRes->GetDescriptor().MipMapLevels == 4 );
	CHECK( textureRes->GetDescriptor().Width == 8 );
	CHECK( textureRes->GetDescriptor().Height == 8 );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.TextureCreator.Create.NoMipmaps", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	CheckerboardGenerator checker( 8, 8 );
	auto buffer = checker.Generate();

	TextureInitData init( std::move( buffer ) );
	init.Height = 8;
	init.Width = 8;
	init.GenerateMipMaps = false;
	init.Format = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;

	auto result = factory.CreateAsset( "::/Texture/Checkerboard/NoMipmaps", TypeID::get< Texture >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );

	Texture* textureRes = static_cast< Texture* >( result.Get() );

	CHECK( textureRes->GetDescriptor().MipMapLevels == 1 );
	CHECK( textureRes->GetDescriptor().Width == 8 );
	CHECK( textureRes->GetDescriptor().Height == 8 );
}

