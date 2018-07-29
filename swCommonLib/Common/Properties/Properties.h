#pragma once

#include "swCommonLib/Common/Object.h"
#include "swCommonLib/Common/RTTR.h"

#include <vector>
#include <string>


class Properties
{
private:
public:

	static std::vector< rttr::property >					GetPropertyPath	( Object* object, const std::string& propertyPath, char separator = '/' );
	static std::vector< rttr::property >					GetPropertyPath	( rttr::variant object, const std::string& propertyPath, Size offset = 0, char separator = '/' );

	static std::pair< rttr::variant, rttr::property >		GetProperty		( Object* object, const std::string& propertyPath, char separator = '/' );
	static std::pair< rttr::variant, rttr::property >		GetProperty		( rttr::variant object, const std::string& propertyPath, Size offset = 0, char separator = '/' );
	static std::pair< rttr::variant, rttr::property >		GetProperty		( Object* object, const std::vector< rttr::property >& propertyPath );
	
	template< typename Type >
	static Type						GetValue		( Object* object, const std::vector< rttr::property >& propertyPath );

	static rttr::property			EmptyProperty	();
	static TypeID					GetRealType		( const rttr::variant& object );
	static TypeID					GetRealType		( Object* object );
};

//====================================================================================//
//			Implementation	
//====================================================================================//


template< typename Type >
inline Type			Properties::GetValue		( Object* object, const std::vector< rttr::property >& propertyPath )
{
	rttr::variant propertyVal = object;

	for( auto& property : propertyPath )
	{
		propertyVal = property.get_value( propertyVal );
	}

	return propertyVal.get_value< Type >();
}
