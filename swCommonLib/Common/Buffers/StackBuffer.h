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


//====================================================================================//
//			StackBuffer with alignemnt
//====================================================================================//

namespace impl
{

// ================================ //
//
template< typename StructType, Size align >
constexpr Size			ComputePadding	()
{
	return ( align - sizeof( StructType ) % align ) % align;
}

// ================================ //
//
template< typename StructType, Size align >
constexpr Size			SizeofWithPadding	()
{
	return sizeof( StructType ) + ComputePadding< StructType, align >();
}

// ================================ //
// Inherit this struct to force padding.
template< Size size >
struct PaddingStruct
{
    uint8			Padding[ size ];
};

// ================================ //
//
template<>
struct PaddingStruct< 0 >
{};


}	// impl



/**@brief StackBuffer with added padding. Content sizeof will be multply of specified value.

You can use this structure for storing constants buffers data, since they need to be 16 bytes multiply.*/
template< typename StructType, Size align = 16 >
class StackBufferA : public StructType, impl::PaddingStruct< impl::ComputePadding< StructType, align >() >
{
	typedef StackBufferA< StructType, align >* ThisType;
private:
public:

	explicit		StackBufferA()
	{
		static_assert( sizeof( StackBufferA< StructType, align > ) == impl::SizeofWithPadding< StructType, align >(), "Something is wrong with StackBufferA implementation. Sizeof doesn't match expected size." );
	}

	Size			GetSize		() const		{ return impl::SizeofWithPadding< StructType, align >(); }
	uint8*			GetData		() const		{ return reinterpret_cast< uint8* >( const_cast< ThisType >( this ) ); }

	BufferRange		GetView		() const		{ return BufferRange( GetData(), GetSize() ); }
};


}	// sw


