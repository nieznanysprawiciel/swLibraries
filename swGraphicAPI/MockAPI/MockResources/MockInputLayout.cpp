/**
@file MockInputLayout.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "MockInputLayout.h"



RTTR_REGISTRATION
{
	rttr::registration::class_< sw::MockInputLayout >( "sw::MockInputLayout" );
}



namespace sw
{

// ================================ //
//
MockInputLayout::MockInputLayout()
{}

// ================================ //
//
sw::Nullable< MockInputLayout* >		MockInputLayout::CreateLayout		( const InputLayoutDescriptor& layoutDesc )
{
	return new MockInputLayout();
}

// ================================ //
//
MockInputLayout::~MockInputLayout()
{}

}	// sw