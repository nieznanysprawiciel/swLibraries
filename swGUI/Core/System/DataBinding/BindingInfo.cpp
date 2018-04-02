#include "BindingInfo.h"




namespace sw {
namespace gui
{


// ================================ //
//
BindingInfo::BindingInfo		( const BindingPtr & binding )
	: m_propertyBinding( binding )
{}


// ================================ //
//
void			BindingInfo::PropagateToSource		()
{
	m_propertyBinding->PropagateToSource();

	for( auto& binding : m_boundProperties )
	{
		binding->PropagateToTarget();
	}
}


// ================================ //
//
void			BindingInfo::PropagateToTarget		()
{
	assert( !"Implement me" );
}


}	// gui
}	// sw


