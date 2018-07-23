#pragma once

#include "swCommonLib/Common/RTTR.h"

#include <string>


namespace sw
{

/**@defgroup Tests
@brief Testing environment, classes helpers.*/

/**@defgroup TestClassHierarchy Test Classes Hierarchy
@ingroup Tests
@brief Example class hierarchy with rttr properties which can be used in different tests scenarios.

@todo Extract all classes to different library which can be freely linked to any project.
Move to swCommonLibrary.*/


/**@brief Base animal class.
@ingroup TestClassHierarchy*/
class Animal
{
	RTTR_ENABLE();
	RTTR_REGISTRATION_FRIEND;
private:

	std::string			m_name;
	uint16				m_age;

protected:
public:
	explicit		Animal		() = default;
	explicit		Animal		( const std::string & name );
	virtual			~Animal		();

};


int		LinkRegistration	();


}	// sw


