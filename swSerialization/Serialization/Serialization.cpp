/**
@file Serialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swSerialization/Serialization/stdafx.h"
#include "Serialization.h"

#include <codecvt>



RTTR_REGISTRATION
{

    rttr::registration::enumeration< sw::SerializationMeta >( "sw::SerializationMeta" )
        (
            rttr::value( "Serialize", sw::SerializationMeta::Serialize )
        );

}


namespace sw
{


//====================================================================================//
//			Initialziation	
//====================================================================================//

// ================================ //
//
Serialization::Serialization		()
	:	m_context( new SerializationContext )
{
	InitializeContext( m_context.get() );
}

// ================================ //
//
Serialization::Serialization		( SerializationContextPtr ctx )
	:	m_context( ctx )
{
	InitializeContext( m_context.get() );
}

// ================================ //
//
OverridesSerial&        Serialization::SerialOverride   ()
{
    return m_context->SerialOverrides;
}

// ================================ //
//
OverridesDeserial&      Serialization::DeserialOverride ()
{
    return m_context->DeserialOverrides;
}

// ================================ //
//
void			Serialization::InitializeContext		( SerializationContext* ctx )
{}

//====================================================================================//
//			Serialization	
//====================================================================================//


// ================================ //
//
bool			Serialization::Serialize				( const filesystem::Path& filePath, const Object* object )
{
	return false;
}

}	// sw


