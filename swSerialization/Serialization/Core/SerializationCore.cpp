/**
@file SerialziationCore.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Serialization/stdafx.h"
#include "SerializationCore.h"


#include "swCommonLib/Common/Converters/Convert.h"
#include "swCommonLib/Common/fmt.h"

#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"



namespace sw
{


// ================================ //
/// We support only polymorphic types derived from Object.
auto SerializationCore::IsPolymorphicType		( TypeID type ) -> bool
{
	return GetRawWrappedType( type ).is_derived_from< Object >();
}

//====================================================================================//
//			Serialization	
//====================================================================================//


// ================================ //
//
void SerializationCore::DefaultSerialize
( 
    ISerializer& ser,
    const rttr::variant& object
)
{
    auto dynamicType = SerializationCore::GetRealType( object );
    SerializeObject( ser, dynamicType.get_name(), object );
}

// ================================ //
//
void SerializationCore::SerializeObject
(
    ISerializer& ser,
    rttr::string_view name,
    const rttr::instance& value
)
{
    ser.EnterObject( name.to_string() );

    auto dynamicType = SerializationCore::GetRealType( value );

    auto& overrides = ser.GetContext< SerializationContext >()->SerialOverrides;
    auto& typeDesc = overrides.GetTypeDescriptor( dynamicType );

    // If user specified override function for this type - use it.
    // Otherwise default serialization.
    if( typeDesc.CustomFunction )
        typeDesc.CustomFunction( ser, value, typeDesc );
    else
        SerializePropertiesVec( ser, value, typeDesc.Properties );

    ser.Exit();	//	prop.get_name()
}

// ================================ //
//
void SerializationCore::SerializePolymorphic
(
    ISerializer& ser,
    rttr::string_view name,
    const rttr::variant& value
)
{
    ser.EnterObject( name.to_string() );

    if( IsNullptr( value ) )
    {
        // Create empty entry with named combined from dynamic type name and nullptr.
        ser.EnterObject( GenNullptrName().to_string() );
        ser.Exit();
    }
    else
    {
        auto instance = rttr::instance( value );
        auto dynamicType = SerializationCore::GetRealType( instance );
        assert( IsPolymorphicType( dynamicType ) );

        SerializeObject( ser, dynamicType.get_name(), instance );
    }

    ser.Exit();	//	prop.get_name()
}

// ================================ //
//
void SerializationCore::SerializeNotPolymorphic
( 
    ISerializer& ser,
    rttr::string_view name,
    const rttr::variant& value
)
{
    assert( !IsPolymorphicType( value.get_type() ) );
    SerializeObject( ser, name, value );
}

// ================================ //
//
void SerializationCore::SerializePolymorphic
(
    ISerializer& ser,
    const rttr::instance& parent,
    rttr::property prop
)
{
    SerializePolymorphic( ser, prop.get_name(), prop.get_value( parent ) );
}

// ================================ //
//
void SerializationCore::SerializeNotPolymorphic
(
    ISerializer& ser,
    const rttr::instance& parent,
    rttr::property prop
)
{
    assert( !IsPolymorphicType( prop.get_type() ) );
    SerializeNotPolymorphic( ser, prop.get_name(), prop.get_value( parent ) );
}

// ================================ //
//
void SerializationCore::SerializePropertiesVec
(
    ISerializer& ser,
    const rttr::instance& parent,
    const std::vector< rttr::property >& properties
)
{
	for( auto& property : properties )
	{
		bool serialized = false;
		serialized = serialized || SerializeBasicTypes( ser, parent, property );
		serialized = serialized || SerializeStringTypes( ser, parent, property );
		serialized = serialized || SerializeEnumTypes( ser, parent, property );
		serialized = serialized || SerializeArrayTypes( ser, parent, property );
		serialized = serialized || SerializeObjectTypes( ser, parent, property );
	}
}


// ================================ //
//
auto SerializationCore::SerializeBasicTypes
(
    ISerializer& ser,
    const rttr::instance& object,
    rttr::property prop
) -> bool
{
	return SerializeBasicTypes( ser, prop.get_name(), prop.get_value( object ) );
}

// ================================ //
//
auto SerializationCore::SerializeBasicTypes
(
    ISerializer& ser,
    rttr::string_view name,
    const rttr::variant& propertyValue
) -> bool
{
	auto propertyType = propertyValue.get_type();

	if( !propertyType.is_arithmetic() )
		return false;

	if( propertyType == rttr::type::get< float >() )
		SerializeProperty< float >( ser, name, propertyValue );
	else if( propertyType == rttr::type::get< bool >() )
		SerializeProperty< bool >( ser, name, propertyValue );
	else if( propertyType == rttr::type::get< int32 >() )
		SerializeProperty< int32 >( ser, name, propertyValue );
	else if( propertyType == rttr::type::get< uint32 >() )
		SerializeProperty< uint32 >( ser, name, propertyValue );
	else if( propertyType == rttr::type::get< int16 >() )
		SerializeProperty< int16 >( ser, name, propertyValue );
	else if( propertyType == rttr::type::get< uint16 >() )
		SerializeProperty< uint16 >( ser, name, propertyValue );
	else if( propertyType == rttr::type::get< int8 >() )
		SerializeProperty< int8 >( ser, name, propertyValue );
	else if( propertyType == rttr::type::get< uint8 >() )
		SerializeProperty< uint8 >( ser, name, propertyValue );
	else if( propertyType == rttr::type::get< int64 >() )
		SerializeProperty< int64 >( ser, name, propertyValue );
	else if( propertyType == rttr::type::get< uint64 >() )
		SerializeProperty< uint64 >( ser, name, propertyValue );
	else if( propertyType == rttr::type::get< double >() )
		SerializeProperty< double >( ser, name, propertyValue );
	else if( propertyType == rttr::type::get< char >() )
		SerializeProperty< char >( ser, name, propertyValue );
	else
		return false;

	return true;
}

// ================================ //
//
auto SerializationCore::SerializeStringTypes
(
    ISerializer& ser,
    rttr::string_view name,
    const rttr::variant& value
) -> bool
{
    auto propertyType = value.get_type();

    if( propertyType == rttr::type::get< std::string >() )
        SerializeProperty< std::string >( ser, name, value );
    else if( propertyType == rttr::type::get< std::wstring >() )
        SerializeProperty< std::wstring >( ser, name, value );
    else
        return false;

    return true;
}

// ================================ //
//
auto SerializationCore::SerializeEnumTypes
(
    ISerializer& ser,
    rttr::string_view name,
    const rttr::variant& value
) -> bool
{
    auto propertyType = value.get_type();

    if( !propertyType.is_enumeration() )
        return false;

    assert( propertyType.is_valid() );		/// Type haven't been registered.
    assert( propertyType.is_enumeration() );

    rttr::enumeration enumVal = propertyType.get_enumeration();

    ser.SetAttribute( name.to_string(), enumVal.value_to_name( value ).to_string() );

    return true;
}

// ================================ //
//
auto SerializationCore::SerializeStringTypes
(
    ISerializer& ser,
    const rttr::instance& object,
    rttr::property prop
) -> bool
{
    return SerializeStringTypes( ser, prop.get_name(), prop.get_value( object ) );
}

// ================================ //
//
auto SerializationCore::SerializeEnumTypes
(
    ISerializer& ser,
    const rttr::instance& object,
    rttr::property prop
) -> bool
{
	return SerializeEnumTypes( ser, prop.get_name(), prop.get_value( object ) );
}

// ================================ //
//
auto SerializationCore::SerializeArrayTypes
(
    ISerializer& ser,
    rttr::string_view name,
    const rttr::variant& value
) -> bool
{
    TypeID propertyType = SerializationCore::GetWrappedType( value.get_type() );
    if( !propertyType.is_sequential_container() )
        return false;

    auto arrayView = value.create_sequential_view();

    assert( arrayView.is_valid() );
    assert( arrayView.get_rank() == 1 );
    if( arrayView.get_rank() != 1 )
        return true;

    TypeID arrayElementType = arrayView.get_rank_type( 1 );
    assert( arrayElementType.is_class() || arrayElementType.get_raw_type().is_class() );
    if( !arrayElementType.is_class() && !arrayElementType.get_raw_type().is_class() )
        return true;

    ser.EnterArray( name.to_string() );

    /// @todo No all serializers support array attributes (for example json doesn't).
    if( arrayView.is_dynamic() )
        ser.SetAttribute( "ArraySize", arrayView.get_size() );

    if( IsPolymorphicType( arrayElementType ) )
    {
        // Process generic objects. Default serialization writes object type.
        for( auto& element : arrayView )
        {
            auto value = element.extract_wrapped_value();

            // We serialize "Element" because some serializers like json don't
            // have named elements in arrays and we would lose type information.
            // This is not the case in not polymorphic serialization where type 
            // information from property is enough to deserialize array.
            SerializePolymorphic( ser, "Element", value );
        }
    }
    else
    {
        for( auto& element : arrayView )
        {
            // Non generic objects use default serialization.
            auto elementType = SerializationCore::GetRealType( element );
            SerializeNotPolymorphic( ser, elementType.get_name(), element );
        }
    }

    ser.Exit();

    return true;
}

auto SerializationCore::SerializeObjectTypes
( 
    ISerializer& ser, 
    rttr::string_view name, 
    const rttr::variant& value
) -> bool
{
    auto propertyType = value.get_type();
    if( propertyType.is_wrapper() )
        propertyType = propertyType.get_wrapped_type();

    if( !propertyType.get_raw_type().is_class() )
        return false;

    bool serialized = true;

    if( IsPolymorphicType( propertyType ) )
        SerializePolymorphic( ser, name, value );
    else
        SerializeNotPolymorphic( ser, name, value );

    return serialized;
}

// ================================ //
//
auto SerializationCore::SerializeArrayTypes
(
    ISerializer& ser,
    const rttr::instance& object,
    rttr::property prop
) -> bool
{
    return SerializeArrayTypes( ser, prop.get_name(), prop.get_value( object ) );
}

// ================================ //
//
auto SerializationCore::SerializeObjectTypes
(
    ISerializer& ser,
    const rttr::instance& object,
    rttr::property prop
) -> bool
{
    return SerializeObjectTypes( ser, prop.get_name(), prop.get_value( object ) );
}


//====================================================================================//
//				SerializeProperty template specialization
//====================================================================================//

// ================================ //
//
template<>
void SerializationCore::SerializeProperty< char >
(
    ISerializer& ser,
    rttr::string_view name,
    const rttr::variant& propertyValue
)
{
    char character = propertyValue.get_value< char >();
    ser.SetAttribute(name.to_string(), std::string(1, character));
}

// ================================ //
//
template<>
void SerializationCore::SerializeProperty< std::wstring >
(
    ISerializer& ser,
    rttr::string_view name,
    const rttr::variant& propertyValue
)
{
    std::wstring str = propertyValue.get_value< std::wstring >();
    ser.SetAttribute(name.to_string(), WstringToUTF(str));
}


}	// sw
