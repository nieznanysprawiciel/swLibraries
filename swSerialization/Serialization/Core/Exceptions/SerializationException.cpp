/**
@file SerialziationException.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Serialization/stdafx.h"
#include "SerializationException.h"

#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/fmt.h"


namespace sw
{

// ================================ //
//
auto SerializationException::ErrorMessage           () const -> std::string
{
	return PrintLineNumber() + RuntimeException::ErrorMessage();
}

// ================================ //
//
auto SerializationException::PrintLineNumber		() const -> std::string
{
    // Note: Lines are numbered beginning from 1. If we got 0 here,
    // position information is useless and we can ommit it.
    if( m_filePosition.Line != 0 )
        return fmt::format( "Line: [{}] Column: [{}]. ", m_filePosition.Line, m_filePosition.CharPosition );

    return std::string();
}

// ================================ //
//
auto SerializationException::PrintWarning		    () const -> std::string
{
	return "Serialization Warning. ";
}

// ================================ //
//
auto SerializationException::PrintError			    () const -> std::string
{
	return "Serialization Error. ";
}

// ================================ //
//
auto SerializationException::Create
(
    std::string message,
    FilePosition filePos
) -> SerializationExceptionPtr
{
    return std::make_shared< SerializationException >( std::move( message ), filePos );
}

// ================================ //
//
auto SerializationException::Create
(
    const IDeserializer& deser,
    std::string message
) -> SerializationExceptionPtr
{
    return std::make_shared< SerializationException >( std::move( message ), deser.CurrentLineNumber() );
}

}	// sw
