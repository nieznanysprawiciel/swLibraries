#pragma once
/**
@file ISerializationContext.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Serialization/ISerializationContext.h"

#include <map>
#include <vector>


namespace sw
{


/**@brief Serialization context for automatic serialization.

You can extend serialization functionality by deriving from this class.

@ingroup Serialization*/
struct SerializationContext : public ISerializationContext
{
private:

	typedef std::map< rttr::type, std::vector< rttr::property > > TypePropertyMap;

public:


	TypePropertyMap			TypeProperties;		///< Maps containing all serializable properties for type.



public:
	virtual		~SerializationContext() = default;
};

DEFINE_PTR_TYPE( SerializationContext )


}	// sw


