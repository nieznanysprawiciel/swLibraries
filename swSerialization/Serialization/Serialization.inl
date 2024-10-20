#pragma once
/**
@file Serialization.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Serialization.h"

#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"



namespace sw
{

// ================================ //
//
template< typename Type >
inline ReturnResult			Serialization::Serialize		( const filesystem::Path& filePath, const Type& object )
{
	ISerializer ser( std::static_pointer_cast< ISerializationContext >( m_context ) );

    auto result = Serialize< Type >( ser, object );
	if( result.IsValid() )
	{
		filesystem::Dir::CreateDirectory( filePath );
        return ser.SaveFile( filePath.String(), WritingMode::Readable );
	}

	return result;
}

// ================================ //
//
template< typename Type >
inline ReturnResult			Serialization::Serialize		( ISerializer& ser, const Type& object )
{
    // Pointer can be copied into instance, but reference must be wrapped, otherwise
    // rttr will try to copy it's value.
    auto objectVariant = std::is_pointer< Type >::value ?
        rttr::variant( object ) :
        rttr::variant( std::reference_wrapper< const Type >( object ) );

	SerializationCore::DefaultSerialize( ser, objectVariant );
	return Success::True;
}

// ================================ //
//
template< typename Type >
inline Nullable< Type >     Serialization::Deserialize      ( const filesystem::Path& filePath )
{
    IDeserializer deser( std::static_pointer_cast< ISerializationContext >( m_context ) );

    auto result = deser.LoadFromFile( filePath.String() );
    if( result.IsValid() )
        return Deserialize< Type >( deser );

    return result;
}

// ================================ //
//
template< typename Type >
inline ReturnResult			Serialization::Deserialize		( const filesystem::Path& filePath, Type& object )
{
	IDeserializer deser( std::static_pointer_cast< ISerializationContext >( m_context ) );

    auto result = deser.LoadFromFile( filePath.String() );
    if( result.IsValid() )
		return Deserialize( deser, object );

    return result;
}

// ================================ //
//
template< typename Type >
inline Nullable< Type >     Serialization::Deserialize      ( IDeserializer& deser )
{
    Type object;
    return Deserialize( deser, object ).Ok( std::move( object ) );
}

// ================================ //
//
template< typename Type >
inline ReturnResult         Serialization::Deserialize		( IDeserializer& deser, Type& object )
{
    // Pointer can be copied into instance, but reference must be wrapped, otherwise
    // rttr will try to copy it's value.
    rttr::variant objectInstance = std::is_pointer< Type >::value ?
        rttr::variant( object ) :
        rttr::variant( std::reference_wrapper< Type >( object ) );

	auto objType = SerializationCore::GetRealType( objectInstance );

	if( deser.EnterObject( objType.get_raw_type().get_name().to_string() ) )
	{
		auto result = SerializationCore::DefaultDeserializeImpl( deser, objectInstance, objType );
		deser.Exit();

		return result;
	}

    /// @todo Return proper error messsage.
	return Success::False;
}


}	// sw
