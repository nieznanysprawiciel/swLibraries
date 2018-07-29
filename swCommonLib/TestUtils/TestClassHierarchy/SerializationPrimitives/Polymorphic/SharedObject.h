#pragma once

#include "BaseObject.h"



namespace sw
{

// ================================ //
//
class SharedObject : public BaseObject
{
	RTTR_ENABLE( BaseObject )
	RTTR_REGISTRATION_FRIEND
public:

	StructWithSimpleTypes		m_simpleStruct2;

protected:
public:
	explicit		SharedObject		() = default;
	~SharedObject	() = default;

};

DEFINE_PTR_TYPE( SharedObject )



// ================================ //
//
class DerivedFromSharedObject : public SharedObject
{
	RTTR_ENABLE( SharedObject )
	RTTR_REGISTRATION_FRIEND
public:
protected:
public:
	explicit		DerivedFromSharedObject		() = default;
	~DerivedFromSharedObject	() = default;

};


}	// sw
