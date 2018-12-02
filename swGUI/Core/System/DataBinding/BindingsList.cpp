/**
@file BindingsList.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "BindingsList.h"

#include "BindingInfo.h"
#include "DependencyObject.h"

#include "swCommonLib/Common/Properties/Properties.h"

namespace sw {
namespace gui
{



// ================================ //
/// @todo Implement more efficient way to find BindingInfo object. Here we make to many memory
/// accesses in different cache lines.
BindingInfoPtr			BindingsList::FindBinding		( const DependencyProperty& dependencyProperty )
{
	return FindBinding( dependencyProperty.Property );
}

// ================================ //
//
BindingInfoPtr			BindingsList::FindBinding		( const rttr::property& property )
{
	for( auto& bindingInfo : m_bindings )
	{
		if( bindingInfo->GetProperty() == property )
			return bindingInfo;
	}

	return nullptr;
}

// ================================ //
//
ReturnResult			BindingsList::AddBinding		( BindingPtr binding )
{
	auto bindingInfo = FindBinding( binding->GetTargetProperty() );
	if( bindingInfo )
	{
		if( bindingInfo->GetBinding() != nullptr )
		{
			/// @todo Better error message.
			return std::string( "Property [" ) + binding->GetTargetProperty().get_name() + "] is already bound to property.";
		}
		else
		{
			bindingInfo->SetBinding( binding );
		}
	}
	else
	{
		bindingInfo = std::make_shared< BindingInfo >( binding );
		m_bindings.push_back( bindingInfo );
	}

	AddLinkToSource( bindingInfo );

	return Result::Success;
}

// ================================ //
//
void					BindingsList::AddBindingLink		( const BindingInfoPtr& binding )
{
	auto sourcePropInfo = FindBinding( binding->GetProperty() );
	
	// If BindingInfo object didn't exist, we create new one with empty binding.
	if( sourcePropInfo == nullptr )
		sourcePropInfo = std::make_shared< BindingInfo >( binding->GetProperty() );

	sourcePropInfo->AddBindingLink( binding );
	m_bindings.push_back( sourcePropInfo );
}

// ================================ //
//
ReturnResult			BindingsList::AddLinkToSource		( const BindingInfoPtr& binding )
{
	auto object = binding->m_binding->GetSourceObject();

	auto objectType = object.get_type();
	auto type = objectType.is_wrapper() ? objectType.get_wrapped_type() : objectType;

	if( type.is_derived_from< DependencyObject >() )
	{
		auto dependencyObject = objectType.is_wrapper() ? object.get_wrapped_value< DependencyObject* >() : object.get_value< DependencyObject* >();
		dependencyObject->AddBindingLink( binding );
	}

	return Result::Success;
}


}	// gui
}	// sw