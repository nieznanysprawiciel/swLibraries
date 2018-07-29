#pragma once

#include "SharedObject.h"


namespace sw
{

// ================================ //
//
class PolymorphicSharedPtrContainer
{
public:

	SharedObjectPtr			ObjectPtr;

public:

	// ================================ //
	//
	explicit			PolymorphicSharedPtrContainer()
		:	ObjectPtr( nullptr )
	{}


};



}	// sw

