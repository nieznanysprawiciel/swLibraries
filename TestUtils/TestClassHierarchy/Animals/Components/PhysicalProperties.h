#pragma once


#include "swCommonLib/Common/TypesDefinitions.h"


namespace sw
{



/**@brief PhysicalProperties
@ingroup TestClassHierarchy*/
struct PhysicalProperties
{
	float			Weight;
	uint32			Length;
	uint32			Height;

// ================================ //
//
	PhysicalProperties()
		: Weight( 0 )
		, Length( 0 )
		, Height( 0 )
	{}
};


}	// sw


