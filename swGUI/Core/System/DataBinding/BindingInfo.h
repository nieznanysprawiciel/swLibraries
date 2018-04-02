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

class BindingInfo;
DEFINE_PTR_TYPE( BindingInfo )

typedef std::vector< BindingInfoPtr > BindingsVec;


/**@brief Holds information about all bindings to property.

This class describes bindings of single property. Target property can be bound to only one source property.
That's why we have one m_propertyBinding field, which binds target to source.

Other properties can treat this property as source. All bound properties are listed in m_boundProperties vector.

@ingroup DataBindingSystem*/
class BindingInfo
{
public:

	BindingPtr				m_propertyBinding;
	BindingsVec				m_boundProperties;	///< All properties receiving values from this one.


public:

	explicit			BindingInfo			( const BindingPtr & binding );

	void				PropagateToSource	();
	void				PropagateToTarget	();
};



}	// gui
}	// sw



