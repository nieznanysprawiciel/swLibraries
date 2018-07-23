#pragma once

#include "swCommonLib/Common/RTTR.h"


namespace sw {
namespace gui
{


/**@brief Contains information about single DependancyProperty.

Note that WPF threats DependencyProperties different then this gui. In WPF each property has
it's default value and it exists only, if this value is different.
In this moment all properties in swGUI need to have corresponding fields or getters/setters
in class members. @todo Maybe in future we should change this, since it is usefull thing to spare
some memory especially in large controls.

@todo Think about AttachedProperties. How to implement them?*/
class DependencyProperty
{
public:

	const rttr::property		Property;

public:

	explicit		DependencyProperty		( const rttr::property& property )
		: Property( property )
	{}


	/**@brief Registers DependencyProperty from existing rttr property.*/
	static DependencyProperty			Register		( rttr::property& property );

	/**@brief Registers DependencyProperty from existing rttr property.*/
	static DependencyProperty			Register		( const char* propertyName, TypeID ownerType );
};




}	// gui
}	// sw


