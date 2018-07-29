#pragma once
/**
@file PropertyPath.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Common/Properties/Properties.h"
#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"

#include <vector>


/**@brief */
template< typename KeyType >
class PropertyPath
{
private:
	std::vector< rttr::property >	m_path;

public:
	/// Constructor for serialization.
	explicit		PropertyPath	();
	explicit		PropertyPath	( Object* object, const std::string& propertyPath );
					~PropertyPath	() = default;

	KeyType			GetValue		( Object* object );
	void			SetValue		( Object* object, KeyType& value );
};


//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
template< typename KeyType >
inline			PropertyPath< KeyType >::PropertyPath()
{}

// ================================ //
//
template< typename KeyType >
inline			PropertyPath< KeyType >::PropertyPath	( Object* object, const std::string& propertyPath )
	:	m_path( Properties::GetPropertyPath( object, propertyPath ) )
{}

// ================================ //
//
template< typename KeyType >
inline KeyType	PropertyPath< KeyType >::GetValue		( Object* object )
{
	auto finalPair = Properties::GetProperty( object, m_path );
	auto& owner = finalPair.first;
	auto& prop = finalPair.second;

	return sw::SerializationCore::GetPropertyValue< KeyType >( prop, owner );
}

// ================================ //
//
template< typename KeyType >
inline void		PropertyPath< KeyType >::SetValue		( Object* object, KeyType& value )
{
	auto finalPair = Properties::GetProperty( object, m_path );
	auto& owner = finalPair.first;
	auto& prop = finalPair.second;

	sw::SerializationCore::SetPropertyValue( prop, owner, value );
}
