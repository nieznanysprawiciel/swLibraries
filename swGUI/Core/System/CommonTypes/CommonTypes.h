#pragma once
/**
@file CommonTypes.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include <string>
#include <DirectXMath.h>

#include "Thickness.h"

#include "swGeometrics/GeometricsCore/Math/Types.h"


namespace sw {
namespace gui
{



static const std::string	EMPTY_STRING;


typedef DirectX::XMFLOAT2	Position;
typedef DirectX::XMFLOAT2	Size2D;
typedef DirectX::XMFLOAT2	Point;
typedef DirectX::XMFLOAT4	Color;

using Rect = Rect2d;

}	// gui
}	// sw
