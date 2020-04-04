#pragma once
/**
@file BufferRaw.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/RTTR.h"

#include <allocators>



namespace sw
{

typedef void ( *Deallocator )( uint8* pointer, Size numElements );

/**@brief Buffer containing raw bytes that can be converted to @ref BufferTyped.

BufferRaw can be created only from @ref BufferTyped.*/
class BufferRaw
{
private:

	uint8*			m_data;
	Size			m_size;
	TypeID			m_type;

	Deallocator		m_deallocator;

protected:

	explicit			BufferRaw		( uint8* data, Size size, TypeID type, Deallocator deallocator );

public:

	explicit			BufferRaw		( const BufferRaw& ) = delete;
						BufferRaw		( BufferRaw&& );

	BufferRaw&			operator=		( const BufferRaw& ) = delete;
	BufferRaw&			operator=		( BufferRaw&& );

public:

	~BufferRaw		();

	TypeID				GetType			() const		{ return m_type; }
	Size				GetSize			() const		{ return m_size; }
	uint8*				GetData			()				{ return reinterpret_cast< uint8* >( m_data ); }
	const uint8*		GetData			() const		{ return reinterpret_cast< const uint8* >( m_data ); }
	bool				IsValid			() const		{ return m_data != nullptr; }

public:

	template< typename ContentType, class Aloc > friend class BufferTyped;
};

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline		BufferRaw::BufferRaw		( uint8* data, Size size, TypeID type, Deallocator deallocator )
	:	m_data( data )
	,	m_size( size )
	,	m_type( type )
	,	m_deallocator( deallocator )
{}

// ================================ //
//
inline		BufferRaw::BufferRaw		( BufferRaw&& bufferRaw )
	:	m_data( bufferRaw.m_data )
	,	m_size( bufferRaw.m_size )
	,	m_type( bufferRaw.m_type )
	,	m_deallocator( bufferRaw.m_deallocator )	
{
	bufferRaw.m_data = nullptr;
	bufferRaw.m_size = 0;
}

// ================================ //
//
inline BufferRaw&	BufferRaw::operator=	( BufferRaw&& bufferRaw )
{
	m_data = bufferRaw.m_data;
	m_size = bufferRaw.m_size;
	m_type = bufferRaw.m_type;
	m_deallocator = bufferRaw.m_deallocator;

	bufferRaw.m_data = nullptr;
	bufferRaw.m_size = 0;

	return *this;
}

// ================================ //
//
inline		BufferRaw::~BufferRaw		()
{
	m_deallocator( m_data, m_size );
	m_data = nullptr;
	m_size = 0;
}


}	// sw


