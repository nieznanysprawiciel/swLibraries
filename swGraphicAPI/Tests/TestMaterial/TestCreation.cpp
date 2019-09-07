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

#include "swGraphicAPI/Assets/MaterialAsset/PhongMaterialData.h"

#include "swGraphicAPI/MockAssets/Utils.h"



using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.Assets.Material.Creation.PS_VS_only", "[GraphicAPI][SoilTextureLoader]" )
{
    auto rm = CreateResourceManagerWithMocksAndDefaults();
    rm->RegisterAssetCreator( MaterialCreator::CreateCreator() );
    auto api = ResourceManagerAPI( rm.get() );

    MaterialInitData initInfo;
    initInfo.PixelShader = api.LoadPixelShader( "$(TestAssets)/shaders/hlsl/MinimalShader.psh" ).Get();
    initInfo.VertexShader = api.LoadVertexShader( "$(TestAssets)/shaders/hlsl/MinimalShader.vsh" ).Get();
    initInfo.ShadingData = std::make_shared< ShadingModelData< PhongMaterial > >();
    REQUIRE_IS_VALID( initInfo.AutoCreateBuffer( "::Generated/test-material-1", rm.get() ) );

    auto resource = api.CreateAsset< MaterialAsset >( "::Generated/test-material-1", std::move( initInfo ) );
    REQUIRE_IS_VALID( resource );

    auto material = resource.Get();

    CHECK( material->GetMaterialBuffer() != nullptr );
    CHECK( material->GetPixelShader() != nullptr );
    CHECK( material->GetVertexShader() != nullptr );
    CHECK( material->GetGeometryShader() == nullptr );
    CHECK( material->GetTessControlShader() == nullptr );
    CHECK( material->GetTessEvaluationShader() == nullptr );

    CHECK( material->GetTexture( 0 ) == nullptr );
    CHECK( material->GetTexture( 1 ) == nullptr );
    CHECK( material->GetTexture( 2 ) == nullptr );
    CHECK( material->GetTexture( 3 ) == nullptr );
    CHECK( material->GetTexture( 4 ) == nullptr );

    CHECK( material->GetAssetPath() == "::Generated/test-material-1" );
    CHECK( material->GetDescriptor().ShadingData->GetShadingModelType() == TypeID::get< PhongMaterial >() );
}

// ================================ //
// AutoCreateBuffer should return invalid ReturnResult if ShadingModel was nullptr.
TEST_CASE( "GraphicAPI.Assets.Material.Creation.AutoCreateBuffer.NullptrShadingModel", "[GraphicAPI][SoilTextureLoader]" )
{
    auto rm = CreateResourceManagerWithMocksAndDefaults();
    rm->RegisterAssetCreator( MaterialCreator::CreateCreator() );

    MaterialInitData initInfo;
    auto result = initInfo.AutoCreateBuffer( "::Generated/test-material-1", rm.get() );
    REQUIRE_FALSE( result.IsValid() );
}


