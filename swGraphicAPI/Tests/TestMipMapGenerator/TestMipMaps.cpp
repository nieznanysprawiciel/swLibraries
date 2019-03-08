#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestMipMaps.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/AssetCreators/Textures/MipMapGenerator.h"
#include "swGraphicAPI/ImageGenerators/CheckerboardGenerator.h"

using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.TextureCreator.MipMapGenerator.Generate.ImagePowerOf2", "[GraphicAPI]" )
{
	CheckerboardGenerator checker( 8, 8 );
	auto buffer = checker.Generate();
	auto startSize = buffer.GetSize();

	TextureInfo texInfo;
	texInfo.GenerateMipMaps = true;
	texInfo.MipMapFilter = MipMapFilter::Box;
	texInfo.Format = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;
	texInfo.TextureWidth = 8;
	texInfo.TextureHeight = 8;

	MipMapGenerator mipmap;
	auto newBuffer = mipmap.Generate( buffer, texInfo ).Get();

	CHECK( texInfo.TextureWidth == 8 );
	CHECK( texInfo.TextureHeight == 8 );
	CHECK( texInfo.MipMapLevels == 4 );
	
	CHECK( newBuffer.GetSize() == 4 * (8*8 + 4*4 + 2*2 + 1 ) );
}


// ================================ //
// 
TEST_CASE( "GraphicAPI.TextureCreator.MipMapGenerator.Generate.ImageNotPowerOf2", "[GraphicAPI]" )
{
	CheckerboardGenerator checker( 10, 10 );
	auto buffer = checker.Generate();
	auto startSize = buffer.GetSize();

	TextureInfo texInfo;
	texInfo.GenerateMipMaps = true;
	texInfo.MipMapFilter = MipMapFilter::Box;
	texInfo.Format = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;
	texInfo.TextureWidth = 10;
	texInfo.TextureHeight = 10;

	MipMapGenerator mipmap;
	auto newBuffer = mipmap.Generate( buffer, texInfo ).Get();

	CHECK( texInfo.TextureWidth == 16 );
	CHECK( texInfo.TextureHeight == 16 );
	CHECK( texInfo.MipMapLevels == 5 );
	
	CHECK( newBuffer.GetSize() == 4 * ( 16*16 + 8*8 + 4*4 + 2*2 + 1 ) );
}
