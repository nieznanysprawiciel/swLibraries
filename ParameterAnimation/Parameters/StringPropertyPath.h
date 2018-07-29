#pragma once
/**
@file StringPropertyPath.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"


/**@brief */
template< typename KeyType >
class StringPropertyPath
{
private:
	std::string		m_path;

protected:
public:
	explicit		StringPropertyPath	();
	explicit		StringPropertyPath	( Object* object, const std::string& propertyPath );
					~StringPropertyPath	() = default;


	KeyType			GetValue		( Object* object );
	void			SetValue		( Object* object, KeyType& value );
};


//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
template< typename KeyType >
inline		StringPropertyPath< KeyType >::StringPropertyPath()
	:	m_path( "" )
{}

// ================================ //
//
template< typename KeyType >
inline		StringPropertyPath<	KeyType >::StringPropertyPath( Object* object, const std::string& propertyPath )
	:	m_path( propertyPath )
{}

// ================================ //
//
template< typename KeyType >
inline KeyType		StringPropertyPath< KeyType >::GetValue		( Object* object )
{
	auto finalPair = Properties::GetProperty( object, m_path );
	auto& owner = finalPair.first;
	auto& prop = finalPair.second;

	return sw::SerializationCore::GetPropertyValue< KeyType >( prop, owner );
}

template< typename KeyType >
inline void			StringPropertyPath< KeyType >::SetValue		( Object* object, KeyType& value )
{
	auto finalPair = Properties::GetProperty( object, m_path );
	auto& owner = finalPair.first;
	auto& prop = finalPair.second;

	sw::SerializationCore::SetPropertyValue( prop, owner, value );
}
