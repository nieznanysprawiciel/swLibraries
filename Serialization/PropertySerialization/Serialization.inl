#pragma once

#include "Serialization.h"


template< typename Type >
inline Type					TypeDefaultValue()
{ return Type(); }

template<>	inline uint16			TypeDefaultValue()		{	return 0;	}
template<>	inline int16			TypeDefaultValue()		{	return 0;	}
template<>	inline uint32			TypeDefaultValue()		{	return 0;	}
template<>	inline int32			TypeDefaultValue()		{	return 0;	}
template<>	inline int64			TypeDefaultValue()		{	return 0;	}

template<>	inline float			TypeDefaultValue()		{	return 0.0f;}
template<>	inline double			TypeDefaultValue()		{	return 0.0;	}

template<>	inline std::wstring		TypeDefaultValue()		{	return std::wstring( L"" );	}
template<>	inline std::string		TypeDefaultValue()		{	return std::string( "" );	}

template<>	inline DirectX::XMFLOAT2	TypeDefaultValue()	{	return DirectX::XMFLOAT2( 0.0, 0.0 );	}
template<>	inline DirectX::XMFLOAT3	TypeDefaultValue()	{	return DirectX::XMFLOAT3( 0.0, 0.0, 0.0 );	}
template<>	inline DirectX::XMFLOAT4	TypeDefaultValue()	{	return DirectX::XMFLOAT4( 0.0, 0.0, 0.0, 0.0 );	}

template<>	inline EngineObject*		TypeDefaultValue()		{	return nullptr;	}


/**@brief Returns typed property value.*/
template< typename PropertyType >
PropertyType	Serialization::GetPropertyValue			( rttr::property prop, const rttr::instance& object )
{
	auto value = prop.get_value( object );
	assert( value.is_valid() );
	return value.get_value< PropertyType >();
}

/**@brief Serializuje w�a�ciwo�� podanego typu.

@todo Mo�na zoptymalizowa� pobieranie nazwy z w�a�ciwo�ci i ograniczy� alokacj� string�w.*/
template< typename PropertyType >
void			Serialization::SerializeProperty		( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	ser->SetAttribute( prop.get_name().to_string(), GetPropertyValue< PropertyType >( prop, object ) );
}


/**@brief Ustawia warto�� podanej w�a�ciwo�ci.*/
template< typename PropertyType >
void			Serialization::SetPropertyValue			( rttr::property prop, const rttr::instance& object, PropertyType value )
{
	prop.set_value( object, value );
}

/**@brief Deserializuje w�a�ciwo�� podanego typu.

@todo Mo�na zoptymalizowa� pobieranie nazwy z w�a�ciwo�ci i ograniczy� alokacj� string�w.*/
template< typename PropertyType >
void			Serialization::DeserializeProperty		( IDeserializer* deser, rttr::property prop, const rttr::instance& object )
{
	PropertyType value = static_cast< PropertyType >( deser->GetAttribute( prop.get_name().to_string(), TypeDefaultValue< PropertyType >() ) );
	SetPropertyValue< PropertyType >( prop, object, value );
}


