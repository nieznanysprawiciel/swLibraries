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

#include "swSerialization/Serialization/Core/TypeDescriptor.h"
#include "swSerialization/Serialization/Core/VariantWrapper.h"

#include "swSerialization/Serialization/SerializationContext.h"


#include <string>




namespace sw
{


typedef std::vector< rttr::variant > VariantVec;


/**@brief Core serialization/deserialization functions.

This class is usefull only if you write your own serialization implementation.

@ingroup Serialization*/
class SerializationCore
{
public:

	static bool				IsPolymorphicType		( TypeID type );
	
	static void				DefaultSerialize		( ISerializer& ser, const Object* object );
	static void				DefaultDeserialize		( const IDeserializer& deser, Object* object );

	static void				DefaultSerializeImpl	( ISerializer& ser, const rttr::instance& object );
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

    static void				SerializeObject     	( ISerializer& ser, rttr::string_view name, const rttr::instance& value );
    static void				SerializePolymorphic	( ISerializer& ser, rttr::string_view name, const rttr::instance& value );
	static void				SerializePolymorphic	( ISerializer& ser, const rttr::instance& object, rttr::property prop );
	static void				SerializeNotPolymorphic	( ISerializer& ser, const rttr::instance& object, rttr::property prop );
	static void				SerializePropertiesVec	( ISerializer& ser, const rttr::instance& object, const std::vector< rttr::property >& properties );

	/// @name Types deserialization
    /// Functions get previous property value in parameter and generate new value or return the same object.
    /// Since previous value can be nullptr it is required to provide expected type, that
    /// can be got from property or array element. Note that result object can 
	///@{

    static Nullable< VariantWrapper >       DeserializeBasicType	    ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );
    static Nullable< VariantWrapper >       DeserializeString	        ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );
    static Nullable< VariantWrapper >       DeserializeEnum    	        ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );
    static Nullable< VariantWrapper >       DeserializeArray  	        ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );
    static Nullable< VariantWrapper >       DeserializeObject        	( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );
    static Nullable< VariantWrapper >       DeserializeObjectInArray  	( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );
    static Nullable< VariantWrapper >       DeserializeArrayInArray     ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );

    static Nullable< VariantWrapper >       DeserializePolymorphic		( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );
    static Nullable< VariantWrapper >       DeserializeNotPolymorphic	( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );

    /**@brief Selects deserialization implementation for polymorphic or not polymorphic types.*/
    static Nullable< VariantWrapper >       DeserializeObjectSelector   ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );
    static Nullable< VariantWrapper >       DeserializeDispatcher       ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );
    static ReturnResult                     DeserializePropertiesVec    ( const IDeserializer& deser, const rttr::instance& object, const std::vector< rttr::property >& properties );
    static ReturnResult                     DeserializeArrayElements    ( const IDeserializer& deser, rttr::variant_sequential_view& arrayView );
    static Nullable< VariantWrapper >       DeserializeArrayDispatcher  ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );
    
    static Nullable< VariantWrapper >       RunDeserializeOverride                  ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );    
    static Nullable< VariantWrapper >       RunDeserializeOverridePolymorphic       ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType );
    
    static Nullable< VariantWrapper >       DefaultDeserializePolymorphicImpl       ( const IDeserializer& deser, rttr::string_view typeName, rttr::variant& prevValue, DeserialTypeDesc& desc );
    static Nullable< VariantWrapper >       DefaultDeserializeNotPolymorphicImpl    ( const IDeserializer& deser, TypeID expectedType, rttr::variant& prevValue, DeserialTypeDesc& desc );
    ///@}
	
    static ReturnResult                     SetObjectProperty           ( const IDeserializer& deser, const rttr::instance& parent, rttr::property prop, VariantWrapper& newObject );
    static ReturnResult                     SetArrayElement             ( const IDeserializer& deser, rttr::variant_sequential_view& arrayView, Size index, VariantWrapper& newObject );
    static ReturnResult                     ResizeArray                 ( const IDeserializer& deser, rttr::variant_sequential_view& arrayView, Size newSize );

    ///@name Objects creation and destruction
    ///@{
    static Nullable< rttr::variant >        CreateInstance				( TypeID type );
    static Nullable< rttr::variant >        CreateInstance				( rttr::string_view typeName );

    /**@brief Destroy object in variant.*/
    static void							    DestroyObject			    ( rttr::variant& object );

    /**@brief Destroys object in variant if it is new value not reference to previosu.*/
    static void							    DestroyObjectIfNew          ( VariantWrapper& object );

    ///@}

	template< typename PropertyType >
	static void				            SerializeProperty	                        ( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue );

	template<>	static void				SerializeProperty< char >					( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue );
    template<>	static void				SerializeProperty< std::wstring >			( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue );


	template< typename PropertyType >
	static void				            SetPropertyValue	                        ( rttr::property prop, const rttr::instance& object, PropertyType value );

	template< typename PropertyType >
	static void				            DeserializeProperty	                        ( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );

    template< typename PropertyType >
    static PropertyType                 DeserializeProperty	                        ( const IDeserializer& deser, rttr::string_view name );

    template< typename PropertyType >
    static PropertyType	                GetPropertyValue			                ( rttr::property prop, const rttr::instance& object );

    template< typename PropertyType >
    static VariantWrapper               DeserializePropertyToVariant                ( const IDeserializer& deser, rttr::string_view name );

    template<> static std::wstring      DeserializeProperty< std::wstring >			( const IDeserializer& deser, rttr::string_view name );
    template<> static char				DeserializeProperty< char >					( const IDeserializer& deser, rttr::string_view name );


	/**@brief Gets real type of the object that means most derived and wrapped type.*/
	static TypeID						GetRealType			    ( const rttr::instance& object );

	/**@brief Gets wrapped type. If type isn't wrapper it returns it unmodified.*/
	static TypeID						GetWrappedType			( TypeID type );

	/**@brief First extracts wrapped type and then returns raw type.*/
	static TypeID						GetRawWrappedType		( TypeID type );

    /**@brief Converts variant in place to other type.
    Returns false on conversion fail.*/
    static bool 						ConvertVariant          ( rttr::variant& value, TypeID type );

	/**@brief Returns SerialziationContext from deserializer.*/
	static SerializationContext*		Context					( const IDeserializer& deser );

    static bool                         IsStringType            ( TypeID type );

    static std::string		            WstringToUTF	    	( const std::wstring& str );
    static std::wstring		            UTFToWstring		    ( const std::string& str );
};


}	// sw


#include "SerializationCore.inl"
