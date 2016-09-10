#pragma once

#include "Common/EngineObject.h"
#include "Common/RTTR.h"
#include "Common/Serialization/Serializer.h"
#include "Common/Serialization/Deserializer.h"

#include "Common/Serialization/SW/EngineSerializationContext.h"

#include <DirectXMath.h>
#include <string>


class Serialization
{
public:

	static std::vector< rttr::property >&		GetTypeFilteredProperties	( rttr::type objType, EngineSerializationContext* context );


	static bool				ShouldSave				( rttr::property& prop, MetaDataType saveFlag );
	
	static void				DefaultSerialize		( ISerializer* ser, const EngineObject* object );
	static void				DefaultDeserialize		( IDeserializer* deser, EngineObject* object );

	static void				DefaultSerializeImpl	( ISerializer* ser, const rttr::instance& object, rttr::type dynamicType );

	static bool				SerializeBasicTypes		( ISerializer* ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeVectorTypes	( ISerializer* ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeStringTypes	( ISerializer* ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeEnumTypes		( ISerializer* ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeArrayTypes		( ISerializer* ser, const rttr::instance& object, rttr::property& prop );
	
	static void				SerializePropertiesVec	( ISerializer* ser, const rttr::instance& object, std::vector< rttr::property >& properties );

	static bool				DeserializeBasicTypes	( IDeserializer* deser, const EngineObject* object, rttr::property& prop );
	static bool				DeserializeVectorTypes	( IDeserializer* deser, const EngineObject* object, rttr::property& prop );
	static bool				DeserializeStringTypes	( IDeserializer* deser, const EngineObject* object, rttr::property& prop );


	static std::string		WstringToUTF		( const std::wstring& str );
	static std::wstring		UTFToWstring		( const std::string& str );

	template< typename PropertyType >
	static PropertyType		GetPropertyValue	( rttr::property prop, const rttr::instance& object );

	template< typename PropertyType >
	static void				SerializeProperty	( ISerializer* ser, rttr::property prop, const rttr::instance& object );



	template<>	static void				SerializeProperty< EngineObject* >			( ISerializer* ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< void* >					( ISerializer* ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< DirectX::XMFLOAT2* >		( ISerializer* ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< DirectX::XMFLOAT3* >		( ISerializer* ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< DirectX::XMFLOAT4* >		( ISerializer* ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< std::wstring >			( ISerializer* ser, rttr::property prop, const rttr::instance& object );


	template< typename PropertyType >
	static void				SetPropertyValue	( rttr::property prop, const EngineObject* object, PropertyType value );

	template< typename PropertyType >
	static void				DeserializeProperty	( IDeserializer* deser, rttr::property prop, const EngineObject* object );


	template<>	static void				DeserializeProperty< DirectX::XMFLOAT2* >	( IDeserializer* deser, rttr::property prop, const EngineObject* object );
	template<>	static void				DeserializeProperty< DirectX::XMFLOAT3* >	( IDeserializer* deser, rttr::property prop, const EngineObject* object );
	template<>	static void				DeserializeProperty< DirectX::XMFLOAT4* >	( IDeserializer* deser, rttr::property prop, const EngineObject* object );
	template<>	static void				DeserializeProperty< std::wstring >			( IDeserializer* deser, rttr::property prop, const EngineObject* object );
};

#include "Serialization.inl"
