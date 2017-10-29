#pragma once
/**
@file Serialization.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"
#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Serialization/Serializer.h"
#include "swCommonLib/Serialization/Deserializer.h"

#include "swCommonLib/Serialization/PropertySerialization/EngineSerializationContext.h"
#include <DirectXMath.h>
#include <string>


#include "swCommonLib/System/Path.h"
#include "swCommonLib/System/Dir.h"

#include "SerializationContext.h"
#include "Core/SerializationCore.h"


namespace sw
{

/**@brief Main object which performs serialization and deserialization.

@ingroup Serialization*/
class Serialization
{
private:

	SerializationContextPtr		m_context;

protected:
public:

	/**@brief Creates serialization object with default serialization context. If your serialization
	needs custom context use other overload of this function.*/
	explicit		Serialization		();

	/**@brief Creates serialization object with custom context.*/
	explicit		Serialization		( SerializationContextPtr ctx );

	~Serialization		() = default;


	/**@brief Serialize to file.*/
	bool			Serialize			( const filesystem::Path& filePath, const EngineObject* object );

	/**@brief Serialize object to file.*/
	template< typename Type >
	bool			Serialize			( const filesystem::Path& filePath, const Type& object );

	/**@brief Serialize object to provided serializer.
	This serialization doesn't write it's output anywhere.

	@note Serializer must be initialized with context which is derived from SerializationContext.*/
	template< typename Type >
	bool			Serialize			( ISerializer& ser, const Type& object );

private:

	void			InitializeContext	( SerializationContext* ctx );
};





}	// sw


#include "Serialization.inl"
