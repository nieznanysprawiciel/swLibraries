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
		filesystem::Dir::CreateDirectory( filePath );
		return ser.SaveFile( filePath.String(), WritingMode::Readable );
	}

	return false;
}

// ================================ //
//
template< typename Type >
inline bool			Serialization::Serialize		( ISerializer& ser, const Type& object )
{
	SerializationCore::DefaultSerializeImpl( ser, object, TypeID::get( object ) );
	return true;
}

// ================================ //
//
template< typename Type >
inline bool			Serialization::Deserialize		( const filesystem::Path& filePath, const Type& object )
{
	IDeserializer deser( std::static_pointer_cast< ISerializationContext >( m_context ) );

	if( deser.LoadFromFile( filePath.String(), ParsingMode::ParseInsitu ) )
	{
		return Deserialize( deser, object );
	}

	return false;
}

// ================================ //
//
template< typename Type >
inline bool			Serialization::Deserialize		( IDeserializer& deser, Type& object )
{
	rttr::instance objectVar( object );
	TypeID objType = objectVar.get_derived_type();
	objType = objType.is_wrapper() ? objType.get_wrapped_type() : objType;

	if( deser.EnterObject( objType.get_raw_type().get_name().to_string() ) )
	{
		SerializationCore::DefaultDeserializeImpl( deser, object, objType );
		deser.Exit();

		return true;
	}

	return false;
}


}	// sw
