#pragma once


#include "swCommonLib/Common/RTTR.h"

#include "BindingMode.h"
#include "Expressions/BindingExpression.h"
#include "Binding.h"


#include <string>
#include <vector>



namespace sw {
namespace gui
{

struct BindingInfo;
DEFINE_PTR_TYPE( BindingInfo )

typedef std::vector< BindingInfoPtr > BindingsVec;


/**@brief Holds information about all bindings to property.

This class describes bindings of single property. Target property can be bound to only one source property.
That's why we have one PropertyBinding field, which binds target to source.

Other properties can treat this property as source. All bound properties are listed in BoundProperties vector.

@ingroup DataBindingSystem*/
struct BindingsInfo
{
	BindingPtr				PropertyBinding;
	BindingsVec				BoundProperties;	///< All properties receiving values from this one.
};



}	// gui
}	// sw



