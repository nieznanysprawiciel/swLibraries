#pragma once

#include "Serialization.h"



namespace sw
{

// ================================ //
//
template< typename Type >
inline bool			Serialization::Serialize		( const filesystem::Path& filePath, const Type& object )
{
	ISerializer ser( std::static_pointer_cast< ISerializationContext >( m_context ) );

	if( Serialize< Type >( ser, object ) )
	{
		if( filesystem::Dir::CreateDirectory( filePath ) )
			return ser.SaveFile( filePath.String() );
	}

	return false;
}

// ================================ //
//
template< typename Type >
inline bool			Serialization::Serialize		( ISerializer& ser, const Type& object )
{
	SerializationCore::DefaultSerializeImpl( &ser, object, TypeID::get( object ) );
	return true;
}


}	// sw
