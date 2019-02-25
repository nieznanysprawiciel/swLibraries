#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestAssetsFactory.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Shaders/ShaderCreator.h"
#include "swGraphicAPI/Resources/Shaders/ShaderInitData.h"


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetsFactory.CreateAsset", "[GraphicAPI]" )
{
	AssetsFactory factory;

	ShaderInitData init( ShaderType::VertexShader );

	auto result = factory.CreateAsset( "../TestAssets/shaders/hlsl/MinimalShader.vsh", TypeID::get< VertexShader >(), std::move( init ) );
	REQUIRE( result.IsValid() == true );

	CHECK( result.Get() != nullptr );
}




