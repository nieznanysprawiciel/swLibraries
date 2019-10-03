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

//====================================================================================//
//			Material test utils	
//====================================================================================//

// ================================ //
//
ReturnResult            Compare         ( MaterialAssetPtr mat, MaterialAssetPtr reference )
{
    if( mat->GetMaterialBuffer()->GetElementSize() != reference->GetMaterialBuffer()->GetElementSize() )
        return "MaterialBuffer sizes differ";

    if( mat->GetMaterialBuffer()->GetElementCount() != reference->GetMaterialBuffer()->GetElementCount() )
        return "MaterialBuffer elements count differs";

    // Compare shaders.
    if( mat->GetVertexShader() != reference->GetVertexShader() )
        return "VertexShader differs";

    if( mat->GetPixelShader() != reference->GetPixelShader() )
        return "PixelShader differs";

    if( mat->GetGeometryShader() != reference->GetGeometryShader() )
        return "GeometryShader differs";

    if( mat->GetTessControlShader() != reference->GetTessControlShader() )
        return "ControlShader differs";

    if( mat->GetTessEvaluationShader() != reference->GetTessEvaluationShader() )
        return "EvaluationShader differs";

    // Compare textures.
    for( int i = 0; i < 5; i++ )
    {
        if( mat->GetTexture( i ) != reference->GetTexture( i ) )
            return "Texture on index " + Convert::ToString( i ) + " differes.";
    }

    if( TypeID::get( mat->GetDescriptor().ShadingData.get() ) != TypeID::get( reference->GetDescriptor().ShadingData.get() ) )
        return "Type of ShadingData differs";

    if( mat->GetDescriptor().ParametricBuffers.size() != reference->GetDescriptor().ParametricBuffers.size() )
        return "Sizes of ParametricBuffers differ";

    for( Size i = 0; i < mat->GetDescriptor().ParametricBuffers.size(); i++ )
    {
        if( mat->GetDescriptor().ParametricBuffers[ i ] != reference->GetDescriptor().ParametricBuffers[ i ] )
            return "Parametric buffers differ on index " + Convert::ToString( i );
    }

    return Result::Success;
}


// ================================ //
//
filesystem::Path        Translate       ( nResourceManager* rm, filesystem::Path path )
{
    return rm->GetPathsManager()->Translate( path );
}

// ================================ //
//
std::unique_ptr< nResourceManager >			CreateResourceManagerWithMaterials	()
{
    auto rm = CreateResourceManagerWithMocksAndDefaults();

    rm->RegisterAssetCreator( MaterialCreator::CreateCreator() );
    rm->RegisterLoader( std::make_shared< SWMaterialLoader >() );
    rm->RegisterLoader( std::make_shared< SoilTextureLoader >() );

    return std::move( rm );
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
    for( int i = 0; i < 5; i++ )
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
