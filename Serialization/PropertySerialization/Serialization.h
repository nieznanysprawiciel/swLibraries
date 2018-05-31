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

/**@defgroup Serialization Serialization
@ingroup CommonLibrary
@brief Automatic serialization library based on rttr properties.

@see @ref Page_Serialization "Serialization Reference"*/



/**@page Page_Serialization Serialization

@section Serialization_General General

Serialization library uses RTTR information to serialize classes. Remember to register
your classes in RTTR before using these serialization functionalities.

@section Serialization_ChoosingSerializer Choosing serializer

Serializer can be chosen at link time. Add one of serializers projects (SerializerJSON or SerializerXML) as referenced project.
This behavior may change in future version and serializers will be rewritten to implement common interface.

@section Serialization_Usage Usage Examples

@subsection Serialization_Usage_Serialization Serialization

@code{.cpp}
BaseObject object;
sw::Serialization serial;

bool success = serial.Serialize( "Serialization/GenericObject.xml", object );
@endcode

@subsection Serialization_Usage_Deserialization Deserialization

@code{.cpp}
BaseObject object;
sw::Serialization deserial;

bool success = deserial.Deserialize( "Serialization/GenericObject.xml", object );
@endcode

@section Serialization_FuturePlans Future plans

Serialization library is still in development process. There're many things that should be covered in
future versions:

- Deserialization of polymorphic types not derived from sw::EngineObject.
- Arrays habdling:
	- Serialization/deserialization of arrays nested in arrays (array ranks).
	- Arrays with basic types (ints, floats and so on).
	- Arrays with polymorphic types that need creation.
- Serialization/deserialization of associative containers from stl.
- Better handling of wrapped types:
	- Setting objects for Properties with mixed wrapped and raw pointer types.
	- Handling wrappers that don't take ownership of pointers (especially destroying these types).
- Implementing hooks for overriding serialization/deserialization for specified types.
- Better documentation ;)

@see @ref Serialization*/



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

	/**@brief Deserialize object from file.*/
	template< typename Type >
	bool			Deserialize			( const filesystem::Path& filePath, const Type& object );

	/**@brief Deserialize object to provided serializer.
	This deserialization doesn't write it's output anywhere.

	@note Deserializer must be initialized with context which is derived from SerializationContext.*/
	template< typename Type >
	bool			Deserialize			( IDeserializer& deser, Type& object );

private:

	void			InitializeContext	( SerializationContext* ctx );
};





}	// sw


#include "Serialization.inl"
