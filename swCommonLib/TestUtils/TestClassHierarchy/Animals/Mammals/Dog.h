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
	explicit		Dog			( std::string name, uint16 age, std::string race );
	virtual			~Dog		() = default;

};

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline Dog::Dog		( std::string name, uint16 age, std::string race )
	:	Mammal( name, age )
	,	m_race( race )
{}


}	// sw


