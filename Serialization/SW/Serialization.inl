#pragma once

#include "Serialization.h"



/**@brief Zwraca wartoœæ podanej w³aœciwoœci.*/
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

/**@brief Serializuje w³aœciwoœæ podanego typu.

@todo Mo¿na zoptymalizowaæ pobieranie nazwy z w³aœciwoœci i ograniczyæ alokacjê stringów.*/
template< typename PropertyType >
void			Serialization::SerializeProperty					( ISerializer* ser, rttr::property prop, const EngineObject* object )
{
	ser->SetAttribute( prop.get_name(), GetPropertyValue< PropertyType >( prop, object ) );
}


