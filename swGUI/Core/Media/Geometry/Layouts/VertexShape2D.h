#pragma once
/**
@file VertexShape2D.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <DirectXMath.h>


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



}	// gui
}	// sw


