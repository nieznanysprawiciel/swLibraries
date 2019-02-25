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

//====================================================================================//
//			Helpers	
//====================================================================================//

// ================================ //
//
class FakeResource : public Resource
{
	RTTR_ENABLE( Resource );
};

// ================================ //
//
struct FakeResourceInitData : public IAssetCreateInfo
{
	RTTR_ENABLE( IAssetCreateInfo );

public:

	virtual TypeID		GetAssetType		() const override
	{
		return TypeID::get< FakeResource >();
	}
};



//====================================================================================//
//			Tests	
//====================================================================================//

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

// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetsFactory.CreateAsset.NotRegisteredCreator", "[GraphicAPI]" )
{
	AssetsFactory factory;
	FakeResourceInitData init;

	auto result = factory.CreateAsset( "Fake", TypeID::get< FakeResource >(), std::move( init ) );
	REQUIRE( result.IsValid() == false );
	CHECK( result.GetError() != nullptr );
}



