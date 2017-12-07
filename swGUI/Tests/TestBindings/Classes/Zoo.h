#pragma once

#include "swCommonLib/Common/RTTR.h"

#include "swGUI/Tests/TestBindings/Classes/Mammals/HomoSapiens.h"

namespace sw
{


/**@brief Zoo.
@ingroup TestClassHierarchy*/
class Zoo
{
	RTTR_ENABLE();
	RTTR_REGISTRATION_FRIEND;
public:

	HomoSapiensPtr		m_owner;
	HomoSapiens*		m_director;

public:

	explicit			Zoo	()
		: m_director( nullptr )
	{}


};



}	// sw

