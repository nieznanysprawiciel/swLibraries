#pragma once
/**
@file BindingsList.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "BindingInfo.h"
#include "Binding.h"

#include "DependencyProperty.h"




namespace sw {
namespace gui
{


/**@brief List of all bindings for single object.*/
class BindingsList
{
private:

	std::vector< BindingInfoPtr >		m_bindings;

protected:
public:
	explicit		BindingsList		() = default;
					~BindingsList		() = default;


	BindingInfoPtr			FindBinding		( const DependencyProperty& dependencyProperty );
	BindingInfoPtr			FindBinding		( const rttr::property& property );
	ReturnResult			AddBinding		( BindingPtr binding );

	void					AddBindingLink	( const BindingInfoPtr& binding );

private:

	ReturnResult			AddLinkToSource	( const BindingInfoPtr& binding );
};



}	// gui
}	// sw


