/**
@file VertexShape2D.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "VertexShape2D.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/ResourcesFactory.h"


namespace sw {
namespace gui
{

const std::wstring		VertexShape2D_LayoutName = L"::sw::gui::VertexShape2D";

// ================================ //
//
template<>
InputLayoutDescriptorUPtr		CreateLayoutDescriptor< VertexShape2D >	()
{
	InputLayoutDescriptor* desc = ResourcesFactory::CreateInputLayoutDescriptor( GetLayoutName< VertexShape2D >() );
	desc->AddRow( "POSITION", ResourceFormat::RESOURCE_FORMAT_R32G32_FLOAT, 0, 0, false, 0 );
	desc->AddRow( "TEXCOORD", ResourceFormat::RESOURCE_FORMAT_R32G32_FLOAT, 0, 8, false, 0 );

	return std::unique_ptr< InputLayoutDescriptor >( desc );
}

// ================================ //
//
template<>
const std::wstring&				GetLayoutName< VertexShape2D >			()
{
	return VertexShape2D_LayoutName;
}

// ================================ //
//
template<>
std::string						GetLayoutExampleShader< VertexShape2D >	()
{
	return "$(CoreGUI-Shader-Dir)/Layouts/VertexShape2D.vsh";
}


}	// gui
}	// sw