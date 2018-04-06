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
		m_binding->PropagateToTarget();

	for( auto& binding : m_boundProperties )
	{
		binding->PropagateToSource();
	}
}

// ================================ //
//
void			BindingInfo::AddBindingLink			( const BindingInfoPtr& info )
{
	m_boundProperties.push_back( info );
}


}	// gui
}	// sw


