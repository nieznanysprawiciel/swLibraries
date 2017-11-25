#pragma once
/**
@file DefaultBindingExpression.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Engine.
*/




#include "BindingExpression.h"


namespace sw {
namespace gui
{



/**@brief Evaluates binding expression by expanding path beginning from data context.
@ingroup DataBindingSystem*/
class DefaultBindingExpression : public BindingExpression
{
protected:
public:
	explicit		DefaultBindingExpression	( const std::string & bindingPath );
	virtual			~DefaultBindingExpression	() = default;


	virtual Nullable< BindingTarget >	EvaluateExpression		( const rttr::variant & dataContext, const rttr::variant & propertyOwner ) const override;
	virtual BindingExpressionType		GetExpressionType		() const override;

public:

	static Nullable< BindingTarget >	EvaluateRelativeProperty	( const rttr::variant & dataContext, const std::string & path );

};

DEFINE_PTR_TYPE( DefaultBindingExpression )


}	// gui
}	// sw

