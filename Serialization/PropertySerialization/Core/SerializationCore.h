#pragma once
/**
@file SerialziationCore.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"
#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Serialization/Serializer.h"
#include "swCommonLib/Serialization/Deserializer.h"

#include "swCommonLib/Serialization/PropertySerialization/SerializationContext.h"
#include <DirectXMath.h>
#include <string>




namespace sw
{


/**@brief Core serialization/deserialization functions.

This class is usefull only if you write your own serialization implementation.

@ingroup Serialization*/
class SerializationCore
{
public:

	static std::vector< rttr::property >&		GetTypeFilteredProperties	( rttr::type objType, SerializationContext* context );


	static bool				ShouldSave				( const rttr::property& prop, MetaDataType saveFlag );
	
	static void				DefaultSerialize		( ISerializer& ser, const EngineObject* object );
	static void				DefaultDeserialize		( IDeserializer& deser, EngineObject* object );

	static void				DefaultSerializeImpl	( ISerializer& ser, const rttr::instance& object, rttr::type dynamicType );
	static void				DefaultDeserializeImpl	( IDeserializer& deser, const rttr::instance& object, rttr::type dynamicType );

	///@name Types serialization
	///@{

	/**@brief Serialize basic arithemtic types and bool.*/
	static bool				SerializeBasicTypes		( ISerializer* ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeVectorTypes	( ISerializer* ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeStringTypes	( ISerializer* ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeEnumTypes		( ISerializer* ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeArrayTypes		( ISerializer* ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeObjectTypes	( ISerializer& ser, const rttr::instance& object, rttr::property& prop );

	static bool				SerializeBasicTypes		( ISerializer* ser, rttr::string_view name, const rttr::variant& propertyValue );
	///@}


	static void				SerializePropertiesVec	( ISerializer* ser, const rttr::instance& object, std::vector< rttr::property >& properties );

	///@name Types deserialization
	///@{

	/**@brief Deserialize basic arithemtic types and bool.*/
	static bool				DeserializeBasicTypes	( IDeserializer* deser, const rttr::instance& object, rttr::property& prop );
	static bool				DeserializeVectorTypes	( IDeserializer* deser, const rttr::instance& object, rttr::property& prop );
	static bool				DeserializeStringTypes	( IDeserializer* deser, const rttr::instance& object, rttr::property& prop );
	static bool				DeserializeEnumTypes	( IDeserializer* deser, const rttr::instance& object, rttr::property& prop );
	static bool				DeserializeArrayTypes	( IDeserializer* deser, const rttr::instance& object, rttr::property& prop );
	static bool				DeserializeObjectTypes	( IDeserializer* deser, const rttr::instance& object, rttr::property& prop );

	///@}

	static std::string		WstringToUTF		( const std::wstring& str );
	static std::wstring		UTFToWstring		( const std::string& str );

	template< typename PropertyType >
	static PropertyType		GetPropertyValue	( rttr::property prop, const rttr::instance& object );

	template< typename PropertyType >
	static void				SerializeProperty	( ISerializer* ser, rttr::property prop, const rttr::instance& object );

	template< typename PropertyType >
	static void				SerializeProperty	( ISerializer* ser, rttr::string_view name, const rttr::variant& propertyValue );


	template<>	static void				SerializeProperty< EngineObject* >			( ISerializer* ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< void* >					( ISerializer* ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< DirectX::XMFLOAT2* >		( ISerializer* ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< DirectX::XMFLOAT3* >		( ISerializer* ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< DirectX::XMFLOAT4* >		( ISerializer* ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< std::wstring >			( ISerializer* ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< char >					( ISerializer* ser, rttr::property prop, const rttr::instance& object );

	template<>	static void				SerializeProperty< char >					( ISerializer* ser, rttr::string_view name, const rttr::variant& propertyValue );


	template< typename PropertyType >
	static void				SetPropertyValue	( rttr::property prop, const rttr::instance& object, PropertyType value );

	template< typename PropertyType >
	static void				DeserializeProperty	( IDeserializer* deser, rttr::property prop, const rttr::instance& object );


	template<>	static void				DeserializeProperty< EngineObject* >		( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< void* >				( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< DirectX::XMFLOAT2* >	( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< DirectX::XMFLOAT3* >	( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< DirectX::XMFLOAT4* >	( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< std::wstring >			( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< char >					( IDeserializer* deser, rttr::property prop, const rttr::instance& object );

	/**@brief Gets real type of the object that means most derived and wrapped type.*/
	static TypeID						GetRealType			( const rttr::instance& object );

	/**@brief Gets wrapped type. If type isn't wrapper it returns it unmodified.*/
	static TypeID						GetWrappedType			( TypeID type );
};


}	// sw


#include "SerializationCore.inl"
