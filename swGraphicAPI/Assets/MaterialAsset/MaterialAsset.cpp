/**
@file MaterialAsset.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Assets/MaterialAsset/stdafx.h"

#include "MaterialAsset.h"

#include "swCommonLib/Common/Converters.h"



RTTR_REGISTRATION
{


	rttr::registration::class_< sw::ParametricBufferInfo >( "ParametricBufferInfo" )
		.property( "ShaderType", &sw::ParametricBufferInfo::ShaderType )
		.property( "BufferSize", &sw::ParametricBufferInfo::BufferSize )
		.property( "BufferType", &sw::ParametricBufferInfo::GetBufferType, &sw::ParametricBufferInfo::SetBufferType );

	rttr::registration::class_< sw::MaterialInfo >( "MaterialInfo" )
		.property( "ParametricBuffers", &sw::MaterialInfo::ParametricBuffers )
		.property( "ShadingData", &sw::MaterialInfo::ShadingData );

	rttr::registration::class_< sw::MaterialAsset >( "MaterialAsset" )
		.property( "VertexShader", &sw::MaterialAsset::m_vertexShader )
		.property( "PixelShader", &sw::MaterialAsset::m_pixelShader )
		.property( "GeometryShader", &sw::MaterialAsset::m_geometryShader )
		.property( "TesselationControlShader", &sw::MaterialAsset::m_controlShader )
		.property( "TesselationEvaluationShader", &sw::MaterialAsset::m_evaluationShader )
		.property_readonly( "DiffuseTexture", &sw::MaterialAsset::GetTexture1 )
		.property_readonly( "SpecularTexture", &sw::MaterialAsset::GetTexture2 )
		.property_readonly( "AmbientTexture", &sw::MaterialAsset::GetTexture3 )
		.property_readonly( "NormalMap", &sw::MaterialAsset::GetTexture4 )
		.property_readonly( "DisplacementMap", &sw::MaterialAsset::GetTexture5 )
		.property_readonly( "Texture6", &sw::MaterialAsset::GetTexture6 )
		.property_readonly( "Texture7", &sw::MaterialAsset::GetTexture7 )
		.property_readonly( "Texture8", &sw::MaterialAsset::GetTexture8 )
		//.property( "Textures", &MaterialAsset::m_textures )
		.property( "Descriptor", &sw::MaterialAsset::m_descriptor ) BIND_AS_PTR;

}


namespace sw
{


// ================================ //
//
MaterialAsset::MaterialAsset        ( AssetPath path, MaterialCreateData&& initData )
	: Resource( std::move( path ) )
	, m_materialBuffer( std::move( initData.MaterialBuffer ) )
	, m_vertexShader( std::move( initData.Data.VertexShader ) )
	, m_pixelShader( std::move( initData.Data.PixelShader ) )
	, m_geometryShader( std::move( initData.Data.GeometryShader ) )
	, m_evaluationShader( std::move( initData.Data.TesselationEvaluationShader ) )
	, m_controlShader( std::move( initData.Data.TesselationControlShader ) )
	, m_descriptor( std::move( initData.Data.AdditionalBuffers ), std::move( initData.Data.ShadingData ) )
{
	for( int i = 0; i < MAX_MATERIAL_TEXTURES; ++i )
	{
		m_textures[ i ] = std::move( initData.Data.Textures[ i ] );
	}
}

// ================================ //
//
MaterialAsset::~MaterialAsset       ()
{}



}	// sw

