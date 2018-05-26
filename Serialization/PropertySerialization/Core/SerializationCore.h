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
	static bool				IsPolymorphicType		( TypeID type );
	
	static void				DefaultSerialize		( ISerializer& ser, const EngineObject* object );
	static void				DefaultDeserialize		( const IDeserializer& deser, EngineObject* object );

	static void				DefaultSerializeImpl	( ISerializer& ser, const rttr::instance& object, rttr::type dynamicType );
	static void				DefaultDeserializeImpl	( const IDeserializer& deser, const rttr::instance& object, rttr::type dynamicType );

	///@name Types serialization
	///@{

	/**@brief Serialize basic arithemtic types and bool.*/
	static bool				SerializeBasicTypes		( ISerializer& ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeVectorTypes	( ISerializer& ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeStringTypes	( ISerializer& ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeEnumTypes		( ISerializer& ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeArrayTypes		( ISerializer& ser, const rttr::instance& object, rttr::property& prop );
	static bool				SerializeObjectTypes	( ISerializer& ser, const rttr::instance& object, rttr::property& prop );

	static bool				SerializeBasicTypes		( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue );
	///@}

	static void				SerializePolymorphic	( ISerializer& ser, const rttr::instance& object, rttr::property& prop );
	static void				SerializePropertiesVec	( ISerializer& ser, const rttr::instance& object, std::vector< rttr::property >& properties );

	///@name Types deserialization
	///@{

	/**@brief Deserialize basic arithemtic types and bool.*/
	static bool				DeserializeBasicTypes	( const IDeserializer& deser, const rttr::instance& object, rttr::property& prop );
	static bool				DeserializeVectorTypes	( const IDeserializer& deser, const rttr::instance& object, rttr::property& prop );
	static bool				DeserializeStringTypes	( const IDeserializer& deser, const rttr::instance& object, rttr::property& prop );
	static bool				DeserializeEnumTypes	( const IDeserializer& deser, const rttr::instance& object, rttr::property& prop );
	static bool				DeserializeArrayTypes	( const IDeserializer& deser, const rttr::instance& object, rttr::property& prop );
	static bool				DeserializeObjectTypes	( const IDeserializer& deser, const rttr::instance& object, rttr::property& prop );

	///@}

	static void				DeserializePolymorphic		( const IDeserializer& deser, const rttr::instance& object, rttr::property& prop );
	static void				DeserializeNotPolymorphic	( const IDeserializer& deser, const rttr::instance& object, rttr::property& prop );
	static rttr::variant	CreateInstance				( TypeID type );


	static std::string		WstringToUTF		( const std::wstring& str );
	static std::wstring		UTFToWstring		( const std::string& str );

	template< typename PropertyType >
	static PropertyType		GetPropertyValue	( rttr::property prop, const rttr::instance& object );

	template< typename PropertyType >
	static void				SerializeProperty	( ISerializer& ser, rttr::property prop, const rttr::instance& object );

	template< typename PropertyType >
	static void				SerializeProperty	( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue );


	template<>	static void				SerializeProperty< EngineObject* >			( ISerializer& ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< void* >					( ISerializer& ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< DirectX::XMFLOAT2* >		( ISerializer& ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< DirectX::XMFLOAT3* >		( ISerializer& ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< DirectX::XMFLOAT4* >		( ISerializer& ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< std::wstring >			( ISerializer& ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< char >					( ISerializer& ser, rttr::property prop, const rttr::instance& object );

	template<>	static void				SerializeProperty< char >					( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue );


	template< typename PropertyType >
	static void				SetPropertyValue	( rttr::property prop, const rttr::instance& object, PropertyType value );

	template< typename PropertyType >
	static void				DeserializeProperty	( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );


	template<>	static void				DeserializeProperty< EngineObject* >		( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< void* >				( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< DirectX::XMFLOAT2* >	( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< DirectX::XMFLOAT3* >	( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< DirectX::XMFLOAT4* >	( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< std::wstring >			( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< char >					( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );

	/**@brief Gets real type of the object that means most derived and wrapped type.*/
	static TypeID						GetRealType			( const rttr::instance& object );

	/**@brief Gets wrapped type. If type isn't wrapper it returns it unmodified.*/
	static TypeID						GetWrappedType			( TypeID type );

	/**@brief First extracts wrapped type and then returns raw type.*/
	static TypeID						GetRawWrappedType		( TypeID type );
};


}	// sw


#include "SerializationCore.inl"
