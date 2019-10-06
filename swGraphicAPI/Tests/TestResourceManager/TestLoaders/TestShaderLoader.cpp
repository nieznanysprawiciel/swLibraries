#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestShaderLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/ResourceManager.h"

#include "swGraphicAPI/MockAssets/Utils.h"

#include "swCommonLib/Common/Exceptions/Common/FileNotFoundException.h"


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.ShaderLoader.FileDoesntExists", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocksAndDefaults();

	auto resource = rm->LoadGeneric( "../TestAssets/shaders/example-notexists.vsh::main", nullptr, TypeID::get< VertexShader >() );
	REQUIRE( resource.IsValid() == false );

	CHECK( resource.GetError() != nullptr );
	CHECK( resource.GetError()->get_type() == TypeID::get< FileNotFoundException >() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ShaderLoader.Load.VertexShader", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocksAndDefaults();

	auto resource = rm->LoadGeneric( "../TestAssets/shaders/hlsl/MinimalShader.vsh::main", nullptr, TypeID::get< VertexShader >() );
	REQUIRE( resource.IsValid() == true );

	CHECK( resource.Get() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ShaderLoader.Load.PixelShader", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocksAndDefaults();

	auto resource = rm->LoadGeneric( "../TestAssets/shaders/hlsl/MinimalShader.psh::main", nullptr, TypeID::get< PixelShader >() );
	REQUIRE( resource.IsValid() == true );

	CHECK( resource.Get() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.ShaderLoader.Load.ComputeShader", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocksAndDefaults();

	auto resource = rm->LoadGeneric( "../TestAssets/shaders/hlsl/MinimalShader.csh::main", nullptr, TypeID::get< ComputeShader >() );
	REQUIRE( resource.IsValid() == true );

	CHECK( resource.Get() != nullptr );
}
