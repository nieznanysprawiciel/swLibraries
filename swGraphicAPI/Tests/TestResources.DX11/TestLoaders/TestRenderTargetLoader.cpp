#include "swGraphicAPI/Tests/TestResources.DX11/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestRenderTargetLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/Loaders/RenderTargetLoader.h"

#include "swGraphicAPI/MockAssets/GraphicAPI.h"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


using namespace sw;



// ================================ //
// Checks if RenderTargetLoader adds all textures to ResoruceManager correctly.
TEST_CASE( "GraphicAPI.DX11.RenderTargetLoader.Create.ColorDepthStencil", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithDefaults();

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

// ================================ //
// Checks if RenderTargetLoader forwards errors.
TEST_CASE( "GraphicAPI.DX11.RenderTargetLoader.Create.InvalidRT", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithDefaults();

	RenderTargetLoadInfo init;
	init.Height = 0;
	init.Width = 0;
	init.DepthStencilFormat = DepthStencilFormat::DEPTH_STENCIL_FORMAT_D24_UNORM_S8_UINT;
	init.ColorBuffFormat = ResourceFormat::RESOURCE_FORMAT_B8G8R8A8_UNORM;

	auto result = rm->LoadGeneric( "::/ColorDepthStencilRT", &init, TypeID::get< RenderTarget >() );
	REQUIRE( !result.IsValid() );

	CHECK( result.GetError() != nullptr );
}

