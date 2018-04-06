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
That's why we have one m_binding field, which binds target to source.

Other properties can treat this property as source. All bound properties are listed in m_boundProperties vector.

@todo Minimize memory footprint, for example we could do something with m_property and m_binding.

@ingroup DataBindingSystem*/
class BindingInfo
{
public:

	BindingPtr				m_binding;
	rttr::property			m_property;			///< Property that owns this binding and other properties are bound to.
	BindingsVec				m_boundProperties;	///< All properties receiving values from this one.


public:

	explicit			BindingInfo			( const BindingPtr& binding );
	explicit			BindingInfo			( const rttr::property& property );

	void				PropagateToSource	();
	void				PropagateToTarget	();

	void				AddBindingLink		( const BindingInfoPtr& info );

public:

	rttr::property		GetProperty			() const { return m_property; }
};



}	// gui
}	// sw



