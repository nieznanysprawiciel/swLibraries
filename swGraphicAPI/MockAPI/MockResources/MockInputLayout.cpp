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
MockInputLayout::MockInputLayout	( const AssetPath& fileName, InputLayoutDescriptor layoutDesc )
	:	ShaderInputLayout( fileName )
    ,   m_desc( std::move( layoutDesc ) )
{}

// ================================ //
//
sw::Nullable< MockInputLayout* >		MockInputLayout::CreateLayout		( const AssetPath& fileName, const InputLayoutDescriptor& layoutDesc )
{
	return new MockInputLayout( fileName, layoutDesc );
}

const InputLayoutDescriptor&            MockInputLayout::GetDescriptor      () const
{
    return m_desc;
}

// ================================ //
//
MockInputLayout::~MockInputLayout()
{}

}	// sw