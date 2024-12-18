#pragma once
/**
@file BufferTyped.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/RTTR.h"

#include "BufferRaw.h"
#include "BufferRange.h"

#include <memory>
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
	explicit			BufferTyped		( const BufferTyped& buffer ) = delete;
						BufferTyped		( BufferTyped&& buffer );

						~BufferTyped	();


	BufferTyped< ContentType, Alloc >&		operator=		( const BufferTyped& ) = delete;
	BufferTyped< ContentType, Alloc >&		operator=		( BufferTyped&& );

private:

	/**@brief Stealing constructor takes ownership of memory.*/
	explicit			BufferTyped		( ContentType*&& data, Size numElements );

public:

	TypeID				GetType			() const		{ return TypeID::get< ContentType >(); }
	Size				GetSize			() const		{ return m_count * sizeof( ContentType ); }
	Size				ElementsCount	() const		{ return m_count; }
	Size				ElementSize		() const		{ return sizeof( ContentType ); }
	
	bool				IsValid			() const { return m_data != nullptr; }
	
	uint8*				GetRawData		()				{ return reinterpret_cast< uint8* >( m_data ); }
	const uint8*		GetRawData		() const		{ return reinterpret_cast< const uint8* >( m_data ); }
	
	ContentType*		GetData		    () { return static_cast< ContentType* >( m_data ); }
	const ContentType*	GetData		    () const { return static_cast< const ContentType* >( m_data ); }
	

public:

	ContentType&		operator[]		( Size idx );
	const ContentType&	operator[]		( Size idx ) const;

	void				ZeroMemory();

public:

	/**@brief Creates raw buffer. Note that new buffer will be owner of memory and this object ends empty.*/
	BufferRaw			MoveToRawBuffer	();
    BufferRange         GetView			() { return BufferRange( GetRawData(), GetSize() ); }

public:
	static BufferRaw	CreateEmpty		();

public:

	/**@brief Takes ownership of memory.*/
	static BufferTyped< ContentType, Alloc >		StealMemory			( ContentType*&& data, Size numElements );
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
inline		BufferTyped< ContentType, Alloc >::BufferTyped	( BufferTyped< ContentType, Alloc >&& other )
{
	m_data = other.m_data;
	m_count = other.ElementsCount();

	other.m_data = nullptr;
	other.m_count = 0;
}

// ================================ //
//
template< typename ContentType, class Alloc >
inline		BufferTyped< ContentType, Alloc >::BufferTyped	( ContentType*&& data, Size numElements )
	:	m_data( std::move( data ) )
	,	m_count( numElements )
{
	data = nullptr;
	// Don't allocate.
}

// ================================ //
//
template< typename ContentType, class Alloc >
inline BufferTyped< ContentType, Alloc >&			BufferTyped< ContentType, Alloc >::operator=( BufferTyped< ContentType, Alloc >&& other )
{
	m_data = other.m_data;
	m_count = other.ElementsCount();

	other.m_data = nullptr;
	other.m_count = 0;
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
template<typename ContentType, class Alloc>
inline void					BufferTyped< ContentType, Alloc >::ZeroMemory()
{
	std::memset( this->GetRawData(), 0, this->GetSize());
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

// ================================ //
//
template< typename ContentType, class Alloc >
inline BufferRaw			BufferTyped< ContentType, Alloc >::CreateEmpty		()
{
	BufferTyped< ContentType > buffer( 0 );
	return buffer.MoveToRawBuffer();
}

// ================================ //
//
template< typename ContentType, class Alloc >
inline BufferTyped< ContentType, Alloc >			BufferTyped< ContentType, Alloc >::StealMemory			( ContentType*&& data, Size numElements )
{
	return BufferTyped< ContentType, Alloc >( std::move( data ), numElements );
}


}	// sw


