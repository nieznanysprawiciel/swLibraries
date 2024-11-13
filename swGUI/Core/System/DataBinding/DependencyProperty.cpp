/**
@file DependancyProperty.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "swCommonLib/Common/Exceptions/Common/InvalidCodeLogicException.h"
#include "DependencyProperty.h"

#include <assert.h>


namespace sw {
namespace gui
{

// ================================ //
//
DependencyProperty			DependencyProperty::Register		( rttr::property& property )
{
	if( !property.is_valid() )
        throw InvalidCodeLogicException::Create( "Registering DependencyProperty: rttr property is not valid.", __FILE__, __LINE__ );
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


