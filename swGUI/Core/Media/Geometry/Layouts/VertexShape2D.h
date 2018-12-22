#pragma once
/**
@file VertexShape2D.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <DirectXMath.h>

#include "Layouts.h"


namespace sw {
namespace gui
{

/**@brief Basic shape 2D vertex structure.
@ingroup Geometries*/
struct VertexShape2D
{
	DirectX::XMFLOAT2		Position;
	DirectX::XMFLOAT2		UV;
};


// ================================ //
//
template<>
InputLayoutDescriptorUPtr		CreateLayoutDescriptor< VertexShape2D >	();

// ================================ //
//
template<>
const std::wstring&				GetLayoutName< VertexShape2D >			();

// ================================ //
//
template<>
std::string						GetLayoutExampleShader< VertexShape2D >	();

}	// gui
}	// sw


