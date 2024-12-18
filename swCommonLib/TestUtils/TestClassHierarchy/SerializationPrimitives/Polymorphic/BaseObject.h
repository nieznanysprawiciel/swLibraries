#pragma once
/**
@file BaseObject.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Object.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructWithSimpleTypes.h"



namespace sw
{


// ================================ //
//
class BaseObject : public Object
{
	RTTR_ENABLE( Object )
	RTTR_REGISTRATION_FRIEND
public:

	StructWithSimpleTypes		m_simpleStruct1;

protected:
public:
	explicit		BaseObject		() = default;
	                ~BaseObject	    () = default;

};
DEFINE_PTR_TYPE( BaseObject );


// ================================ //
//
class DerivedObject : public BaseObject
{
	RTTR_ENABLE( BaseObject )
	RTTR_REGISTRATION_FRIEND
public:

	StructWithSimpleTypes		m_simpleStruct2;

protected:
public:
	explicit		DerivedObject		() = default;
	                ~DerivedObject	    () = default;
};
DEFINE_PTR_TYPE( DerivedObject );


// ================================ //
//
class NotRelated : public Object
{
	RTTR_ENABLE( Object )
	RTTR_REGISTRATION_FRIEND
public:

	StructWithSimpleTypes		m_simpleStruct1;

protected:
public:
	explicit		NotRelated		() = default;
	                ~NotRelated	    () = default;

};



}	// sw


