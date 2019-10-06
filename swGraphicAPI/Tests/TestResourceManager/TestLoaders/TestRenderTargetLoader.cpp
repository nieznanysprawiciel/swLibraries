#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestRenderTargetLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/ResourceManager.h"

#include "swGraphicAPI/MockAssets/Utils.h"



using namespace sw;


// ================================ //
// Checks if RenderTargetLoader adds all textures to ResoruceManager correctly.
TEST_CASE( "GraphicAPI.RenderTargetLoader.Create.ColorDepthStencil", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocksAndDefaults();

	RenderTargetLoadInfo init;
	init.Height = 8;
	init.Width = 8;
	init.DepthStencilFormat = DepthStencilFormat::DEPTH_STENCIL_FORMAT_D24_UNORM_S8_UINT;
	init.ColorBuffFormat = ResourceFormat::RESOURCE_FORMAT_B8G8R8A8_UNORM;

	auto result = rm->LoadGeneric( "::/ColorDepthStencilRT", &init, TypeID::get< RenderTarget >() );
	REQUIRE_IS_VALID( result );

	auto loadedRT = result.Get();

	auto rt = rm->Get< RenderTarget >( "::/ColorDepthStencilRT" );
	auto colorTex = rm->Get< Texture >( "::/ColorDepthStencilRT/color" );
	auto depthTex = rm->Get< Texture >( "::/ColorDepthStencilRT/depth" );
	auto stencilTex = rm->Get< Texture >( "::/ColorDepthStencilRT/stencil" );

	CHECK( rt != nullptr );
	CHECK( rt == loadedRT );

	CHECK( colorTex == rt->GetColorBuffer() );
	CHECK( depthTex == rt->GetDepthBuffer() );
	CHECK( stencilTex == rt->GetStencilBuffer() );
}


