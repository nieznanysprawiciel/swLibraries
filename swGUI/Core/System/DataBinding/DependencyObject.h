#pragma once
/**
@file DependencyObject.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/EngineObject.h"

#include "BindingInfo.h"
#include "Binding.h"
#include "BindingsList.h"

#include "DependencyProperty.h"


/**@defgroup DataBindingSystem Data Binding

@ingroup GUICore*/


namespace sw {
namespace gui
{

/**@brief Support for data binding.

It should correspond to WPF DependencyObject.

@ingroup DataBindingSystem
@ingroup ControlsFramework*/
class DependencyObject : public EngineObject
{
	RTTR_ENABLE( EngineObject );
	RTTR_REGISTRATION_FRIEND
private:
protected:

	rttr::variant		m_dataContext;		///< Context for binding. @todo Consider using std::shared_ptr.
	BindingsList		m_bindingsList;

public:

	explicit		DependencyObject	();
	virtual			~DependencyObject	() = default;


	const rttr::variant&		GetDataContext	() const { return m_dataContext; }
	virtual void				SetDataContext	( const rttr::variant& dataContext );

	ReturnResult				AddBinding		( BindingPtr binding );

public:

	/**@brief If other property binds to this object, it should add binding link.
	@todo This function should be private only for use by binding system.*/
	void						AddBindingLink	( const BindingInfoPtr& bindingInfo );

public:

	template< typename ClassType, typename PropertyType >
	using FieldMemberPtr = PropertyType ( ClassType::* );

	template< typename ClassType, typename PropertyType >
	void			SetValue			( const DependencyProperty& prop, PropertyType value, FieldMemberPtr< ClassType, PropertyType > fieldPtr );

private:

	template< typename ClassType, typename PropertyType >
	PropertyType	GetValue			( FieldMemberPtr< ClassType, PropertyType > fieldPtr ) const;

	template< typename ClassType, typename PropertyType >
	void			SetValue			( FieldMemberPtr< ClassType, PropertyType > fieldPtr, PropertyType value );
};



}	// gui
}	// sw

#include "DependencyObject.inl"
