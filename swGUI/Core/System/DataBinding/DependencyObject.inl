#pragma once
/**
@file DependencyObject.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "DependencyObject.h"


namespace sw {
namespace gui
{

// ================================ //
//
template< typename ClassType, typename PropertyType >
inline bool					DependencyObject::SetValue			( const DependencyProperty& prop,
																  PropertyType value,
																  FieldMemberPtr< ClassType, PropertyType > fieldPtr )
{
    assert( prop.Property.get_type() == TypeID::get< PropertyType >() );

	// Prevent from infinite loop in case of TwoWay binding mode.
	if( value != GetValue( fieldPtr ) )
	{
		SetValue( fieldPtr, value );

		BindingInfoPtr bindingInfo = m_bindingsList.FindBinding( prop );
		
		if( bindingInfo )
			bindingInfo->PropagateToSource();
        return true;
	}
    return false;
}





//====================================================================================//
//			Helper functions
//====================================================================================//

// ================================ //
//
template< typename ClassType, typename PropertyType >
inline PropertyType				DependencyObject::GetValue		( FieldMemberPtr< ClassType, PropertyType > fieldPtr ) const
{
	return static_cast< const ClassType* const >( this )->*fieldPtr;
}

// ================================ //
//
template< typename ClassType, typename PropertyType >
inline void						DependencyObject::SetValue		( FieldMemberPtr< ClassType, PropertyType > fieldPtr, PropertyType value )
{
	static_cast< ClassType* const >( this )->*fieldPtr = value;
}

}	// gui
}	// sw
