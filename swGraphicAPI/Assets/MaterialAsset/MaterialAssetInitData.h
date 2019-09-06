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
	MaterialInitData	( MaterialInitData&& other );
	void operator=		( MaterialInitData&& other );

public:
    // ================================ //
    //
    virtual TypeID		GetAssetType	() const override { return TypeID::get< MaterialAsset >(); }
};



//====================================================================================//
//			Implementation	
//====================================================================================//

#define MOVE_FIELD( param ) param = std::move( other.##param );

// ================================ //
//
inline          MaterialInitData::MaterialInitData  ( MaterialInitData&& other )
{
	MOVE_FIELD( VertexShader );
	MOVE_FIELD( PixelShader );
	MOVE_FIELD( GeometryShader );
	MOVE_FIELD( TesselationControlShader );
	MOVE_FIELD( TesselationEvaluationShader );
	MOVE_FIELD( AdditionalBuffers );
	MOVE_FIELD( ShadingData );

	for( int i = 0; i < MAX_MATERIAL_TEXTURES; ++i )
		Textures[ i ] = std::move( other.Textures[ i ] );
}

// ================================ //
//
inline void		MaterialInitData::operator=         ( MaterialInitData&& other )
{
	MOVE_FIELD( VertexShader );
	MOVE_FIELD( PixelShader );
	MOVE_FIELD( GeometryShader );
	MOVE_FIELD( TesselationControlShader );
	MOVE_FIELD( TesselationEvaluationShader );
	MOVE_FIELD( AdditionalBuffers );
	MOVE_FIELD( ShadingData );

	for( int i = 0; i < MAX_MATERIAL_TEXTURES; ++i )
		Textures[ i ] = std::move( other.Textures[ i ] );
}

}	// sw

