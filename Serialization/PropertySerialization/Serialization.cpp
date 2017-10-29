/**
@file Serialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Serialization/PropertySerialization/stdafx.h"
#include "Serialization.h"

#include <codecvt>



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
void			Serialization::InitializeContext		( SerializationContext* ctx )
{}

//====================================================================================//
//			Serialization	
//====================================================================================//


// ================================ //
//
bool			Serialization::Serialize				( const filesystem::Path& filePath, const EngineObject* object )
{
	return false;
}

}	// sw


