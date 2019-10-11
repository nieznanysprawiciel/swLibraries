#include "Animal.h"

#include "Mammals/Mammal.h"
#include "Mammals/Dog.h"
#include "Mammals/HomoSapiens.h"

#include "Zoo.h"

//====================================================================================//
// Whole registration happens in one file, beacause visual studio can ommit unused code
// and registration doesn't seem to be used.
//====================================================================================//


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::Animal >( "sw::Animal" )
		.property( "Name", &sw::Animal::m_name ) BIND_AS_REF
		.property( "Age", &sw::Animal::m_age );

	rttr::registration::class_< sw::Mammal >( "sw::Mammal" )
		.property( "PhysicalProperties", &sw::Mammal::m_physicalProperties ) BIND_AS_PTR;

	rttr::registration::class_< sw::HomoSapiens >( "sw::HomoSapiens" );

	rttr::registration::class_< sw::Dog >( "sw::Dog" )
		.property( "Race", &sw::Dog::m_race ) BIND_AS_REF;

	rttr::registration::class_< sw::PhysicalProperties >( "sw::PhysicalProperties" )
		.property( "Weight", &sw::PhysicalProperties::Weight )
		.property( "Length", &sw::PhysicalProperties::Length )
		.property( "Height", &sw::PhysicalProperties::Height );

	rttr::registration::class_< sw::Zoo >( "sw::Zoo" )
		.property( "Owner", &sw::Zoo::m_owner )
		.property( "Director", &sw::Zoo::m_director );
}


// ================================ //
// Add this function to pull registration code into library.
int			sw::LinkRegistration()
{
	return 0;
}



// ================================ //
//
sw::Animal::Animal	( const std::string & name )
	:	m_name( name )
{}

// ================================ //
//
sw::Animal::Animal	( const std::string& name, uint16 age )
	:	m_name( name )
	,	m_age( age )
{}

// ================================ //
//
sw::Animal::~Animal()
{}
