#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestShaderCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Shaders/ShaderCreator.h"
#include "swGraphicAPI/Resources/Shaders/ShaderInitData.h"

#include "swCommonLib/System/File.h"


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.VertexShader.Create", "[GraphicAPI]" )
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
// Not compiling shader creation should return error message.
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.VertexShader.Create.CompilationFailed", "[GraphicAPI]" )
{
	AssetsFactory factory;

	ShaderInitData init( ShaderType::VertexShader );

	auto result = factory.CreateAsset( "../TestAssets/shaders/hlsl/NotCompiling.vsh", TypeID::get< VertexShader >(), std::move( init ) );

	REQUIRE( result.IsValid() == false );
	CHECK( result.GetError() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.PixelShader.Create", "[GraphicAPI]" )
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
// Not compiling shader creation should return error message.
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.PixelShader.Create.CompilationFailed", "[GraphicAPI]" )
{
	AssetsFactory factory;

	ShaderInitData init( ShaderType::PixelShader );

	auto result = factory.CreateAsset( "../TestAssets/shaders/hlsl/NotCompiling.psh", TypeID::get< PixelShader >(), std::move( init ) );

	REQUIRE( result.IsValid() == false );
	CHECK( result.GetError() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.ComputeShader.Create", "[GraphicAPI]" )
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


// ================================ //
// Not compiling shader creation should return error message.
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.ComputeShader.Create.CompilationFailed", "[GraphicAPI]" )
{
	AssetsFactory factory;

	ShaderInitData init( ShaderType::ComputeShader );

	auto result = factory.CreateAsset( "../TestAssets/shaders/hlsl/NotCompiling.csh", TypeID::get< ComputeShader >(), std::move( init ) );

	REQUIRE( result.IsValid() == false );
	CHECK( result.GetError() != nullptr );
}

// ================================ //
// Checks shader generation from ShaderCodeInitData.
// This creates shader from source code in string. Tested only for one shader type.
// Rest left for intefrations tests of ShaderLoader.
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.ComputeShader.Create.FromCode", "[GraphicAPI]" )
{
	AssetsFactory factory;

	ShaderCodeInitData init( ShaderType::VertexShader );
	init.SourceCode = filesystem::File::Load( "../TestAssets/shaders/hlsl/MinimalShader.vsh" );

	auto result = factory.CreateAsset( "../TestAssets/shaders/hlsl/MinimalShader.vsh", TypeID::get< VertexShader >(), std::move( init ) );

	if( !result.IsValid() )
	{
		INFO( result.GetErrorReason() );
		REQUIRE( result.IsValid() == true );
	}

	CHECK( result.Get() != nullptr );
}
