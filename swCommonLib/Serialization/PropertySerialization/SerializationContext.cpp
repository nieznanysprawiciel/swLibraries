/**
@file SerializationContext.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Serialization/PropertySerialization/stdafx.h"
#include "SerializationContext.h"


namespace sw
{



// ================================ //
//
const SerializationContext::Exceptions&			SerializationContext::GetWarnings		()
{
	return m_warnings;
}

// ================================ //
//
void			SerializationContext::AddWarning			( ExceptionPtr warning )
{
	m_warnings.push_back( warning );
}

}	// sw
