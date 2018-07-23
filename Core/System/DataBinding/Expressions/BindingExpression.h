#pragma once
/**
@file BindingExpression.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Engine.
*/


#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/RTTR.h"

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include <string>


namespace sw {
namespace gui
{



/**@brief Evaluated binding result.
@ingroup DataBindingSystem*/
struct BindingTarget
{
	rttr::variant		Target;
	rttr::property		Property;

// ================================ //
//
	BindingTarget( const rttr::variant & target, const rttr::property & property )
		: Target( target )
		, Property( property )
	{}
};


/**@brief Binding expressions types.
@todo We should implement some other types here like Collection binding, StaticResource binding, ElementName...
@ingroup DataBindingSystem*/
enum class BindingExpressionType : uint8
{
	DataContext,			///< Find property by path beginning in current DataContext.
	StaticResource,			///< Bind to property of static resource defined in xml.
	Self,					///< Binding to property of the same object.
	FindAncestor,			///< Binding to one of ancestors in controls hierarchy.
	TemplatedParent,		///< Binding to control which the template is applied to.
	PreviousData,			///< Maybe won't be supported.
	ElementName				///< Find control by name.
};


/**@brief Class can evaluate binding address to right property and object.

@todo WPF bindings support fallback value in case that binding failed. We need to consider implementing it.
Find proper place for this value, propbably BindngExpression class.

@todo Support for priority bindings.

@todo How to handle multi binding ??

@ingroup DataBindingSystem*/
class BindingExpression
{
protected:

	std::string			m_path;

public:

	explicit			BindingExpression	( const std::string & bindingPath )
		: m_path( bindingPath )
	{}

	virtual				~BindingExpression	() {}

public:

	/**@brief Evaluates binding expression.
	
	@param[in] dataContext Data context where expression will start evaluation.
	@param[in] propertyOwner Owner control of property which is bound to source.
	@return Returns evaluated target object and property.*/
	virtual Nullable< BindingTarget >		EvaluateExpression		( const rttr::variant & dataContext, const rttr::variant & propertyOwner ) const = 0;


	/**@brief Gets expression type.*/
	virtual BindingExpressionType			GetExpressionType		() const = 0;

public:

	static Nullable< BindingTarget >		EvaluateRelativeProperty	( const rttr::variant & dataContext, const std::string & path );
};

DEFINE_PTR_TYPE( BindingExpression )


}	// gui
}	// sw
