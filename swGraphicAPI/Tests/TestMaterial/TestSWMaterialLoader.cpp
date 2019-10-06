#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestSWMaterialLoader.cpp
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
#include "swGraphicAPI/Tests/TestMaterial/Utils.h"
#include "swCommonLib/Common/Macros/GenerateOperators.h"



using namespace sw;


//====================================================================================//
//			Negative tests	
//====================================================================================//

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Format.NoHeader", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/no-header.swmat", nullptr );
    REQUIRE( !material.IsValid() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Format.NoMaterialAsset", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/no-MaterialAsset.swmat", nullptr );
    REQUIRE( !material.IsValid() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Format.InvalidXML", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/invalid-xml.swmat", nullptr );
    REQUIRE( !material.IsValid() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Format.InvalidVersion", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/invalid-version.swmat", nullptr );
    REQUIRE( !material.IsValid() );
}


//====================================================================================//
//			Shaders tests	
//====================================================================================//

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Shaders.NoPixelShader", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/no-ps.swmat", nullptr );
    REQUIRE( !material.IsValid() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Shaders.NoVertexShader", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/no-vs.swmat", nullptr );
    REQUIRE( !material.IsValid() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Shaders.NotExistingPS", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/not-existing-ps.swmat", nullptr );
    REQUIRE( !material.IsValid() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Shaders.NotExistingVS", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/not-existing-vs.swmat", nullptr );
    REQUIRE( !material.IsValid() );
}

// ================================ //
// No <GeometryShader/> key in xml. Loader should produce valid Material.
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Shaders.NoGeometryShaderEntry", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/no-gs-entry.swmat", nullptr );
    REQUIRE_IS_VALID( material );
}


//====================================================================================//
//			Textures	
//====================================================================================//

// ================================ //
// Material file contains one valid texture, but doesn't contains empty <Texture/> entries.
// Loader should produce valid material with one texture under index 0.
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Textures.SingleTextureEntry", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/single-texture-entry.swmat", nullptr );
    REQUIRE_IS_VALID( material );

    CHECK( material.Get()->GetTexture( 0 ) != nullptr );
    CHECK( material.Get()->GetTexture( 0 )->GetFilePath() == "$(TestAssets)/texture/random-pixels.jpg" );
    CHECK( material.Get()->GetTexture( 0 )->GetAssetPath().GetInternalPath() == "" );

    // Validate textures expected to be nullptrs.
    for( int i = 1; i < MAX_MATERIAL_TEXTURES; i++ )
        CHECK( material.Get()->GetTexture( i ) == nullptr );
}

// ================================ //
// Material file contains no <Textures></Textures> entry.
// Loader should produce valid material without textures.
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Textures.NoTexturesEntry", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/no-textures-entry.swmat", nullptr );
    REQUIRE_IS_VALID( material );

    // Validate textures expected to be nullptrs.
    for( int i = 0; i < MAX_MATERIAL_TEXTURES; i++ )
        CHECK( material.Get()->GetTexture( i ) == nullptr );
}

// ================================ //
// File references not existing texture. Loader should produce valid
// material without requested texture. Warning is reported.
TEST_CASE( "GraphicAPI.Loaders.swMaterialLoader.Loader.Textures.NotExistingTexture", "[GraphicAPI][swMaterialLoader]" )
{
    auto rm = CreateResourceManagerWithMaterials();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< MaterialAsset >( "$(MaterialAssets)/not-existing-texture.swmat", nullptr );
    REQUIRE_IS_VALID( material );

    // Validate textures expected to be nullptrs.
    for( int i = 0; i < MAX_MATERIAL_TEXTURES; i++ )
        CHECK( material.Get()->GetTexture( i ) == nullptr );
}
