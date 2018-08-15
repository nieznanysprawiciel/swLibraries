#pragma once
/**
@file BufferTyped.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/RTTR.h"

#include "BufferRaw.h"

#include <allocators>
#include <assert.h>



namespace sw
{



/**@brief Templeted buffer which can store elements of specified type.*/
template< typename ContentType, class Alloc = std::allocator< ContentType > >
class BufferTyped
{
private:

	ContentType*		m_data;			///< Data array pointer.
	Size				m_count;		///< Number of elements.

public:

	explicit			BufferTyped		( Size numElements );
	explicit			BufferTyped		( BufferRaw&& rawBuffer );

						~BufferTyped	();

public:

	TypeID				GetType			() const		{ return TypeID::get< ContentType >(); }
	Size				GetSize			() const		{ return m_count * sizeof( ContentType ); }
	Size				ElementsCount	() const		{ return m_count; }
	uint8*				GetRawData		()				{ return reinterpret_cast< uint8* >( m_data ); }
	const uint8*		GetRawData		() const		{ return reinterpret_cast< const uint8* >( m_data ); }
	bool				IsValid			() const		{ return m_data != nullptr; }

public:

	ContentType&		operator[]		( Size idx );
	const ContentType&	operator[]		( Size idx ) const;

public:

	/**@brief Creates raw buffer. Note that new buffer will be owner of memory and this object ends empty.*/
	BufferRaw			MoveToRawBuffer	();
};



namespace impl
{

// ================================ //
//
template< typename ContentType, class Alloc >
void	Deallocate		( uint8* pointer, Size numElements )
{
	Alloc deallocator;
	deallocator.deallocate( reinterpret_cast< ContentType* >( pointer ), numElements / sizeof( ContentType ) );
}

}



//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
template< typename ContentType, class Alloc >
inline		BufferTyped< ContentType, Alloc >::BufferTyped	( Size numElements )
	:	m_data( nullptr )
	,	m_count( numElements )
{
	Alloc allocator;
	m_data = allocator.allocate( numElements );
}

// ================================ //
//
template< typename ContentType, class Alloc >
inline		BufferTyped< ContentType, Alloc >::BufferTyped	( BufferRaw&& rawBuffer )
{
	assert( rawBuffer.GetType() == TypeID::get< ContentType >() );

	m_data = reinterpret_cast< ContentType* >( rawBuffer.GetData() );
	m_count = rawBuffer.GetSize() / sizeof( ContentType );

	rawBuffer.m_data = nullptr;
	rawBuffer.m_size = 0;
}

// ================================ //
//
template< typename ContentType, class Alloc >
inline		BufferTyped< ContentType, Alloc >::~BufferTyped	()
{
	Alloc allocator;
	allocator.deallocate( m_data, m_count );

	m_data = nullptr;
	m_count = 0;
}

// ================================ //
//
template< typename ContentType, class Alloc >
inline ContentType&			BufferTyped< ContentType, Alloc >::operator[]		( Size idx )
{
	assert( idx < m_count );
	return m_data[ idx ];
}

// ================================ //
//
template< typename ContentType, class Alloc >
inline const ContentType&	BufferTyped< ContentType, Alloc >::operator[]		( Size idx ) const
{
	assert( idx < m_count );
	return m_data[ idx ];
}

// ================================ //
//
template< typename ContentType, class Alloc >
inline BufferRaw			BufferTyped< ContentType, Alloc >::MoveToRawBuffer	()
{
	BufferRaw rawBuffer( GetRawData(), GetSize(), GetType(), &impl::Deallocate< ContentType, Alloc > );

	m_data = nullptr;
	m_count = 0;

	return rawBuffer;
}


}	// sw


