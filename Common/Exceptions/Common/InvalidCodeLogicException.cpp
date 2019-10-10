/**
@file InvalidCodeLogicException.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "InvalidCodeLogicException.h"

#include "swCommonLib/Common/Converters.h"


namespace sw
{

// ================================ //
//
InvalidCodeLogicException::InvalidCodeLogicException						( std::string message, std::string filePath, uint32 line )
	:	RuntimeException( std::move( message ) )
	,	m_path( std::move( filePath ) )
	,	m_line( line )
{}

// ================================ //
//
std::string						InvalidCodeLogicException::ErrorMessage		() const
{
	return RuntimeException::ErrorMessage() + " We shouldn't be here. Code is invalid, check file [" + m_path + "], line " + Convert::ToString( m_line ) + ".";
}

// ================================ //
//
InvalidCodeLogicExceptionPtr	InvalidCodeLogicException::Create			( std::string message, std::string filePath, uint32 line )
{
	return std::make_shared< InvalidCodeLogicException >( std::move( message ), std::move( filePath ), line );
}

}	// sw

