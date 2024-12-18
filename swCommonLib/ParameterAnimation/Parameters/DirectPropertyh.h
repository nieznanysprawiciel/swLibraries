#pragma once
/**
@file DirectProperty.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Common/Object.h"

#include "swCommonLib/Common/Properties/Properties.h"
#include "swSerialization/Serialization/Serialization.h"


/**@brief */
template< typename KeyType >
class DirectProperty
{
private:
	rttr::property		m_property;
	rttr::variant		m_object;		///< @todo Change to typed pointer some way.

protected:
public:
	/// Constructor for serialization.
	explicit		DirectProperty	();
	explicit		DirectProperty	( Object* object, const std::string& propertyPath );
					~DirectProperty	() = default;


	KeyType			GetValue		( Object* object );
	void			SetValue		( Object* object, KeyType& value );
};

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
template< typename KeyType >
inline			DirectProperty< KeyType >::DirectProperty()
	:	m_property( Properties::EmptyProperty() )
	,	m_object( rttr::variant() )
{}


// ================================ //
//
template< typename KeyType >
inline			DirectProperty< KeyType >::DirectProperty	( Object* object, const std::string& propertyPath )
	:	m_property( Properties::EmptyProperty() )
	,	m_object( nullptr )
{
	auto accessor = Properties::GetProperty( object, propertyPath );
	m_property = accessor.second;
	m_object = accessor.first;
}

// ================================ //
//
template< typename KeyType >
inline KeyType		DirectProperty< KeyType >::GetValue		( Object* )
{
	return sw::SerializationCore::GetPropertyValue< KeyType >( m_property, m_object );
}

// ================================ //
//
template< typename KeyType >
inline void			DirectProperty< KeyType >::SetValue		( Object* object, KeyType& value )
{
	sw::SerializationCore::SetPropertyValue( m_property, m_object, value );
}

