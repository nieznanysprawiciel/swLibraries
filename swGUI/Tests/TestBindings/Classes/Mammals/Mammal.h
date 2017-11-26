#pragma once

#include "swGUI/Tests/TestBindings/Classes/Animal.h"
#include "swGUI/Tests/TestBindings/Classes/Components/PhysicalProperties.h"



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
	virtual			~Mammal		() = default;

};



}	// sw

