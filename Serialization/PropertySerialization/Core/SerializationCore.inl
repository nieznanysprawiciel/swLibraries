#pragma once
/**
@file SerializationCore.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "SerializationCore.h"


namespace sw
{


//====================================================================================//
//			Default value traits	
//====================================================================================//

template< typename Type >
inline Type					TypeDefaultValue()
{
	return Type();
}

template<>	inline uint16			TypeDefaultValue() { return 0; }
template<>	inline int16			TypeDefaultValue() { return 0; }
template<>	inline uint32			TypeDefaultValue() { return 0; }
template<>	inline int32			TypeDefaultValue() { return 0; }
template<>	inline int64			TypeDefaultValue() { return 0; }

template<>	inline float			TypeDefaultValue() { return 0.0f; }
template<>	inline double			TypeDefaultValue() { return 0.0; }

template<>	inline std::wstring		TypeDefaultValue() { return std::wstring( L"" ); }
template<>	inline std::string		TypeDefaultValue() { return std::string( "" ); }

template<>	inline DirectX::XMFLOAT2	TypeDefaultValue() { return DirectX::XMFLOAT2( 0.0, 0.0 ); }
template<>	inline DirectX::XMFLOAT3	TypeDefaultValue() { return DirectX::XMFLOAT3( 0.0, 0.0, 0.0 ); }
template<>	inline DirectX::XMFLOAT4	TypeDefaultValue() { return DirectX::XMFLOAT4( 0.0, 0.0, 0.0, 0.0 ); }

template<>	inline EngineObject*		TypeDefaultValue() { return nullptr; }


//====================================================================================//
//			Property templated getters/setters	
//====================================================================================//


/**@brief Returns typed property value.*/
template< typename PropertyType >
PropertyType	SerializationCore::GetPropertyValue			( rttr::property prop, const rttr::instance& object )
{
	auto value = prop.get_value( object );
	assert( value.is_valid() );
	return value.get_value< PropertyType >();
}

/**@brief Serializuje w³aœciwoœæ podanego typu.

@todo Mo¿na zoptymalizowaæ pobieranie nazwy z w³aœciwoœci i ograniczyæ alokacjê stringów.*/
template< typename PropertyType >
void			SerializationCore::SerializeProperty		( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	ser->SetAttribute( prop.get_name().to_string(), GetPropertyValue< PropertyType >( prop, object ) );
}

// ================================ //
//
template< typename PropertyType >
inline void		SerializationCore::SerializeProperty		( ISerializer* ser, rttr::string_view name, const rttr::variant& propertyValue )
{
	ser->SetAttribute( name.to_string(), propertyValue.get_value< PropertyType >() );
}


/**@brief Ustawia wartoœæ podanej w³aœciwoœci.*/
template< typename PropertyType >
void			SerializationCore::SetPropertyValue			( rttr::property prop, const rttr::instance& object, PropertyType value )
{
	prop.set_value( object, value );
}

/**@brief Deserializuje w³aœciwoœæ podanego typu.

@todo Mo¿na zoptymalizowaæ pobieranie nazwy z w³aœciwoœci i ograniczyæ alokacjê stringów.*/
template< typename PropertyType >
void			SerializationCore::DeserializeProperty		( IDeserializer* deser, rttr::property prop, const rttr::instance& object )
{
	PropertyType value = static_cast<PropertyType>( deser->GetAttribute( prop.get_name().to_string(), TypeDefaultValue< PropertyType >() ) );
	SetPropertyValue< PropertyType >( prop, object, value );
}

// ================================ //
//
inline TypeID	SerializationCore::GetRealType				( const rttr::instance& object )
{
	auto objectType = object.get_derived_type();
	return objectType.is_wrapper() ? objectType.get_wrapped_type() : objectType;
}

// ================================ //
//
inline TypeID	SerializationCore::GetWrappedType			( TypeID type )
{
	return type.is_wrapper() ? type.get_wrapped_type() : type;
}


}	// sw