#pragma once



#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/BaseObject.h"

#include <vector>



namespace sw
{


// ================================ //
//
class ArrayPolymorphicContainer : public EngineObject
{
	RTTR_ENABLE( EngineObject );
	RTTR_REGISTRATION_FRIEND
public:

	std::vector< BaseObject* >		PolymorphicsVec;

protected:
public:
	explicit		ArrayPolymorphicContainer		();
	~ArrayPolymorphicContainer	();


	void			ArraysSet1			();

};

//====================================================================================//
//			Implementation
//====================================================================================//


// ================================ //
//
inline		ArrayPolymorphicContainer::ArrayPolymorphicContainer	()
{}

// ================================ //
//
inline		ArrayPolymorphicContainer::~ArrayPolymorphicContainer	()
{
	for( auto obj : PolymorphicsVec )
		delete obj;

	PolymorphicsVec.clear();
}

// ================================ //
//
inline void			ArrayPolymorphicContainer::ArraysSet1		()
{
	PolymorphicsVec.clear();

	//
	DerivedObject* object1 = new DerivedObject();
	object1->m_simpleStruct1.FillWithDataset2();
	object1->m_simpleStruct1.FillWithDataset3();

	PolymorphicsVec.push_back( object1 );

	//
	BaseObject* object2 = new BaseObject();
	object2->m_simpleStruct1.FillWithDataset4();

	PolymorphicsVec.push_back( object2 );

	//
	DerivedObject* object3 = new DerivedObject();
	object1->m_simpleStruct1.FillWithDataset4();
	object1->m_simpleStruct1.FillWithDataset1();

	PolymorphicsVec.push_back( object3 );
}



}	// sw

