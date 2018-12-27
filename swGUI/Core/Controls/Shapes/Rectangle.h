#pragma once
/**
@file Rectangle.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Shape.h"


namespace sw {
namespace gui
{



/**@brief Draws rectangle shape.
@ingroup Shapes
@ingroup Controls*/
class Rectangle : public Shape
{
	RTTR_ENABLE( Shape );
	RTTR_REGISTRATION_FRIEND;
private:
protected:
public:
	explicit		Rectangle		() = default;
	virtual			~Rectangle		() = default;

};



}	// gui
}	// sw


