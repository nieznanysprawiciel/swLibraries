#pragma once
/**
@file StackBuffer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "BufferRange.h"


namespace sw
{

/**@brief Buffer that doesn't allocate memory.

This class wrappes structure in buffer interface.*/
template< typename StructType >
class StackBuffer : public StructType
{
	typedef StackBuffer< StructType >* ThisType;
private:
public:

	Size			GetSize		() const		{ return sizeof( StructType ); }
	uint8*			GetData		() const		{ return reinterpret_cast< uint8* >( const_cast< ThisType >( this ) ); }

	BufferRange		GetView		() const		{ return BufferRange( GetData(), GetSize() ); }
};


}	// sw


