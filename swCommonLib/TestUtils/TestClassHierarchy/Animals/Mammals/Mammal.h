#pragma once

#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Animal.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Components/PhysicalProperties.h"



namespace sw
{


/**@brief Base mammal class.
@ingroup TestClassHierarchy*/
class Mammal : public Animal
{
	RTTR_ENABLE( Animal );
	RTTR_REGISTRATION_FRIEND;
private:
public:

	PhysicalProperties		m_physicalProperties;

public:
	explicit		Mammal		() = default;
	explicit		Mammal		( std::string name, uint16 age );
	virtual			~Mammal		() = default;

};


//====================================================================================//
//			Implementation
//====================================================================================//

// ================================ //
//
inline Mammal::Mammal		( std::string name, uint16 age )
	:	Animal( name, age )
{}



}	// sw

