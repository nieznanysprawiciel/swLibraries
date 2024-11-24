#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestSWMaterialSaver.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialAsset.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialAssetInitData.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialCreator.h"

#include "swGraphicAPI/Assets/MaterialAsset/PhongMaterialData.h"

#include "swGraphicAPI/Loaders/swMaterialLoader/swMaterialLoader.h"

#include "swGraphicAPI/MockAssets/Utils.h"
#include "swGraphicAPI/Tests/TestMaterial/Utils.h"
#include "swCommonLib/Common/Macros/GenerateOperators.h"



using namespace sw;

//====================================================================================//
//			Material test utils	
//====================================================================================//

namespace DirectX {
    GENERATE_RELATIONAL_OPERATORS(DirectX::XMFLOAT3, x, y, z);
    GENERATE_RELATIONAL_OPERATORS(DirectX::XMFLOAT4, x, y, z, w);
}

// ================================ //
//
fs::Path                Translate       ( ResourceManager* rm, fs::Path path )
{
    return rm->GetPathsManager()->Translate( path );
}

//====================================================================================//
//			Test cases	
//====================================================================================//


// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Saver.PS_VS_only", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    MaterialInitData initInfo;
    initInfo.PixelShader = api.LoadPixelShader( "$(TestAssets)/shaders/hlsl/MinimalShader.psh" ).Get();
    initInfo.VertexShader = api.LoadVertexShader( "$(TestAssets)/shaders/hlsl/MinimalShader.vsh" ).Get();
    initInfo.ShadingData = std::make_shared< ShadingModelData< PhongMaterial > >();
    REQUIRE_IS_VALID( initInfo.AutoCreateBuffer( "::Generated/test-material-1", RMLoaderAPI( rm.get() ) ) );

    auto resource = api.CreateAsset< MaterialAsset >( "::Generated/test-material-1", std::move( initInfo ) );
    REQUIRE_IS_VALID( resource );

    SWMaterialLoader().SaveMaterial( Translate( rm.get(), "$(TestWorkingDir)/swMaterialLoader/Material-PS_VS_only.swmat" ), resource.Get().Ptr() );

    auto material = api.Load< MaterialAsset >( "$(TestWorkingDir)/swMaterialLoader/Material-PS_VS_only.swmat", nullptr );
    REQUIRE_IS_VALID( material );

    REQUIRE( material.Get()->GetMaterialBuffer() != nullptr );

    // Validate shaders.
    REQUIRE( material.Get()->GetPixelShader() != nullptr );
    REQUIRE( material.Get()->GetVertexShader() != nullptr );

    CHECK( material.Get()->GetPixelShader()->GetFilePath() == "$(TestAssets)/shaders/hlsl/MinimalShader.psh" );
    CHECK( material.Get()->GetVertexShader()->GetFilePath() == "$(TestAssets)/shaders/hlsl/MinimalShader.vsh" );

    CHECK( material.Get()->GetGeometryShader() == nullptr );
    CHECK( material.Get()->GetTessControlShader() == nullptr );
    CHECK( material.Get()->GetTessEvaluationShader() == nullptr );

    // Validate textures
    for( int i = 0; i < MAX_MATERIAL_TEXTURES; i++ )
        CHECK( material.Get()->GetTexture( i ) == nullptr );

    CHECK( material.Get()->GetDescriptor().ParametricBuffers.size() == 0 );
    CHECK( material.Get()->GetDescriptor().ShadingData.get() != nullptr );

    REQUIRE_IS_VALID( Compare( material, resource ) );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Saver.2Textures", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    MaterialInitData initInfo;
    initInfo.PixelShader = api.LoadPixelShader( "$(TestAssets)/shaders/hlsl/MinimalShader.psh" ).Get();
    initInfo.VertexShader = api.LoadVertexShader( "$(TestAssets)/shaders/hlsl/MinimalShader.vsh" ).Get();
    initInfo.ShadingData = std::make_shared< ShadingModelData< PhongMaterial > >();
    initInfo.Textures[ 0 ] = api.LoadTexture( "$(TestAssets)/texture/random-pixels.jpg" ).Get();
    initInfo.Textures[ 2 ] = api.LoadTexture( "$(TestAssets)/texture/big-lightweight.png" ).Get();
    REQUIRE_IS_VALID( initInfo.AutoCreateBuffer( "::Generated/test-material-2", RMLoaderAPI( rm.get() ) ) );

    auto resource = api.CreateAsset< MaterialAsset >( "::Generated/test-material-2", std::move( initInfo ) );
    REQUIRE_IS_VALID( resource );

    SWMaterialLoader().SaveMaterial( Translate( rm.get(), "$(TestWorkingDir)/swMaterialLoader/Material-2Textures.swmat" ), resource.Get().Ptr() );

    auto material = api.Load< MaterialAsset >( "$(TestWorkingDir)/swMaterialLoader/Material-2Textures.swmat", nullptr );
    REQUIRE_IS_VALID( material );

    CHECK( material.Get()->GetTexture( 0 ) != nullptr );
    CHECK( material.Get()->GetTexture( 2 ) != nullptr );

    CHECK( material.Get()->GetTexture( 1 ) == nullptr );
    CHECK( material.Get()->GetTexture( 3 ) == nullptr );
    CHECK( material.Get()->GetTexture( 4 ) == nullptr );

    CHECK( material.Get()->GetTexture( 0 )->GetFilePath() == "$(TestAssets)/texture/random-pixels.jpg" );
    CHECK( material.Get()->GetTexture( 2 )->GetFilePath() == "$(TestAssets)/texture/big-lightweight.png" );

    REQUIRE_IS_VALID( Compare( material, resource ) );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Saver.ShadingModel", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    MaterialInitData initInfo;
    initInfo.PixelShader = api.LoadPixelShader( "$(TestAssets)/shaders/hlsl/MinimalShader.psh" ).Get();
    initInfo.VertexShader = api.LoadVertexShader( "$(TestAssets)/shaders/hlsl/MinimalShader.vsh" ).Get();
    
    auto shadingModel = std::make_shared< ShadingModelData< PhongMaterial > >();
    initInfo.ShadingData = shadingModel;

    shadingModel->Data.Diffuse = DirectX::XMFLOAT4( 0.2f, 0.3f, 0.4f, 0.5f );
    shadingModel->Data.Ambient = DirectX::XMFLOAT4( 0.1f, 0.14f, 0.17f, 0.19f );
    shadingModel->Data.Emissive = DirectX::XMFLOAT3( 0.32f, 0.35f, 0.47f );
    shadingModel->Data.Specular = DirectX::XMFLOAT4( 0.6f, 0.7f, 0.75f, 0.9f );
    shadingModel->Data.Power = 13.0f;
    
    REQUIRE_IS_VALID( initInfo.AutoCreateBuffer( "::Generated/test-material-3", RMLoaderAPI( rm.get() ) ) );

    auto resource = api.CreateAsset< MaterialAsset >( "::Generated/test-material-3", std::move( initInfo ) );
    REQUIRE_IS_VALID( resource );

    SWMaterialLoader().SaveMaterial( Translate( rm.get(), "$(TestWorkingDir)/swMaterialLoader/Material-ShadingData.swmat" ), resource.Get().Ptr() );

    auto material = api.Load< MaterialAsset >( "$(TestWorkingDir)/swMaterialLoader/Material-ShadingData.swmat", nullptr );
    REQUIRE_IS_VALID( material );

    auto& desc = material.Get()->GetDescriptor();
    REQUIRE( desc.ShadingData->GetShadingModelType() == TypeID::get< PhongMaterial >() );

    auto shadingData = std::static_pointer_cast< ShadingModelData< PhongMaterial > >( desc.ShadingData );

    CHECK( shadingData->Data.Diffuse == DirectX::XMFLOAT4( 0.2f, 0.3f, 0.4f, 0.5f ) );
    CHECK( shadingData->Data.Ambient == DirectX::XMFLOAT4( 0.1f, 0.14f, 0.17f, 0.19f ) );
    CHECK( shadingData->Data.Emissive == DirectX::XMFLOAT3( 0.32f, 0.35f, 0.47f ) );
    CHECK( shadingData->Data.Specular == DirectX::XMFLOAT4( 0.6f, 0.7f, 0.75f, 0.9f ) );
    CHECK( shadingData->Data.Power == 13.0f );

    CHECK( material.Get()->GetMaterialBuffer()->GetElementSize() == shadingData->GetSize() );

    REQUIRE_IS_VALID( Compare( material, resource ) );
}
