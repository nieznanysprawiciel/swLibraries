/**
@file EngineObject.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swSerialization/Serialization/stdafx.h"

#include "swSerialization/Serialization/EngineObject.h"

///< @todo This is hack - reference to external library that is not dependency.
///< Remove this in future.
#include "swSerialization/Serialization/Serialization.h"




RTTR_REGISTRATION
{
    using namespace rttr;
	
	registration::class_< sw::EngineObject >( "sw::EngineObject" );
}


namespace sw
{

// ================================ //
//
void		EngineObject::Serialize			( ISerializer& ser ) const
{
	SerializationCore::DefaultSerialize( ser, this );
}

// ================================ //
//
void		EngineObject::Deserialize		( const IDeserializer& deser )
{
	SerializationCore::DefaultDeserialize( deser, this );
}

}	// sw

