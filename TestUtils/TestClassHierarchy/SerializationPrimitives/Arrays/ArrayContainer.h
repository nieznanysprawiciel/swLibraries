#pragma once
/**
@file StringContainer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructWithSimpleTypes.h"

#include <vector>



namespace sw
{


// ================================ //
//
class ArrayContainer : public EngineObject
{
	RTTR_ENABLE( EngineObject );
	RTTR_REGISTRATION_FRIEND
public:

	std::vector< StructWithSimpleTypes >		StructsVec;

protected:
public:
	explicit		ArrayContainer		();
	~ArrayContainer	() = default;

	void			ArraysSet1			();
	void			ArraysSet2			();
};

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline ArrayContainer::ArrayContainer()
{
	ArraysSet1();
}

// ================================ //
//
inline void			ArrayContainer::ArraysSet1()
{
	StructWithSimpleTypes content;

	StructsVec.clear();

	content.FillWithDataset1();
	StructsVec.push_back( content );

	content.FillWithDataset2();
	StructsVec.push_back( content );

	content.FillWithDataset3();
	StructsVec.push_back( content );
}

// ================================ //
//
inline void			ArrayContainer::ArraysSet2()
{
	StructWithSimpleTypes content;

	StructsVec.clear();

	content.FillWithDataset3();
	StructsVec.push_back( content );

	content.FillWithDataset2();
	StructsVec.push_back( content );

	content.FillWithDataset1();
	StructsVec.push_back( content );

	content.FillWithDataset4();
	StructsVec.push_back( content );
}


}	// sw


