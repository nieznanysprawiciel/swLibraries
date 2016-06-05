#pragma once

#include "Serialization.h"



/**@brief Zwraca warto�� podanej w�a�ciwo�ci.*/
template< typename PropertyType >
PropertyType	Serialization::GetPropertyValue( rttr::property prop, const EngineObject* object )
{
	if( prop.get_declaring_type().is_derived_from< EngineObject >() )
	{
		auto value = prop.get_value( *static_cast< const EngineObject* >( object ) );
		return value.get_value< PropertyType >();
	}
	else
		assert( false );	return PropertyType();
}

/**@brief Serializuje w�a�ciwo�� podanego typu.

@todo Mo�na zoptymalizowa� pobieranie nazwy z w�a�ciwo�ci i ograniczy� alokacj� string�w.*/
template< typename PropertyType >
void			Serialization::SerializeProperty					( ISerializer* ser, rttr::property prop, const EngineObject* object )
{
	ser->SetAttribute( prop.get_name(), GetPropertyValue< PropertyType >( prop, object ) );
}


