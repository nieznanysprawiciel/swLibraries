#pragma once
/**
@file MaterialAssetInitData.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"

#include "ShadingModelData.h"
#include "MaterialInfo.h"

#include <vector>


namespace sw
{

class MaterialAsset;
class nResourceManager;


/**@brief Struct contains data needed to initialize material.
@ingroup Materials*/
struct MaterialInitData : public IAssetCreateInfo
{
    RTTR_ENABLE( IAssetCreateInfo );
public:
    BufferPtr		                        MaterialBuffer;
	VertexShaderPtr			                VertexShader;
	PixelShaderPtr				            PixelShader;
	GeometryShaderPtr			            GeometryShader;
	ControlShaderPtr			            TesselationControlShader;
	EvaluationShaderPtr 			        TesselationEvaluationShader;
	TexturePtr			                    Textures[ MAX_MATERIAL_TEXTURES ];

	std::vector< ParametricBufferInfo >		AdditionalBuffers;		///< Additional buffers which should be provided by scene entity.
	UPtr< ShadingModelBase >				ShadingData;			///< Initializes buffer with shading model data. @see ShadingModelData

public:

// ================================ //
// This should be generated automatically, but Visual studio 2013 can't :(
	MaterialInitData	() {}

public:

    /**@brief Creates buffer using ShadingData.*/
    ReturnResult        AutoCreateBuffer    ( const AssetPath& materialName, RMLoaderAPI& rm );
    AssetPath           DefaultBufferName   ( const AssetPath& materialName ) const;

public:
    // ================================ //
    //
    virtual TypeID		GetAssetType	    () const override { return TypeID::get< MaterialAsset >(); }
};




}	// sw

