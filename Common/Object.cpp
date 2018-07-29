/**
@file Object.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Object.h"




RTTR_REGISTRATION
{
    using namespace rttr;
	
	registration::class_< Object >( "Object" );
}



// ================================ //
//
Size			Object::MemorySize		() const
{ 
	return this->get_type().get_sizeof();
}



