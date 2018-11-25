#pragma once
/**
@file IndexTypes.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"



namespace sw {
namespace geom
{

typedef uint16 Index16;
typedef uint32 Index32;
typedef uint8 Index8;


/**@brief Order of indicies building triangle.*/
enum WindingOrder
{
	Clockwise,
	CounterClockwise
};

}	// geom
}	// sw
