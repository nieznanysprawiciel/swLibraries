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
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"

#include "swGraphicAPI/MockAssets/GraphicAPI.h"


using namespace sw;


AssetPath        Translate(ResourceManager* rm, filesystem::Path path)
{
	auto translatePath = rm->GetPathsManager()->Translate(path);
	return AssetPath(translatePath, "");
}


// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.VertexShader.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	ShaderInitData init( ShaderType::VertexShader );

	auto rm = CreateResourceManagerWithDefaults();
	auto result = factory.CreateAsset( Translate(rm.get(), "$(TestAssets)/shaders/hlsl/MinimalShader.vsh"), TypeID::get< VertexShader >(), std::move(init));
	REQUIRE_IS_VALID( result );

	CHECK( result.Get() != nullptr );
}

// ================================ //
// Not compiling shader creation should return error message.
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.VertexShader.Create.CompilationFailed", "[GraphicAPI]" )
{
	AssetsFactory factory;
	ShaderInitData init( ShaderType::VertexShader );

	auto rm = CreateResourceManagerWithDefaults();
	auto result = factory.CreateAsset(Translate(rm.get(), "$(TestAssets)/shaders/hlsl/NotCompiling.vsh"), TypeID::get< VertexShader >(), std::move( init ) );

	REQUIRE( result.IsValid() == false );
	CHECK( result.GetError() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.PixelShader.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	ShaderInitData init( ShaderType::PixelShader );

	auto rm = CreateResourceManagerWithDefaults();
	auto result = factory.CreateAsset(Translate(rm.get(), "$(TestAssets)/shaders/hlsl/MinimalShader.psh"), TypeID::get< PixelShader >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	CHECK( result.Get() != nullptr );
}

// ================================ //
// Not compiling shader creation should return error message.
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.PixelShader.Create.CompilationFailed", "[GraphicAPI]" )
{
	AssetsFactory factory;
	ShaderInitData init( ShaderType::PixelShader );

	auto rm = CreateResourceManagerWithDefaults();
	auto result = factory.CreateAsset(Translate(rm.get(), "$(TestAssets)/shaders/hlsl/NotCompiling.psh"), TypeID::get< PixelShader >(), std::move( init ) );

	REQUIRE( result.IsValid() == false );
	CHECK( result.GetError() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.ComputeShader.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	ShaderInitData init( ShaderType::ComputeShader );

	auto rm = CreateResourceManagerWithDefaults();
	auto result = factory.CreateAsset(Translate(rm.get(), "$(TestAssets)/shaders/hlsl/MinimalShader.csh"), TypeID::get< ComputeShader >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	CHECK( result.Get() != nullptr );
}


// ================================ //
// Not compiling shader creation should return error message.
TEST_CASE( "GraphicAPI.DX11.ShaderCreator.ComputeShader.Create.CompilationFailed", "[GraphicAPI]" )
{
	AssetsFactory factory;
	ShaderInitData init( ShaderType::ComputeShader );

	auto rm = CreateResourceManagerWithDefaults();
	auto result = factory.CreateAsset(Translate(rm.get(), "$(TestAssets)/shaders/hlsl/NotCompiling.csh"), TypeID::get< ComputeShader >(), std::move( init ) );

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

	auto rm = CreateResourceManagerWithDefaults();
    auto assetPath = Translate(rm.get(), "$(TestAssets)/shaders/hlsl/MinimalShader.vsh");
	auto path = assetPath.GetFile();

	init.SourceCode = filesystem::File::Load( path );

	auto result = factory.CreateAsset(assetPath, TypeID::get< VertexShader >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	CHECK( result.Get() != nullptr );
}
