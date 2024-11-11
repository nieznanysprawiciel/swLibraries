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
const AssetPath		VertexText2D_LayoutName = "::sw::gui::VertexText2D";

// ================================ //
//
template<>
InputLayoutDescriptor   		CreateLayoutDescriptor< VertexShape2D >	()
{
    InputLayoutDescriptor desc;
    desc.AddEntry( AttributeSemantic::Position, ResourceFormat::RESOURCE_FORMAT_R32G32_FLOAT,
                   offsetof( VertexShape2D, Position ) );
    desc.AddEntry( AttributeSemantic::Texcoord, ResourceFormat::RESOURCE_FORMAT_R32G32_FLOAT,
                   offsetof( VertexShape2D, UV ) );

    return std::move( desc );
}

// ================================ //
//
template<>
const AssetPath&				GetLayoutName< VertexShape2D >			()
{
	return VertexShape2D_LayoutName;
}


// ================================ //
//
template <> InputLayoutDescriptor CreateLayoutDescriptor< VertexText2D >()
{
    InputLayoutDescriptor desc;
    desc.AddEntry( AttributeSemantic::Position, ResourceFormat::RESOURCE_FORMAT_R32G32_FLOAT,
                   offsetof( VertexText2D, Position ) );
    desc.AddEntry( AttributeSemantic::Texcoord, ResourceFormat::RESOURCE_FORMAT_R32G32_FLOAT,
                   offsetof( VertexText2D, UV ) );
    desc.AddEntry( AttributeSemantic::Texcoord, ResourceFormat::RESOURCE_FORMAT_R32G32_FLOAT,
                   offsetof( VertexText2D, AtlasCoords ) );

    return std::move( desc );
}

// ================================ //
//
template <> const AssetPath& GetLayoutName< VertexText2D >() { return VertexText2D_LayoutName; }



}	// gui
}	// sw
