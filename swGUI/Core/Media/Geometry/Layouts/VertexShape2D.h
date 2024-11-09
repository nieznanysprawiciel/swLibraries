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
InputLayoutDescriptor   		CreateLayoutDescriptor< VertexShape2D >	();

// ================================ //
//
template<>
const AssetPath&				GetLayoutName< VertexShape2D >			();


/**@brief Text 2D vertex structure supporting texturing.
@ingroup Geometries*/
struct VertexText2D
{
    DirectX::XMFLOAT2 Position;
    DirectX::XMFLOAT2 AtlasCoords;
    DirectX::XMFLOAT2 UV;
};


// ================================ //
//
template<> 
InputLayoutDescriptor CreateLayoutDescriptor< VertexText2D >();

// ================================ //
//
template<>
const AssetPath& GetLayoutName< VertexText2D >();

}	// gui
}	// sw


