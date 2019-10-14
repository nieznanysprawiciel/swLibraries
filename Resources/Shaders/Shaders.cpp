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
	rttr::registration::class_< ShaderInputLayout >( "sw::ShaderInputLayout" )
        .property_readonly( "Descriptor", &sw::ShaderInputLayout::GetDescriptor );

    rttr::registration::class_< IShader >( "sw::IShader" );

	rttr::registration::class_< PixelShader >( "sw::PixelShader" );
	rttr::registration::class_< VertexShader >( "sw::VertexShader" );

}


namespace sw
{

// ================================ //
//
TypeID			ShaderInitData::GetAssetType		() const
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

// ================================ //
//
ShaderType		ShaderInitData::GetFromTypeID		( TypeID type )
{
	if( type == TypeID::get< VertexShader >() )
		return ShaderType::VertexShader;
	if( type == TypeID::get< PixelShader >() )
		return ShaderType::PixelShader;
	if( type == TypeID::get< GeometryShader >() )
		return ShaderType::GeometryShader;
	if( type == TypeID::get< ControlShader >() )
		return ShaderType::TesselationControlShader;
	if( type == TypeID::get< EvaluationShader >() )
		return ShaderType::TesselationEvaluationShader;
	if( type == TypeID::get< ComputeShader >() )
		return ShaderType::ComputeShader;

	return ShaderType();
}


}	// sw



