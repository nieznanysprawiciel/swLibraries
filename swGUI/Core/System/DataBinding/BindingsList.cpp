#include "BindingsList.h"

#include "BindingInfo.h"


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
		if( bindingInfo->m_propertyBinding->GetTargetProperty() == property )
			return bindingInfo;
	}

	return nullptr;
}

// ================================ //
//
ReturnResult			BindingsList::AddBinding		( BindingPtr binding )
{
	if( FindBinding( binding->GetTargetProperty() ) )
	{
		/// @todo Better error message.
		return std::string( "Property [" ) + binding->GetTargetProperty().get_name() + "] is already bound to property.";
	}

	auto bindingInfo = std::make_shared< BindingInfo >( binding );
	m_bindings.push_back( bindingInfo );

	return Result::Success;
}


}	// gui
}	// sw