#pragma once


#include "BindingExpression.h"



namespace sw {
namespace gui
{

class UIElement;


/**@brief Finds ancestor of current control. Then searches property by path.

Property owner must be derived from UIElement for ancestor binding to work.
We need objects hierarchy to find ancestor.

@todo In future we could support more generic solution, where hierarchy would be provided by user.
For example we could use predefined property "Parent" to resolve hierarchy. Other solution is to provide
property name pointing to parent in AncestorBindingExpression constructor.

@ingroup DataBindingSystem*/
class AncestorBindingExpression : public BindingExpression
{
private:

	TypeID				m_ancestorType;
	uint16				m_ancestorLevels;

protected:
public:
	
	explicit		AncestorBindingExpression		( const std::string & bindingPath, TypeID ancestorType );
	explicit		AncestorBindingExpression		( const std::string & bindingPath, TypeID ancestorType, uint16 levels );
	explicit		AncestorBindingExpression		( TypeID ancestorType );
	explicit		AncestorBindingExpression		( TypeID ancestorType, uint16 levels );
	virtual			~AncestorBindingExpression		() = default;


	virtual Nullable< BindingTarget >		EvaluateExpression		( const rttr::variant& dataContext, const rttr::variant& propertyOwner ) const override;
	virtual BindingExpressionType			GetExpressionType		() const override;

public:

	static rttr::variant					FindAncestor			( const rttr::variant& propertyOwner, TypeID ancestorType, uint16 levels );
	static rttr::variant					FindAncestor			( const UIElement* control, TypeID ancestorType, uint16 levels );

};

DEFINE_PTR_TYPE( AncestorBindingExpression )

}	// gui
}	// sw

