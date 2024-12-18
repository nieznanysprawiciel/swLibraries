#pragma once
/**
@file VertexShape2D.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <DirectXMath.h>


namespace sw {
namespace geom
{

/**@brief Basic shape 2D vertex structure.*/
struct VertexShape2D
{
	DirectX::XMFLOAT2		Position;
	DirectX::XMFLOAT2		UV;
};

/**@brief Text 2D vertex structure supporting texturing.*/
struct VertexText2D
{
	DirectX::XMFLOAT2		Position;
	DirectX::XMFLOAT2		UV;
	DirectX::XMFLOAT2		AtlasCoords;
};



}	// geom
}	// sw

