#pragma once
/**
@file Utils.h
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



namespace sw
{

// ================================ //
//
inline ReturnResult            Compare         ( MaterialAssetPtr mat, MaterialAssetPtr reference )
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
    for( int i = 0; i < MAX_MATERIAL_TEXTURES; i++ )
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

    return Success::True;
}

// ================================ //
//
inline std::unique_ptr< ResourceManager >			CreateResourceManagerWithMaterials	()
{
    auto rm = CreateResourceManagerWithMocksAndDefaults();

    rm->RegisterAssetCreator( MaterialCreator::CreateCreator() );
    rm->RegisterLoader( std::make_shared< SWMaterialLoader >() );
    rm->RegisterLoader( std::make_shared< SoilTextureLoader >() );

    auto pm = rm->GetPathsManager();
    pm->RegisterAlias( "$(MaterialAssets)", "$(TestAssets)/material/" );

    return std::move( rm );
}


}	// sw

