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
	rttr::variant ancestor = AncestorBindingExpression::FindAncestor( propertyOwner, m_ancestorType, m_ancestorLevels );
	return BindingExpression::EvaluateRelativeProperty( ancestor, m_path );
}

// ================================ //
//
BindingExpressionType			AncestorBindingExpression::GetExpressionType		() const
{
	return BindingExpressionType::FindAncestor;
}

// ================================ //
//
rttr::variant					AncestorBindingExpression::FindAncestor				( const UIElement* control, TypeID ancestorType, uint16 levels )
{
	if( levels == 0 )
		return rttr::variant();

	// Ommit current control, it could be of type ancestorType.
	control = control->GetParent();

	while( control && levels > 0 )
	{
		if( control->GetType() == ancestorType )
		{
			levels--;
			continue;
		}

		control = control->GetParent();
	}

	return control == nullptr ? rttr::variant() : control;
}

// ================================ //
//
rttr::variant					AncestorBindingExpression::FindAncestor				( const rttr::variant& propertyOwner, TypeID ancestorType, uint16 levels )
{
	TypeID ownerType = Properties::GetRealType( propertyOwner );
	if( ownerType.is_derived_from< UIElement >() )
	{
		auto control = propertyOwner.get_value< UIElement* >();
		return FindAncestor( control, ancestorType, levels );
	}

	return rttr::variant();
}

}	// gui
}	// sw

