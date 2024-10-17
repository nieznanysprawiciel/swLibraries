#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestShaderLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Resources/Shaders/Exceptions/CompilationException.h"

#include "swGraphicAPI/MockAssets/GraphicAPI.h"


using namespace sw;



// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.ShaderLoader.Load.VertexShader", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithDefaults();

	auto resource = rm->LoadGeneric( "$(TestAssets)/shaders/hlsl/MinimalShader.vsh::main", nullptr, TypeID::get< VertexShader >() );
	REQUIRE( resource.IsValid() == true );

	CHECK( resource.Get() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.ShaderLoader.Load.PixelShader", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithDefaults();

	auto resource = rm->LoadGeneric( "$(TestAssets)/shaders/hlsl/MinimalShader.psh::main", nullptr, TypeID::get< PixelShader >() );
	REQUIRE( resource.IsValid() == true );

	CHECK( resource.Get() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.ShaderLoader.Load.ComputeShader", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithDefaults();

	auto resource = rm->LoadGeneric( "$(TestAssets)/shaders/hlsl/MinimalShader.csh::main", nullptr, TypeID::get< ComputeShader >() );
	REQUIRE( resource.IsValid() == true );

	CHECK( resource.Get() != nullptr );
}

// ================================ //
// Loader should forward compilation errors from shaders.
TEST_CASE( "GraphicAPI.DX11.ShaderLoader.Load.VertexShader.CompilationFailed", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithDefaults();

	auto resource = rm->LoadGeneric( "$(TestAssets)/shaders/hlsl/NotCompiling.vsh::main", nullptr, TypeID::get< VertexShader >() );
	REQUIRE( resource.IsValid() == false );

	CHECK( resource.GetError() != nullptr );
	CHECK( resource.GetError()->get_type() == TypeID::get< CompilationException >() );
}

