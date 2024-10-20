#pragma once
/**
@file SerializationCore.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "SerializationCore.h"

#include "swCommonLib/Common/fmt.h"


namespace sw
{


//====================================================================================//
//			Default value traits	
//====================================================================================//

template< typename Type >
inline Type					TypeDefaultValue()
{
	return Type();
}

template<>	inline uint16			TypeDefaultValue() { return 0; }
template<>	inline int16			TypeDefaultValue() { return 0; }
template<>	inline uint32			TypeDefaultValue() { return 0; }
template<>	inline int32			TypeDefaultValue() { return 0; }
template<>	inline int64			TypeDefaultValue() { return 0; }

template<>	inline float			TypeDefaultValue() { return 0.0f; }
template<>	inline double			TypeDefaultValue() { return 0.0; }

template<>	inline std::wstring		TypeDefaultValue() { return std::wstring( L"" ); }
template<>	inline std::string		TypeDefaultValue() { return std::string( "" ); }

template<>	inline Object*          TypeDefaultValue() { return nullptr; }


//====================================================================================//
//			Property templated getters/setters	
//====================================================================================//


/**@brief Returns typed property value.*/
template< typename PropertyType >
auto SerializationCore::GetPropertyValue
(
    rttr::property prop,
    const rttr::instance& object
) -> PropertyType
{
	auto value = prop.get_value( object );
	assert( value.is_valid() );
	return value.get_value< PropertyType >();
}

// ================================ //
//
template< typename PropertyType >
inline void SerializationCore::SerializeProperty
(
    ISerializer& ser,
    rttr::string_view name,
    const rttr::variant& propertyValue
)
{
	ser.SetAttribute( name.to_string(), propertyValue.get_value< PropertyType >() );
}


/**@brief Ustawia wartoœæ podanej w³aœciwoœci.*/
template< typename PropertyType >
void SerializationCore::SetPropertyValue
(
    rttr::property prop,
    const rttr::instance& object,
    PropertyType value
)
{
	prop.set_value( object, value );
}

/**@brief Deserializuje w³aœciwoœæ podanego typu.

@todo Mo¿na zoptymalizowaæ pobieranie nazwy z w³aœciwoœci i ograniczyæ alokacjê stringów.*/
template< typename PropertyType >
void SerializationCore::DeserializeProperty
(
    const IDeserializer& deser,
    rttr::property prop,
    const rttr::instance& object
)
{
	PropertyType value = static_cast< PropertyType >( deser.GetAttribute( prop.get_name().to_string(), TypeDefaultValue< PropertyType >() ) );
	SetPropertyValue< PropertyType >( prop, object, value );
}

// ================================ //
//
template< typename PropertyType >
inline auto SerializationCore::DeserializeProperty
(
    const IDeserializer& deser,
    rttr::string_view name
) -> PropertyType
{
    return static_cast< PropertyType >( deser.GetAttribute( name.to_string(), TypeDefaultValue< PropertyType >() ) );
}

// ================================ //
//
template< typename PropertyType >
inline auto SerializationCore::DeserializePropertyToVariant
(
    const IDeserializer& deser,
    rttr::string_view name
) -> VariantWrapper
{
    return VariantWrapper::FromNew( rttr::variant( SerializationCore::DeserializeProperty< PropertyType >( deser, name ) ) );
}

// ================================ //
//
inline auto SerializationCore::GetRealType
(
    const rttr::instance& object
) -> TypeID
{
	auto objectType = object.get_derived_type();
	return objectType.is_wrapper() ? objectType.get_wrapped_type() : objectType;
}

// ================================ //
//
inline auto SerializationCore::GetWrappedType
(
    TypeID type
) -> TypeID
{
	return type.is_wrapper() ? type.get_wrapped_type() : type;
}

// ================================ //
//
inline auto SerializationCore::GetRawWrappedType
(
    TypeID type
) -> TypeID
{
	return GetWrappedType( type ).get_raw_type();
}

// ================================ //
//
inline auto SerializationCore::ConvertVariant
(
    rttr::variant& value,
    TypeID targetType
) -> bool
{
    // Don't convert, if type is the same. This can cause problems when we try to convert
    // types that are bound by value. Conversion creates new temporary object and then
    // it is destroyed. If we allocate pointers, they are deallocated.
    auto srcType = value.get_type();
    if( srcType != targetType )
    {
        return value.convert( TypeID( targetType ) );
    }

    return true;
}

// ================================ //
//
inline auto SerializationCore::Context
(
    const IDeserializer& deser
) -> SerializationContext*
{
	return deser.GetContext< SerializationContext >();
}

// ================================ //
//
inline void SerializationCore::DestroyObject
(
    rttr::variant& object
)
{
	if( object.is_valid() )
	{
		TypeID typeToDestroy = object.get_type();

		// What if wrappers don't own objects ?
		if( !typeToDestroy.is_wrapper() )
		{
            // Destroying will fail if we pass not allocated object.
			typeToDestroy.destroy( object );
		}
	}
}

// ================================ //
//
inline void SerializationCore::DestroyObjectIfNew
(
    VariantWrapper& object
)
{
    if( object.IsNew() )
        DestroyObject( object.GetNew() );
}

// ================================ //
//
inline auto SerializationCore::IsStringType
(
    TypeID type
) -> bool
{
    if( type == TypeID::get< std::string >() )
        return true;

    if( type == TypeID::get< std::wstring >() )
        return true;

    return false;
}

// ================================ //
//
inline auto SerializationCore::IsBoundByValue
(
    TypeID elementType
) -> bool
{
    return !elementType.is_wrapper() && !elementType.is_pointer();
}

// ================================ //
//
inline auto SerializationCore::IsNullptr
( 
    const rttr::variant& value
) -> bool
{
    return value == nullptr;
}

// ================================ //
//
inline auto SerializationCore::GenNullptrName() -> rttr::string_view
{
    using namespace std::literals;

    static std::string_view nullptrString = "nullptr"sv;
    return rttr::string_view( nullptrString.data(), nullptrString.length() );
}


}	// sw