#pragma once

#include "BaseObject.h"


namespace sw
{

// ================================ //
//
class PolymorphicObjectContainer
{
public:

	BaseObject*			ObjectPtr;

public:

	// ================================ //
	//
	explicit			PolymorphicObjectContainer()
		:	ObjectPtr( nullptr )
	{}

	// ================================ //
	//
	~PolymorphicObjectContainer()
	{
		delete ObjectPtr;
	}

};


}	// sw

