/**
@file BindingInfo.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "BindingInfo.h"




namespace sw {
namespace gui
{


// ================================ //
//
BindingInfo::BindingInfo		( const BindingPtr& binding )
	: m_binding( binding )
	, m_property( binding->GetTargetProperty() )
{}

// ================================ //
//
BindingInfo::BindingInfo		( const rttr::property& property )
	: m_property( property )
{}


// ================================ //
//
void			BindingInfo::PropagateToSource		()
{
	if( m_binding )
		m_binding->PropagateToSource();

	for( auto& binding : m_boundProperties )
	{
		binding->PropagateToTarget();
	}
}


// ================================ //
//
void			BindingInfo::PropagateToTarget		()
{
	if( m_binding )
	{
		// Note: Propagate value further only if this property changed.
		if( m_binding->PropagateToTarget() )
		{
			for( auto& binding : m_boundProperties )
			{
				binding->PropagateToSource();
			}
		}
	}
}

// ================================ //
//
void			BindingInfo::AddBindingLink			( const BindingInfoPtr& info )
{
	m_boundProperties.push_back( info );
}

// ================================ //
//
void			BindingInfo::SetBinding				( const BindingPtr& binding )
{
	assert( m_binding == nullptr );
	m_binding = binding;
}


}	// gui
}	// sw


