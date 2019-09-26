#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestSWMaterialSaver.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/nResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialAsset.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialAssetInitData.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialCreator.h"

#include "swGraphicAPI/Assets/MaterialAsset/PhongMaterialData.h"

#include "swGraphicAPI/Loaders/swMaterialLoader/swMaterialLoader.h"

#include "swGraphicAPI/MockAssets/Utils.h"



using namespace sw;


// ================================ //
//
filesystem::Path        Translate       ( nResourceManager* rm, filesystem::Path path )
{
    return rm->GetPathsManager()->Translate( path );
}


// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Saver.PS_VS_only", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMocksAndDefaults();
    rm->RegisterAssetCreator( MaterialCreator::CreateCreator() );
    rm->RegisterLoader( std::make_shared< SWMaterialLoader >() );
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

    // Validate shaders.
    REQUIRE( material.Get()->GetPixelShader() != nullptr );
    REQUIRE( material.Get()->GetVertexShader() != nullptr );

    CHECK( material.Get()->GetPixelShader()->GetFilePath() == "$(TestAssets)/shaders/hlsl/MinimalShader.psh" );
    CHECK( material.Get()->GetVertexShader()->GetFilePath() == "$(TestAssets)/shaders/hlsl/MinimalShader.vsh" );

    CHECK( material.Get()->GetGeometryShader() == nullptr );
    CHECK( material.Get()->GetTessControlShader() == nullptr );
    CHECK( material.Get()->GetTessEvaluationShader() == nullptr );

    // Validate textures
    for( int i = 0; i < 5; i++ )
        CHECK( material.Get()->GetTexture( i ) == nullptr );

    CHECK( material.Get()->GetDescriptor().ParametricBuffers.size() == 0 );
    CHECK( material.Get()->GetDescriptor().ShadingData.get() != nullptr );
}
