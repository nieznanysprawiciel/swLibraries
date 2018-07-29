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

const int cArraySize = 4;

// ================================ //
//
class StaticArrayContainer : public EngineObject
{
	RTTR_ENABLE( EngineObject );
	RTTR_REGISTRATION_FRIEND
public:

	StructWithSimpleTypes		StructsVec[ cArraySize ];

protected:
public:
	explicit		StaticArrayContainer		();
	~StaticArrayContainer	() = default;

	void			ArraysSet1			();
	void			ArraysSet2			();

	bool			Compare				( const StaticArrayContainer& other );
};

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline StaticArrayContainer::StaticArrayContainer()
{
	ArraysSet1();
}

// ================================ //
//
inline void			StaticArrayContainer::ArraysSet1()
{
	StructWithSimpleTypes content;

	content.FillWithDataset1();
	StructsVec[ 0 ] = content;

	content.FillWithDataset2();
	StructsVec[ 1 ] = content;

	content.FillWithDataset3();
	StructsVec[ 2 ] = content;

	content.FillWithDataset3();
	StructsVec[ 3 ] = content;
}

// ================================ //
//
inline void			StaticArrayContainer::ArraysSet2()
{
	StructWithSimpleTypes content;

	content.FillWithDataset3();
	StructsVec[ 0 ] = content;

	content.FillWithDataset1();
	StructsVec[ 1 ] = content;

	content.FillWithDataset2();
	StructsVec[ 2 ] = content;

	content.FillWithDataset2();
	StructsVec[ 3 ] = content;
}

// ================================ //
//
inline bool			StaticArrayContainer::Compare	( const StaticArrayContainer& other )
{
	for( int i = 0; i < cArraySize; ++i )
	{
		if( StructsVec[ i ] != other.StructsVec[ i ] )
			return false;
	}

	return true;
}


}	// sw


