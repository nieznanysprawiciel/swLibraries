#pragma once

#include "Mammal.h"



namespace sw
{


/**@brief Dog
@ingroup TestClassHierarchy*/
class Dog : public Mammal
{
	RTTR_ENABLE( Mammal );
	RTTR_REGISTRATION_FRIEND;
private:

	std::string		m_race;

protected:
public:
	explicit		Dog			() = default;
	virtual			~Dog		() = default;

};



}	// sw


