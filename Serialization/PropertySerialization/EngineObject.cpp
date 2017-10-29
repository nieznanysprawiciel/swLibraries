/**
@file EngineObject.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Serialization/PropertySerialization/stdafx.h"

#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"
#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"




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
	//Serialization::DefaultSerialize( ser, this );
}

// ================================ //
//
void		EngineObject::Deserialize		( const IDeserializer& deser )
{
	//Serialization::DefaultDeserialize( deser, this );
}

}	// sw

