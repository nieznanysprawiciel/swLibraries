#include "swGraphicAPI/Tests/TestResources.DX11/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestTextureCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Textures/RenderTargetCreator.h"
#include "swGraphicAPI/Resources/Textures/RenderTarget.h"

#include "swGraphicAPI/MockAssets/Utils.h"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


using namespace sw;



// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.RenderTargetCreator.Create.ColorDepth", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	RenderTargetDescriptor init;
	init.Height = 8;
	init.Width = 8;
	init.DepthStencilFormat = DepthStencilFormat::DEPTH_STENCIL_FORMAT_D16_UNORM;
	init.ColorBuffFormat = ResourceFormat::RESOURCE_FORMAT_B8G8R8A8_UNORM;


	auto result = factory.CreateAsset( "::/RenderTarget/ColorDepth", TypeID::get< RenderTarget >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );

	RenderTarget* rt = static_cast< RenderTarget* >( result.Get() );
	CHECK( rt->GetColorBuffer() != nullptr );
	CHECK( rt->GetDepthBuffer() != nullptr );
	CHECK( rt->GetStencilBuffer() == nullptr );
}


// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.RenderTargetCreator.Create.ColorDepthStencil", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	RenderTargetDescriptor init;
	init.Height = 8;
	init.Width = 8;
	init.DepthStencilFormat = DepthStencilFormat::DEPTH_STENCIL_FORMAT_D24_UNORM_S8_UINT;
	init.ColorBuffFormat = ResourceFormat::RESOURCE_FORMAT_B8G8R8A8_UNORM;


	auto result = factory.CreateAsset( "::/RenderTarget/ColorDepthStencil", TypeID::get< RenderTarget >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );

	RenderTarget* rt = static_cast< RenderTarget* >( result.Get() );
	CHECK( rt->GetColorBuffer() != nullptr );
	CHECK( rt->GetDepthBuffer() != nullptr );
	CHECK( rt->GetStencilBuffer() != nullptr );
}


