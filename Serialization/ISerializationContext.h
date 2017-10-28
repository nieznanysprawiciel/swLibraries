#pragma once

/**
@file ISerializationContext
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



/**@brief Interface for context used in serialization and deserialization.
@ingroup Serialization

ISerializationContext is used to store additional data during serialization and deserialization.
Classes derived from @ref EngineObject can provide their own implementation of Serialize and Deserialize function
which can retrive context by calling @ref ISerializer::GetContext or @ref IDeserializer::GetContext function.

You can derive from this class and set your object as context before serialization.
*/
struct ISerializationContext
{
public:

				ISerializationContext() = default;	///
	virtual		~ISerializationContext() = default;	///

};

DEFINE_PTR_TYPE( ISerializationContext )

