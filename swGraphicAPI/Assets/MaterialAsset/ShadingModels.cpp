/**
@file ShadingModels.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Assets/MaterialAsset/stdafx.h"

#include "swCommonLib/Common/RTTR.h"

#include "ShadingModelData.h"
#include "PhongMaterialData.h"

#include "swCommonLib/Common/MemoryLeaks.h"


RTTR_REGISTRATION
{
    rttr::registration::class_< DirectX::XMFLOAT4 >( "DirectX::XMFLOAT4" )
        .property( "X", &DirectX::XMFLOAT4::x )
        .property( "Y", &DirectX::XMFLOAT4::y )
        .property( "Z", &DirectX::XMFLOAT4::z )
        .property( "W", &DirectX::XMFLOAT4::w );

    rttr::registration::class_< DirectX::XMFLOAT3 >( "DirectX::XMFLOAT3" )
        .property( "X", &DirectX::XMFLOAT3::x )
        .property( "Y", &DirectX::XMFLOAT3::y )
        .property( "Z", &DirectX::XMFLOAT3::z );

    rttr::registration::class_< DirectX::XMFLOAT2 >( "DirectX::XMFLOAT2" )
        .property( "X", &DirectX::XMFLOAT2::x )
        .property( "Y", &DirectX::XMFLOAT2::y );

	rttr::registration::class_< sw::ShadingModelBase >( "ShadingModelBase" )
		.property_readonly( "TypeName", &sw::ShadingModelBase::GetShadingModelTypeName );

	rttr::registration::class_< sw::PhongMaterial >( "PhongMaterial" )
		.property( "Diffuse", &sw::PhongMaterial::Diffuse ) BIND_AS_PTR
		.property( "Specular", &sw::PhongMaterial::Specular ) BIND_AS_PTR
		.property( "Emissive", &sw::PhongMaterial::Emissive ) BIND_AS_PTR
		.property( "Ambient", &sw::PhongMaterial::Ambient ) BIND_AS_PTR
		.property( "Power", &sw::PhongMaterial::Power );

	rttr::registration::class_< sw::ShadingModelData< sw::PhongMaterial > >( "ShadingModelData< PhongMaterial >" )
		.constructor<>()( rttr::policy::ctor::as_raw_ptr )
		.property( "Data", &sw::ShadingModelData< sw::PhongMaterial >::Data ) BIND_AS_PTR;
}




namespace sw
{

// Note: There should be at least one function (or constructor) in this file. Otherwise compiler
//doesn't want to compile RTTR type registrations.

ShadingModelBase::ShadingModelBase()
{}


// ================================ //
//
std::string			ShadingModelBase::GetShadingModelTypeName ()
{
	return GetShadingModelType().get_name().to_string();
}

}	// sw
