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
MockInputLayout::MockInputLayout	( const AssetPath& fileName )
	:	ShaderInputLayout( fileName )
{}

// ================================ //
//
sw::Nullable< MockInputLayout* >		MockInputLayout::CreateLayout		( const AssetPath& fileName, const InputLayoutDescriptor& layoutDesc )
{
	return new MockInputLayout( fileName );
}

// ================================ //
//
MockInputLayout::~MockInputLayout()
{}

}	// sw