#pragma once
/**
@file SerialziationCore.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/RTTR.h"

#include "swCommonLib/Common/Object.h"
#include "swSerialization/Interfaces/Serializer.h"
#include "swSerialization/Interfaces/Deserializer.h"

#include "swSerialization/Serialization/SerializationContext.h"
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

	static const std::vector< rttr::property >&		GetTypeFilteredProperties	( rttr::type objType, SerializationContext* context );


	static bool				ShouldSave				( rttr::property prop, MetaDataType saveFlag );
	static bool				IsPolymorphicType		( TypeID type );
	
	static void				DefaultSerialize		( ISerializer& ser, const Object* object );
	static void				DefaultDeserialize		( const IDeserializer& deser, Object* object );

	static void				DefaultSerializeImpl	( ISerializer& ser, const rttr::instance& object, rttr::type dynamicType );
	static void				DefaultDeserializeImpl	( const IDeserializer& deser, const rttr::instance& object, rttr::type dynamicType );

	///@name Types serialization
	///@{

	/**@brief Serialize basic arithemtic types and bool.*/
	static bool				SerializeBasicTypes		( ISerializer& ser, const rttr::instance& object, rttr::property prop );
	static bool				SerializeStringTypes	( ISerializer& ser, const rttr::instance& object, rttr::property prop );
	static bool				SerializeEnumTypes		( ISerializer& ser, const rttr::instance& object, rttr::property prop );
	static bool				SerializeArrayTypes		( ISerializer& ser, const rttr::instance& object, rttr::property prop );
	static bool				SerializeObjectTypes	( ISerializer& ser, const rttr::instance& object, rttr::property prop );

	static bool				SerializeBasicTypes		( ISerializer& ser, rttr::string_view name, const rttr::variant& value );
    static bool				SerializeStringTypes	( ISerializer& ser, rttr::string_view name, const rttr::variant& value );
    static bool				SerializeEnumTypes		( ISerializer& ser, rttr::string_view name, const rttr::variant& value );
    static bool				SerializeArrayTypes		( ISerializer& ser, rttr::string_view name, const rttr::variant& value );
    static bool				SerializeObjectTypes	( ISerializer& ser, rttr::string_view name, const rttr::variant& value );
	///@}

    static void				SerializeObject     	( ISerializer& ser, rttr::string_view name, const rttr::variant& value );
    static void				SerializePolymorphic	( ISerializer& ser, rttr::string_view name, const rttr::variant& value );
	static void				SerializePolymorphic	( ISerializer& ser, const rttr::instance& object, rttr::property prop );
	static void				SerializeNotPolymorphic	( ISerializer& ser, const rttr::instance& object, rttr::property prop );
	static void				SerializePropertiesVec	( ISerializer& ser, const rttr::instance& object, const std::vector< rttr::property >& properties );

	///@name Types deserialization
	///@{

	/**@brief Deserialize basic arithemtic types and bool.*/
	static bool				DeserializeBasicTypes	( const IDeserializer& deser, const rttr::instance& object, rttr::property prop );
	static bool				DeserializeStringTypes	( const IDeserializer& deser, const rttr::instance& object, rttr::property prop );
	static bool				DeserializeEnumTypes	( const IDeserializer& deser, const rttr::instance& object, rttr::property prop );
	static bool				DeserializeArrayTypes	( const IDeserializer& deser, const rttr::instance& object, rttr::property prop );
	static bool				DeserializeObjectTypes	( const IDeserializer& deser, const rttr::instance& object, rttr::property prop );

	///@}

	static void				DeserializePolymorphic		( const IDeserializer& deser, const rttr::instance& object, rttr::property prop );
	static void				DeserializeNotPolymorphic	( const IDeserializer& deser, const rttr::instance& object, rttr::property prop );
	
	static rttr::variant	CreateAndSetObjectProperty	( const IDeserializer& deser, const rttr::instance& object, rttr::property prop, TypeID dynamicType );
	static rttr::variant	CreateInstance				( TypeID type );


	static std::string		WstringToUTF		( const std::wstring& str );
	static std::wstring		UTFToWstring		( const std::string& str );

	template< typename PropertyType >
	static PropertyType		GetPropertyValue	( rttr::property prop, const rttr::instance& object );

	template< typename PropertyType >
	static void				SerializeProperty	( ISerializer& ser, rttr::property prop, const rttr::instance& object );

	template< typename PropertyType >
	static void				SerializeProperty	( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue );


	template<>	static void				SerializeProperty< std::wstring >			( ISerializer& ser, rttr::property prop, const rttr::instance& object );
	template<>	static void				SerializeProperty< char >					( ISerializer& ser, rttr::property prop, const rttr::instance& object );

	template<>	static void				SerializeProperty< char >					( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue );
    template<>	static void				SerializeProperty< std::wstring >			( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue );


	template< typename PropertyType >
	static void				SetPropertyValue	( rttr::property prop, const rttr::instance& object, PropertyType value );

	template< typename PropertyType >
	static void				DeserializeProperty	( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );


	template<>	static void				DeserializeProperty< std::wstring >			( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
	template<>	static void				DeserializeProperty< char >					( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );

	/**@brief Gets real type of the object that means most derived and wrapped type.*/
	static TypeID						GetRealType			( const rttr::instance& object );

	/**@brief Gets wrapped type. If type isn't wrapper it returns it unmodified.*/
	static TypeID						GetWrappedType			( TypeID type );

	/**@brief First extracts wrapped type and then returns raw type.*/
	static TypeID						GetRawWrappedType		( TypeID type );

	/**@brief Returns SerialziationContext from deserializer.*/
	static SerializationContext*		Context					( const IDeserializer& deser );

	/**@brief Destroy object in variant.*/
	static void							DestroyObject			( rttr::variant& object );
};


}	// sw


#include "SerializationCore.inl"
