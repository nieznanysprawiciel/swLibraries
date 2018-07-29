#pragma once
/**
@file EngineObject.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Object.h"



class ISerializer;
class IDeserializer;



namespace sw
{

/**@brief Base class for serializable objects.

@ingroup Serialization*/
class EngineObject : public Object
{
	RTTR_ENABLE( Object )

public:

	/**@brief Implements default serialization.
	@detail Serializes only declared properties.*/
	virtual void		Serialize		( ISerializer& ser ) const;

	/**@brief Implements default deserialization.*/
	virtual void		Deserialize		( const IDeserializer& deser );
};


}	// sw

