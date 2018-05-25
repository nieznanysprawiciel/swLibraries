/**
@file SerialziationException.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Serialization/PropertySerialization/stdafx.h"
#include "SerializationException.h"

#include "swCommonLib/Common/Converters.h"


namespace sw
{

// ================================ //
//
std::string			SerializationException::ErrorMessage		() const
{
	return PrintLineNumber() + RuntimeException::ErrorMessage();
}

// ================================ //
//
std::string			SerializationException::PrintLineNumber		() const
{
    // Note: Lines are numbered beginning from 1. If we got 0 here,
    // position information is useless and we can ommit it.
    if( m_filePosition.Line != 0 )
        return "Line: [" + Convert::ToString( m_filePosition.Line ) + "] Column: [" + Convert::ToString( m_filePosition.CharPosition ) + "]. ";

    return std::string();
}

// ================================ //
//
std::string			SerializationException::PrintWarning		() const
{
	return "Serialization Warning. ";
}

// ================================ //
//
std::string			SerializationException::PrintError			() const
{
	return "Serialization Error. ";
}

}	// sw
