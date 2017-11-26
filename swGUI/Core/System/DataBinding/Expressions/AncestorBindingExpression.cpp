#include "AncestorBindingExpression.h"

#include "swCommonLib/Common/Properties/Properties.h"

#include "swGUI/Core/Controls/UIElement.h"


namespace sw {
namespace gui
{


// ================================ //
//
AncestorBindingExpression::AncestorBindingExpression		( const std::string& bindingPath, TypeID ancestorType )
	:	BindingExpression( bindingPath )
	,	m_ancestorType( ancestorType )
	,	m_ancestorLevels( 1 )
{}

// ================================ //
//
AncestorBindingExpression::AncestorBindingExpression		( const std::string& bindingPath, TypeID ancestorType, uint16 levels )
	:	BindingExpression( bindingPath )
	,	m_ancestorType( ancestorType )
	,	m_ancestorLevels( levels )
{}

// ================================ //
//
AncestorBindingExpression::AncestorBindingExpression		( TypeID ancestorType )
	:	BindingExpression( "" )
	,	m_ancestorType( ancestorType )
	,	m_ancestorLevels( 1 )
{}

// ================================ //
//
AncestorBindingExpression::AncestorBindingExpression		( TypeID ancestorType, uint16 levels )
	:	BindingExpression( "" )
	,	m_ancestorType( ancestorType )
	,	m_ancestorLevels( levels )
{}

// ================================ //
//
Nullable< BindingTarget >		AncestorBindingExpression::EvaluateExpression		( const rttr::variant& dataContext, const rttr::variant& propertyOwner ) const
{
	return Nullable< BindingTarget >();
}

// ================================ //
//
BindingExpressionType			AncestorBindingExpression::GetExpressionType		() const
{
	return BindingExpressionType::FindAncestor;
}

// ================================ //
//
rttr::variant					AncestorBindingExpression::FindAncestor				( const rttr::variant& propertyOwner )
{
	TypeID ownerType = Properties::GetRealType( propertyOwner );
	if( ownerType.is_derived_from< UIElement >() )
	{

	}

	return rttr::variant();
}

}	// gui
}	// sw

