#pragma once
/**
@file BaseObject.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"

#include "StructWithSimpleTypes.h"



namespace sw
{


// ================================ //
//
class BaseObject : public EngineObject
{
	RTTR_ENABLE( EngineObject )
	RTTR_REGISTRATION_FRIEND
public:

	StructWithSimpleTypes		m_simpleStruct1;

protected:
public:
	explicit		BaseObject		() = default;
	~BaseObject	() = default;

};


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
	~DerivedObject	() = default;

};




}	// sw


