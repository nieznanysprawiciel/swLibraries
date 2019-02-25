/**
@file TestShaderCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/External/Catch/catch.hpp"

#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Shaders/ShaderCreator.h"
#include "swGraphicAPI/Resources/Shaders/ShaderInitData.h"


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.ShaderCreator.VertexShader.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;

	ShaderInitData init( ShaderType::VertexShader );

	auto result = factory.CreateAsset( "../TestAssets/shaders/hlsl/MinimalShader.vsh", TypeID::get< VertexShader >(), std::move( init ) );

	if( !result.IsValid() )
	{
		INFO( result.GetErrorReason() );
		REQUIRE( result.IsValid() == true );
	}

	CHECK( result.Get() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ShaderCreator.PixelShader.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;

	ShaderInitData init( ShaderType::PixelShader );

	auto result = factory.CreateAsset( "../TestAssets/shaders/hlsl/MinimalShader.psh", TypeID::get< PixelShader >(), std::move( init ) );

	if( !result.IsValid() )
	{
		INFO( result.GetErrorReason() );
		REQUIRE( result.IsValid() == true );
	}

	CHECK( result.Get() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ShaderCreator.ComputeShader.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;

	ShaderInitData init( ShaderType::ComputeShader );

	auto result = factory.CreateAsset( "../TestAssets/shaders/hlsl/MinimalShader.csh", TypeID::get< ComputeShader >(), std::move( init ) );

	if( !result.IsValid() )
	{
		INFO( result.GetErrorReason() );
		REQUIRE( result.IsValid() == true );
	}

	CHECK( result.Get() != nullptr );
}



