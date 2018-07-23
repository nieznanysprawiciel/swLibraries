#pragma once

#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Mammals/Mammal.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Components/PhysicalProperties.h"



namespace sw
{


/**@brief Class for people.
@ingroup TestClassHierarchy*/
class HomoSapiens : public Mammal
{
	RTTR_ENABLE( Mammal );
	RTTR_REGISTRATION_FRIEND;
private:
public:
	explicit		HomoSapiens		() = default;
	virtual			~HomoSapiens	() = default;

};

DEFINE_PTR_TYPE( HomoSapiens )


}	// sw

