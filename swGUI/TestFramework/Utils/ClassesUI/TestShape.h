#pragma once
/**
@file TestShape.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/Controls/Shapes/Shape.h"

namespace sw {
namespace gui
{


// ================================ //
//
class TestShape : public Shape
{
public:
	using Shape::SetGeometry;


};

DEFINE_OPTR_TYPE( TestShape );

}	// gui
}	// sw
