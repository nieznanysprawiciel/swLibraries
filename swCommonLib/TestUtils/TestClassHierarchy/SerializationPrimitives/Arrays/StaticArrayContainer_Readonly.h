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

const int cArrayReadonlySize = 4;

// ================================ //
//
class StaticArrayContainer_Readonly : public EngineObject
{
	RTTR_ENABLE( EngineObject );
	RTTR_REGISTRATION_FRIEND
public:

	StructWithSimpleTypes		StructsVec[ cArrayReadonlySize ];

protected:
public:
	explicit		StaticArrayContainer_Readonly		();
	~StaticArrayContainer_Readonly	() = default;

	void			ArraysSet1			();
	void			ArraysSet2			();

	bool			Compare				( const StaticArrayContainer_Readonly& other );
};

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline StaticArrayContainer_Readonly::StaticArrayContainer_Readonly()
{
	ArraysSet1();
}

// ================================ //
//
inline void			StaticArrayContainer_Readonly::ArraysSet1()
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
inline void			StaticArrayContainer_Readonly::ArraysSet2()
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
inline bool			StaticArrayContainer_Readonly::Compare	( const StaticArrayContainer_Readonly& other )
{
	for( int i = 0; i < cArrayReadonlySize; ++i )
	{
		if( StructsVec[ i ] != other.StructsVec[ i ] )
			return false;
	}

	return true;
}


}	// sw


