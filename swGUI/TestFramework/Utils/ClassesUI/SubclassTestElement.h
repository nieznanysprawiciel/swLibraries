#pragma once

#include "TestUIElementClass.h"



/**@brief */
class SubclassTestElement : public TestUIElementClass
{
	RTTR_ENABLE( TestUIElementClass );
	RTTR_REGISTRATION_FRIEND;
private:

	uint32			m_number;

public:


};

