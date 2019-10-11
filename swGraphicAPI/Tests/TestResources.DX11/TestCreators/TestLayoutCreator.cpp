#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestLayoutCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Shaders/LayoutCreator.h"
#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"



using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.LayoutCreator.Create.Semantic.Position", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	InputLayoutDescriptor init;
	init.AddEntry( AttributeSemantic::Position, ResourceFormat::RESOURCE_FORMAT_R32G32B32_FLOAT, 0 );


	auto result = factory.CreateAsset( "::/Layout", TypeID::get< ShaderInputLayout >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.LayoutCreator.Create.Semantic.Blending", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	InputLayoutDescriptor init;
	init.AddEntry( AttributeSemantic::Position, ResourceFormat::RESOURCE_FORMAT_R32G32B32_FLOAT, 0 );
	init.AddEntry( AttributeSemantic::BlendIndicies, ResourceFormat::RESOURCE_FORMAT_B8G8R8A8_UNORM, 12 );
	init.AddEntry( AttributeSemantic::BlendWeights, ResourceFormat::RESOURCE_FORMAT_R32G32B32A32_FLOAT, 16 );

	auto result = factory.CreateAsset( "::/Layout", TypeID::get< ShaderInputLayout >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.LayoutCreator.Create.Semantic.Color", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	InputLayoutDescriptor init;
	init.AddEntry( AttributeSemantic::Position, ResourceFormat::RESOURCE_FORMAT_R32G32B32_FLOAT, 0 );
	init.AddEntry( AttributeSemantic::Color, ResourceFormat::RESOURCE_FORMAT_R32G32B32A32_FLOAT, 12 );

	auto result = factory.CreateAsset( "::/Layout", TypeID::get< ShaderInputLayout >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.LayoutCreator.Create.Semantic.Coordinates", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	InputLayoutDescriptor init;
	init.AddEntry( AttributeSemantic::Position, ResourceFormat::RESOURCE_FORMAT_R32G32B32_FLOAT, 0 );
	init.AddEntry( AttributeSemantic::Texcoord, ResourceFormat::RESOURCE_FORMAT_R32G32_FLOAT, 12 );

	auto result = factory.CreateAsset( "::/Layout", TypeID::get< ShaderInputLayout >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.LayoutCreator.Create.Semantic.NormalBinormalTangent", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	InputLayoutDescriptor init;
	init.AddEntry( AttributeSemantic::Position, ResourceFormat::RESOURCE_FORMAT_R32G32B32_FLOAT, 0 );
	init.AddEntry( AttributeSemantic::Normal, ResourceFormat::RESOURCE_FORMAT_R32G32B32_FLOAT, 12 );
	init.AddEntry( AttributeSemantic::Tangent, ResourceFormat::RESOURCE_FORMAT_R32G32B32_FLOAT, 24 );
	init.AddEntry( AttributeSemantic::Binormal, ResourceFormat::RESOURCE_FORMAT_R32G32B32_FLOAT, 24 );

	auto result = factory.CreateAsset( "::/Layout", TypeID::get< ShaderInputLayout >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.LayoutCreator.Create.Semantic.PointSize", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	InputLayoutDescriptor init;
	init.AddEntry( AttributeSemantic::Position, ResourceFormat::RESOURCE_FORMAT_R32G32B32_FLOAT, 0 );
	init.AddEntry( AttributeSemantic::PointSize, ResourceFormat::RESOURCE_FORMAT_R32_FLOAT, 12 );

	auto result = factory.CreateAsset( "::/Layout", TypeID::get< ShaderInputLayout >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );
}

