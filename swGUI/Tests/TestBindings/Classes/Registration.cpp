#include "Animal.h"

#include "Mammals/Mammal.h"
#include "Mammals/Dog.h"


//====================================================================================//
// Whole registration happens in one file, beacause visual studio can ommit unused code
// and registration doesn't seem to be used.
//====================================================================================//


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::Animal >( "sw::Animal" )
		.property( "Name", &sw::Animal::m_name ) BIND_AS_REF
		.property( "Age", &sw::Animal::m_age );

	rttr::registration::class_< sw::Mammal >( "sw::Mammal" );

	rttr::registration::class_< sw::Dog >( "sw::Dog" )
		.property( "Race", &sw::Dog::m_race ) BIND_AS_REF;
}


// ================================ //
//
sw::Animal::Animal	( const std::string & name )
	:	m_name( name )
{}

// ================================ //
// Add one class to pull registration code into library.
sw::Animal::~Animal()
{}
