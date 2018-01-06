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
@ingroup DataBindingSystem*/
struct BindingsInfo
{
	BindingPtr				PropertyBinding;
	rttr::variant			TargetObject;		///< Object owning this BindingsInfo.
	BindingsVec				BoundProperties;	///< All properties receiving values from this one.
};



}	// gui
}	// sw



