#pragma once

#include "StructWithSimpleTypesShared.h"



namespace sw
{

// ================================ //
//
class StructSharedPtrContainer
{
public:

	StructWithSimpleTypesSharedPtr		SimpleStruct;

public:

	explicit		StructSharedPtrContainer	();

	void			Replace				( StructWithSimpleTypesSharedPtr simpleStruct );
};

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline StructSharedPtrContainer::StructSharedPtrContainer()
	:	SimpleStruct( std::make_shared< StructWithSimpleTypesShared >() )
{}

// ================================ //
//
inline void			StructSharedPtrContainer::Replace		( StructWithSimpleTypesSharedPtr simpleStruct )
{
	SimpleStruct = simpleStruct;
}

}	// sw

