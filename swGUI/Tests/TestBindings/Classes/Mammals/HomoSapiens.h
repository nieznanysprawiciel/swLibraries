#pragma once

#include "swGUI/Tests/TestBindings/Classes/Mammals/Mammal.h"
#include "swGUI/Tests/TestBindings/Classes/Components/PhysicalProperties.h"



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

