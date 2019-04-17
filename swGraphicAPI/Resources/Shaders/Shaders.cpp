/**
@file Shaders.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"


#include "ShaderInitData.h"
#include "LayoutInitData.h"
#include "InputLayout.h"
#include "Shaders.h"


using namespace sw;


RTTR_REGISTRATION
{

	// Shader
	rttr::registration::class_< ShaderInputLayout >( "sw::ShaderInputLayout" );
	rttr::registration::class_< IShader >( "sw::IShader" )
		.property_readonly( "MainFunction", &IShader::GetShaderEntry );

	rttr::registration::class_< PixelShader >( "sw::PixelShader" );
	rttr::registration::class_< VertexShader >( "sw::VertexShader" );

}


namespace sw
{

// ================================ //
//
TypeID			ShaderInitData::GetAssetType() const
{
	switch( Type )
	{
		case ShaderType::VertexShader:
			return TypeID::get< VertexShader >();
		case ShaderType::PixelShader:
			return TypeID::get< PixelShader >();
		case ShaderType::GeometryShader:
			return TypeID::get< GeometryShader >();
		case ShaderType::TesselationControlShader:
			return TypeID::get< ControlShader >();
		case ShaderType::TesselationEvaluationShader:
			return TypeID::get< EvaluationShader >();
		case ShaderType::ComputeShader:
			return TypeID::get< ComputeShader >();
		default:
			return TypeID::get_by_name( "" );
			break;
	}
}


}	// sw



