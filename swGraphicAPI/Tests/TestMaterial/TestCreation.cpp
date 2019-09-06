#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestCreation.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/nResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialAsset.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialAssetInitData.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialCreator.h"

#include "swGraphicAPI/MockAssets/Utils.h"



using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.Assets.Material.Creation.", "[GraphicAPI][SoilTextureLoader]" )
{
    auto rm = CreateResourceManagerWithMocksAndDefaults();
    rm->RegisterAssetCreator( MaterialCreator::CreateCreator() );
    auto api = ResourceManagerAPI( rm.get() );

    MaterialInitData initInfo;
    initInfo.PixelShader = api.LoadPixelShader( "$(TestAssets)/shaders/hlsl/MinimalShader.psh" ).Get();
    initInfo.VertexShader = api.LoadVertexShader( "$(TestAssets)/shaders/hlsl/MinimalShader.vsh" ).Get();

    auto resource = api.CreateAsset< MaterialAsset >( "::Generated/test-material-1", std::move( initInfo ) );
    REQUIRE_IS_VALID( resource );

    
}




