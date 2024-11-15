#include "swGraphicAPI/Tests/TestResourceManager/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestAssetsFactory.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Shaders/ShaderCreator.h"
#include "swGraphicAPI/Resources/Shaders/ShaderInitData.h"

#include "swGraphicAPI/MockAssets/Utils.h"
#include <swGraphicAPI/MockAssets/GraphicAPI.h>


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

// ================================ //
//
AssetPath        Translate(ResourceManager* rm, fs::Path path)
{
	auto translatePath = rm->GetPathsManager()->Translate(path);
	return AssetPath(translatePath, "");
}


//====================================================================================//
//			Tests	
//====================================================================================//

// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetsFactory.CreateAsset", "[GraphicAPI]" )
{
	AssetsFactory factory;
	ShaderInitData init( ShaderType::VertexShader );

	auto rm = CreateResourceManagerWithDefaults();
	auto result = factory.CreateAsset(Translate(rm.get(), "$(TestAssets)/shaders/hlsl/MinimalShader.vsh"), TypeID::get< VertexShader >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

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



