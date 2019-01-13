/**
@file DependancyProperty.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "DependencyProperty.h"

#include <assert.h>


namespace sw {
namespace gui
{

// ================================ //
//
DependencyProperty			DependencyProperty::Register		( rttr::property& property )
{
	assert( property.is_valid() );
	return DependencyProperty( property );
}

// ================================ //
//
DependencyProperty			DependencyProperty::Register		( const char* propertyName, TypeID ownerType )
{
	return Register( ownerType.get_property( propertyName ) );
}


}	// gui
}	// sw


