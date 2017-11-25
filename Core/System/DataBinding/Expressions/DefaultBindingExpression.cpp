#include "DefaultBindingExpression.h"

#include "swCommonLib/Common/Properties/Properties.h"


namespace sw {
namespace gui
{



// ================================ //
//
DefaultBindingExpression::DefaultBindingExpression		( const std::string & bindingPath )
	:	BindingExpression( bindingPath )
{}


// ================================ //
//
Nullable< BindingTarget >				DefaultBindingExpression::EvaluateExpression		( const rttr::variant& dataContext, const rttr::variant& propertyOwner ) const
{
	return DefaultBindingExpression::EvaluateRelativeProperty( dataContext, m_path );
}

// ================================ //
//
BindingExpressionType					DefaultBindingExpression::GetExpressionType		() const
{
	return BindingExpressionType::DataContext;
}

// ================================ //
//
Nullable< BindingTarget >				DefaultBindingExpression::EvaluateRelativeProperty	( const rttr::variant & dataContext, const std::string & path )
{
	auto propObjPair = Properties::GetProperty( dataContext, path, 0, '.' );

	// Check only target object for existance.
	if( propObjPair.first.is_valid() )
		return BindingTarget( propObjPair.first, propObjPair.second );

	/// @todo Make exception for this error.
	return Nullable< BindingTarget >();
}


}	// gui
}	// sw

