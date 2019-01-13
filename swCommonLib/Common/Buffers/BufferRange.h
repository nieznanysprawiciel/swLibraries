#pragma once
/**
@file BufferRange.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"



namespace sw
{


/**@brief Describes range of buffer.
Memory is still owned by source buffer and it shouldn't be freed as long as this object exists.*/
struct BufferRange
{
	uint8*		DataPtr;
	Size		DataSize;

// ================================ //
//
	BufferRange()
		: DataPtr( nullptr )
		, DataSize( 0 )
	{}

	BufferRange( uint8* data, Size size )
		: DataPtr( data )
		, DataSize( size )
	{}			
};



}	// sw
