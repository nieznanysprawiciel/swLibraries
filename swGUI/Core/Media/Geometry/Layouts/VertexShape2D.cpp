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

const AssetPath		VertexShape2D_LayoutName = "::sw::gui::VertexShape2D";

// ================================ //
//
template<>
InputLayoutDescriptor   		CreateLayoutDescriptor< VertexShape2D >	()
{
	InputLayoutDescriptor desc;
    desc.AddEntry( AttributeSemantic::Position, ResourceFormat::RESOURCE_FORMAT_R32G32_FLOAT );
    desc.AddEntry( AttributeSemantic::Texcoord, ResourceFormat::RESOURCE_FORMAT_R32G32_FLOAT );

	return std::move( desc );
}

// ================================ //
//
template<>
const AssetPath&				GetLayoutName< VertexShape2D >			()
{
	return VertexShape2D_LayoutName;
}


}	// gui
}	// sw
