#include "DefaultBindingExpression.h"



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
	return BindingExpression::EvaluateRelativeProperty( dataContext, m_path );
}

// ================================ //
//
BindingExpressionType					DefaultBindingExpression::GetExpressionType		() const
{
	return BindingExpressionType::DataContext;
}



}	// gui
}	// sw

