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

/**@brief Not-copyable object.
@ingroup TestClassHierarchy*/
struct NotCopyable
{
    NotCopyable() = default;
    NotCopyable( const NotCopyable& ) = delete;
    NotCopyable( NotCopyable&& ) = default;
    NotCopyable& operator=( const NotCopyable& ) = delete;
};

}	// sw


