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
bool					SerializationCore::IsPolymorphicType		( TypeID type )
{
	return GetRawWrappedType( type ).is_derived_from< Object >();
}

//====================================================================================//
//			Serialization	
//====================================================================================//


// ================================ //
//
void					SerializationCore::DefaultSerialize			( ISerializer& ser, const Object* object )
{
	DefaultSerializeImpl( ser, object );
}


// ================================ //
//
void					SerializationCore::DefaultSerializeImpl		( ISerializer& ser, const rttr::instance& object )
{
	auto dynamicType = SerializationCore::GetRealType( object );
    SerializeObject( ser, dynamicType.get_name(), object );
}

// ================================ //
//
void                    SerializationCore::SerializeObject          ( ISerializer& ser, rttr::string_view name, const rttr::instance& value )
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
void                    SerializationCore::SerializePolymorphic     ( ISerializer& ser, rttr::string_view name, const rttr::variant& value )
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
void					SerializationCore::SerializePolymorphic		( ISerializer& ser, const rttr::instance& parent, rttr::property prop )
{
    SerializePolymorphic( ser, prop.get_name(), prop.get_value( parent ) );
}

// ================================ //
//
void					SerializationCore::SerializeNotPolymorphic	( ISerializer& ser, const rttr::instance& parent, rttr::property prop )
{
    assert( !IsPolymorphicType( prop.get_type() ) );
    SerializeObject( ser, prop.get_name(), prop.get_value( parent ) );
}

// ================================ //
//
void					SerializationCore::SerializePropertiesVec	( ISerializer& ser, const rttr::instance& parent, const std::vector< rttr::property >& properties )
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
bool				SerializationCore::SerializeBasicTypes			( ISerializer& ser, const rttr::instance& object, rttr::property prop )
{
	return SerializeBasicTypes( ser, prop.get_name(), prop.get_value( object ) );
}

// ================================ //
//
bool				SerializationCore::SerializeBasicTypes			( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue )
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
bool            SerializationCore::SerializeStringTypes             ( ISerializer& ser, rttr::string_view name, const rttr::variant& value )
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
bool            SerializationCore::SerializeEnumTypes               ( ISerializer& ser, rttr::string_view name, const rttr::variant& value )
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
bool			SerializationCore::SerializeStringTypes				( ISerializer& ser, const rttr::instance& object, rttr::property prop )
{
    return SerializeStringTypes( ser, prop.get_name(), prop.get_value( object ) );
}

// ================================ //
//
bool			SerializationCore::SerializeEnumTypes				( ISerializer& ser, const rttr::instance& object, rttr::property prop )
{
	return SerializeEnumTypes( ser, prop.get_name(), prop.get_value( object ) );
}

// ================================ //
//
bool            SerializationCore::SerializeArrayTypes              ( ISerializer& ser, rttr::string_view name, const rttr::variant& value )
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
            DefaultSerializeImpl( ser, element );
        }
    }

    ser.Exit();

    return true;
}

// ================================ //
//
bool			SerializationCore::SerializeArrayTypes				( ISerializer& ser, const rttr::instance& object, rttr::property prop )
{
    return SerializeArrayTypes( ser, prop.get_name(), prop.get_value( object ) );
}

// ================================ //
//
bool			SerializationCore::SerializeObjectTypes				( ISerializer& ser, const rttr::instance& object, rttr::property prop )
{
	auto propertyType = prop.get_type();
	if( propertyType.is_wrapper() )
		propertyType = propertyType.get_wrapped_type();

	if( !propertyType.get_raw_type().is_class() )
		return false;

	bool serialized = true;

	if( IsPolymorphicType( propertyType ) )
		SerializePolymorphic( ser, object, prop );
	else
		SerializeNotPolymorphic( ser, object, prop );

	return serialized;
}

//====================================================================================//
//			Deserialization	
//====================================================================================//

// ================================ //
//
ReturnResult					    SerializationCore::DefaultDeserialize		( const IDeserializer& deser, Object* object )
{
	return DefaultDeserializeImpl( deser, object, object->GetType() );
}

// ================================ //
/// TODO: Replace with new functions.
ReturnResult					    SerializationCore::DefaultDeserializeImpl	    ( const IDeserializer& deser, const rttr::instance& object, rttr::type dynamicType )
{
	auto objectType = dynamicType;

    auto& overrides = deser.GetContext< SerializationContext >()->DeserialOverrides;
    auto& typeDesc = overrides.GetTypeDescriptor( objectType );

    return DeserializePropertiesVec( deser, object, typeDesc.Properties );
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializeBasicType         ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    /// @todo Consider checking these conditions and returning exception on fail.
    assert( expectedType.is_arithmetic() );

    if( expectedType == rttr::type::get< float >() )
        return SerializationCore::DeserializePropertyToVariant< float >( deser, name );
    else if( expectedType == rttr::type::get< bool >() )
        return SerializationCore::DeserializePropertyToVariant< bool >( deser, name );
    else if( expectedType == rttr::type::get< int32 >() )
        return SerializationCore::DeserializePropertyToVariant< int32 >( deser, name );
    else if( expectedType == rttr::type::get< uint32 >() )
        return SerializationCore::DeserializePropertyToVariant< uint32 >( deser, name );
    else if( expectedType == rttr::type::get< int16 >() )
        return SerializationCore::DeserializePropertyToVariant< int16 >( deser, name );
    else if( expectedType == rttr::type::get< uint16 >() )
        return SerializationCore::DeserializePropertyToVariant< uint16 >( deser, name );
    else if( expectedType == rttr::type::get< int8 >() )
        return SerializationCore::DeserializePropertyToVariant< int8 >( deser, name );
    else if( expectedType == rttr::type::get< uint8 >() )
        return SerializationCore::DeserializePropertyToVariant< uint8 >( deser, name );
    else if( expectedType == rttr::type::get< int64 >() )
        return SerializationCore::DeserializePropertyToVariant< int64 >( deser, name );
    else if( expectedType == rttr::type::get< uint64 >() )
        return SerializationCore::DeserializePropertyToVariant< uint64 >( deser, name );
    else if( expectedType == rttr::type::get< double >() )
        return SerializationCore::DeserializePropertyToVariant< double >( deser, name );
    else if( expectedType == rttr::type::get< char >() )
        return SerializationCore::DeserializePropertyToVariant< char >( deser, name );
    else
        return SerializationException::Create( deser, fmt::format( "Type [{}] was none of arithmetic types.", expectedType ) );
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializeString            ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    if( expectedType == rttr::type::get< std::string >() )
        return SerializationCore::DeserializePropertyToVariant< std::string >( deser, name );
    else if( expectedType == rttr::type::get< std::wstring >() )
        return SerializationCore::DeserializePropertyToVariant< std::wstring >( deser, name );
    else
        return SerializationException::Create( deser, fmt::format( "Type [{}] was none of string types.", expectedType ) );
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializeEnum              ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    /// @todo Consider checking these conditions and returning exception on fail.
    assert( expectedType.is_enumeration() );    /// Should be checked by caller.
    assert( expectedType.is_valid() );		    /// Type haven't been registered.

    rttr::enumeration enumVal = expectedType.get_enumeration();

    auto enumFieldString = deser.GetAttribute( name.to_string(), "" );
    rttr::variant value = enumVal.name_to_value( enumFieldString );

    if( value.is_valid() )
        return VariantWrapper::FromNew( std::move( value ) );
    
    return SerializationException::Create( deser, fmt::format( "Enum of type [{}] has no field [{}], while deserializing [{}].",
                                                                expectedType,
                                                                enumFieldString,
                                                                name.to_string() ) );
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializeArray             ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    TypeID propertyType = SerializationCore::GetWrappedType( expectedType );
    if( !propertyType.is_sequential_container() )
        return SerializationException::Create( deser, fmt::format( "Type [{}] is not sequential container.", expectedType ) );

    auto arrayView = prevValue.create_sequential_view();

    assert( arrayView.is_valid() );
    assert( arrayView.get_rank() == 1 );

    if( arrayView.get_rank() != 1 )
        return SerializationException::Create( deser, fmt::format( "Not supported. Array [{}] of type [{}] has nested arrays.", name.to_string(), expectedType ) );

    TypeID arrayElementType = arrayView.get_rank_type( 1 );
    assert( arrayElementType.is_class() || arrayElementType.get_raw_type().is_class() );
    if( !arrayElementType.is_class() && !arrayElementType.get_raw_type().is_class() )
        return SerializationException::Create( deser, fmt::format( "Array [{}] with elements of type [{}] can't be deserialized. Only classes and structures supported.",
                                                                    name.to_string(), arrayElementType ) );

    if( deser.EnterArray( name.to_string() ) )
    {
        auto result = DeserializeArrayElements( deser, arrayView );

        deser.Exit();

        if( !result.IsValid() )
            return result.GetError();
    }
    else
    {
        ///@todo This warning should be conditional depending on flag in SerializationContext.
        Warn< SerializationException >( deser, fmt::format( "Property [{}] not found in file. Value remained unchanged.", name.to_string() ) );
    }

    return RemapBoundByValue( deser, VariantWrapper::FromPrevious( prevValue ), name, expectedType );
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializeObject            ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    if( deser.EnterObject( name.to_string() ) )
    {
        auto result = DeserializeObjectSelector( deser, name, prevValue, expectedType );
        deser.Exit();	// EnterObject( name )

        return result;
    }
    else
    {
        ///@todo This warning should be conditional depending on flag in SerializationContext.
        Warn< SerializationException >( deser, fmt::format( "Property [{}] not found in file. Value remained unchanged.", name.to_string() ) );
        return VariantWrapper::FromPrevious( prevValue );
    }
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializeObjectInArray     ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    return DeserializeObjectSelector( deser, name, prevValue, expectedType );
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializeArrayInArray      ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    return SerializationException::Create( deser, fmt::format( "Not implemented" ) );
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializeObjectSelector    ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    TypeID expectedTypeUnwrapped = SerializationCore::GetRawWrappedType( expectedType );
    
    // Consider returning exception on false.
    assert( expectedTypeUnwrapped.is_class() );

    if( IsPolymorphicType( expectedTypeUnwrapped ) )
    {
        // Retrieve dynamic type of object from deserializer and create new object.
        return DeserializePolymorphic( deser, name, prevValue, expectedType );
    }
    else
    {
        return DeserializeNotPolymorphic( deser, name, prevValue, expectedType );
    }
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializePolymorphic       ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    if( deser.FirstElement() )
    {
        // Handle nullptr cases.
        rttr::string_view dynamicTypeName = deser.GetName();
        if( dynamicTypeName == GenNullptrName() )
            return VariantWrapper::Nullptr();

        auto objectResult = RunDeserializeOverridePolymorphic( deser, dynamicTypeName, prevValue, expectedType );

        if( deser.NextElement() )
        {
            // Warning: Property shouldn't have multiple objects.
            Warn< SerializationException >( deser, fmt::format( "Deserialization of property [{}]. Multiple polymorphic objects defined. Deserializing only first.", name.to_string() ) );
        }

        deser.Exit();	// FirstElement
        return std::move( objectResult ).Get();
    }
    else
    {
        return SerializationException::Create( deser, fmt::format( "Deserialization of property [{}]. Type of polymorphic object not specified.",
                                                                    name.to_string() ) );
    }
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializeNotPolymorphic    ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    auto result = RunDeserializeOverride( deser, name, prevValue, expectedType );
    return RemapBoundByValue( deser, std::move( result ), name, expectedType );
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializeDispatcher        ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    auto expectedTypeUnwrapped = SerializationCore::GetRawWrappedType( expectedType );

    if( expectedTypeUnwrapped.is_arithmetic() )
        return DeserializeBasicType( deser, name, prevValue, expectedType );
    if( expectedTypeUnwrapped.is_enumeration() )
        return DeserializeEnum( deser, name, prevValue, expectedType );
    if( SerializationCore::IsStringType( expectedTypeUnwrapped ) )
        return DeserializeString( deser, name, prevValue, expectedType );
    if( expectedTypeUnwrapped.is_sequential_container() )
        return DeserializeArray( deser, name, prevValue, expectedType );
    if( expectedTypeUnwrapped.is_class() )
        return DeserializeObject( deser, name, prevValue, expectedType );

    return SerializationException::Create( deser, fmt::format( "Type [{}] isn't any of class types known to serialization.", expectedType ) );
}

// ================================ //
//
ReturnResult                        SerializationCore::DeserializePropertiesVec     ( const IDeserializer& deser, const rttr::instance& parent, const std::vector< rttr::property >& properties )
{
    ErrorsCollector collector;

    for( auto& property : properties )
    {
        auto propertyType = property.get_type();
        auto prevValue = property.get_value( parent );

        auto deserResult = DeserializeDispatcher( deser, property.get_name(), prevValue, propertyType );
        auto valueToSet = collector.OnError( std::move( deserResult ), VariantWrapper::FromPrevious( prevValue ) );
        auto result = SerializationCore::SetObjectProperty( deser, parent, property, valueToSet );
        
        // Destroy new object if we failed to set property.
        if( !collector.Success( result ) )
            DestroyObjectIfNew( valueToSet );
    }

    return collector;
}

// ================================ //
//
ReturnResult                        SerializationCore::DeserializeArrayElements     ( const IDeserializer& deser, rttr::variant_sequential_view& arrayView )
{
    TypeID arrayType = arrayView.get_type();
    TypeID arrayElementType = arrayView.get_rank_type( 1 );

    Size idx = 0;

    ErrorsCollector collector;
    VariantVec elementsVec;

    // Array size should be only hint for deserialization.
    auto arraySize = deser.GetAttribute( "ArraySize", 0 );
    if( arraySize != 0 )
        ResizeArray( deser, arrayView, arraySize );

    if( deser.FirstElement() )
    {
        do
        {
            if( idx >= arrayView.get_size() )
            {
                Warn< SerializationException >( deser, fmt::format( "Performance warning: ArraySize hint didn't match real array size." ) );

                auto result = ResizeArray( deser, arrayView, idx + 1 );
                if( !result.IsValid() )
                {
                    deser.Exit();
                    return result;
                }
            }

            auto prevValue = arrayView.get_value( idx );
            auto result = DeserializeArrayDispatcher( deser, "", prevValue, arrayElementType );
            auto value = collector.OnError( std::move( result ), VariantWrapper::FromPrevious( prevValue ) );
            auto setResult = SetArrayElement( deser, arrayView, idx, value );
            
            // Destroy new object if we failed to insert it into array.
            if( !collector.Success( setResult ) )
                DestroyObjectIfNew( value );

            idx++;
        } while( deser.NextElement() );

        deser.Exit();
    }

    return collector;
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DeserializeArrayDispatcher               ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    auto expectedTypeUnwrapped = SerializationCore::GetRawWrappedType( expectedType );

    if( expectedTypeUnwrapped.is_arithmetic()
        || expectedTypeUnwrapped.is_enumeration()
        || SerializationCore::IsStringType( expectedTypeUnwrapped ) )
        return SerializationException::Create( deser, fmt::format( "Type [{}] not supported in array.", expectedType ) );

    // Why: In arrays we always get valid previous values wrapped in std::reference_wrapper.
    // But array element type isn't wrapped type, but raw type. If we pass this type to deserialization,
    // these functions will assume, that object was copied by value, what isn't true.
    // PrevValue is the only way to get real array element type.
    expectedType = prevValue.get_type();

    if( expectedTypeUnwrapped.is_sequential_container() )
        return DeserializeArrayInArray( deser, name, prevValue, expectedType );
    if( expectedTypeUnwrapped.is_class() )
        return DeserializeObjectInArray( deser, name, prevValue, expectedType );

    return SerializationException::Create( deser, fmt::format( "Type [{}] isn't any of class types known to serialization.", expectedType ) );
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::RunDeserializeOverride                   ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    TypeID wrappedType = GetWrappedType( expectedType );

    auto& overrides = deser.GetContext< SerializationContext >()->DeserialOverrides;
    auto& typeDesc = overrides.GetTypeDescriptor( wrappedType );

    if( typeDesc.CustomFunction )
        return typeDesc.CustomFunction( deser, typeDesc );
    else
        return DefaultDeserializeNotPolymorphicImpl( deser, expectedType, prevValue, typeDesc );
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::RunDeserializeOverridePolymorphic        ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    expectedType = GetWrappedType( TypeID::get_by_name( name ) );

    if( !expectedType.is_valid() )
        return SerializationException::Create( deser, fmt::format( "[{}] is not valid type.", name.to_string() ) );

    auto& overrides = deser.GetContext< SerializationContext >()->DeserialOverrides;
    auto& typeDesc = overrides.GetTypeDescriptor( expectedType );

    if( typeDesc.CustomFunction )
        return typeDesc.CustomFunction( deser, typeDesc );
    else
        return DefaultDeserializePolymorphicImpl( deser, expectedType, prevValue, typeDesc );
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::DefaultDeserializePolymorphicImpl        ( const IDeserializer& deser, TypeID expectedType, rttr::variant& prevValue, DeserialTypeDesc& desc )
{
    // Check what type of object we should create.
    auto newClassResult = CreateInstance( expectedType );

    if( !newClassResult.IsValid() )
    {
        deser.Exit();	// FirstElement
        return SerializationException::Create( deser, fmt::format( "Failed to create object. {}",
                                                                    newClassResult.GetErrorReason() ) );
    }

    rttr::variant newClass = std::move( newClassResult ).Get();

    return DeserializePropertiesVec( deser, newClass, desc.Properties ).Ok( VariantWrapper::FromNew( std::move( newClass ) ) );
}

// ================================ //
//
Nullable< VariantWrapper >           SerializationCore::DefaultDeserializeNotPolymorphicImpl     ( const IDeserializer& deser, TypeID expectedType, rttr::variant& prevValue, DeserialTypeDesc& desc )
{
    // We must handle cases, when structure is nullptr or invalid. First can happen for heap allocated
    // structure, second for elements of array while resizing.
    // First we must create new object and then deserialize it.
    if( !prevValue.is_valid() || prevValue == nullptr )
    {
        auto creationResult = CreateInstance( expectedType );

        if( !creationResult.IsValid() )
            return creationResult.GetError();

        rttr::variant newInstance = std::move( creationResult ).Get();
        return DeserializePropertiesVec( deser, newInstance, desc.Properties ).Ok( VariantWrapper::FromNew( std::move( newInstance ) ) );
    }
    else
    {
        // In normal cases we deserialize structure in place and return previous value.
        return DeserializePropertiesVec( deser, prevValue, desc.Properties ).Ok( VariantWrapper::FromPrevious( prevValue ) );
    }
}

// ================================ //
//
ReturnResult                        SerializationCore::SetObjectProperty    ( const IDeserializer& deser, const rttr::instance& parent, rttr::property prop, VariantWrapper& objectToSet )
{
    // Object didn't change, we don't have to set property.
    // Note: This can happen when we deserialize not-polymorphic structure,
    // that doesn't require allocation.
    if( objectToSet.IsPrevious() )
        return Success::True;

    if( objectToSet.IsNullptr() )
        return SetNullptrProperty( deser, parent, prop );

    rttr::variant& newObject = objectToSet.GetNew();

    TypeID propertyType = prop.get_type();
    TypeID createdType = newObject.get_type();

    if( !( propertyType.is_wrapper() && !createdType.is_wrapper() ) &&
        !( !propertyType.is_wrapper() && createdType.is_wrapper() ) )
    {
        if( ConvertVariant( newObject, propertyType ) )
        {
            auto prevValue = prop.get_value( parent );
            if( prop.set_value( parent, newObject ) )
            {
                DestroyObject( prevValue );
                return Success::True;
            }

            // Don't return. Further diagnostic below.
        }
        else
        {
		    std::string errorMessage = fmt::format( "Error setting property [{}]. Can't convert object of type [{}] to [{}].",
                                                    prop.get_name().to_string(),
                                                    createdType,
                                                    propertyType );

            return SerializationException::Create( deser, std::move( errorMessage ) );
        }
    }

	// Error diagnostic. Determine why setting object failed and return error.
	// RTTR should do this internally in convert and set_property functions, so we can delay
	// some checks to handle error cases.

	TypeID wrappedPropType = GetRawWrappedType( propertyType );
	TypeID wrappedClassType = GetRawWrappedType( createdType );

	if( !wrappedClassType.is_derived_from( wrappedPropType ) )
	{
        std::string errorMessage = fmt::format( "Property type [{}] is not base class of created object type [{}].", wrappedClassType );

        return SerializationException::Create( deser, std::move( errorMessage ) );
	}

	// Wrapped and raw pointer mismatch.

	if( propertyType.is_wrapper() && !createdType.is_wrapper() )
	{
		/// @todo When created type is raw pointer and property is wrapped type, we could handle this case
		/// by creating wrapper from pointer. Consider this in future. Many problems could apear, when it comes to
		/// ownership of memory and so on.
        std::string errorMessage = fmt::format( "Error setting property [{}]. Wrapper and raw pointer mismatch between"
                                                " property of type [{}] and created class of type [{}].",
                                                prop.get_name().to_string(),
                                                propertyType,
                                                createdType );

        return SerializationException::Create( deser, std::move( errorMessage ) );
	}
	else if( !propertyType.is_wrapper() && createdType.is_wrapper() )
	{
		// If propertyType is raw pointer and createdType is wrapper we can't do anything with this.
		// There's no way in rttr to steal wrapped value from shared_ptr.
		/// @todo We must take into considerations other wrapper types which not necessary take ownership of
		/// object. To do this we must be able to determine wrapper template type and have some traits connected
		/// to ownership. Think about it in future.
        std::string errorMessage = fmt::format( "Error setting property [{}]. Wrapper and raw pointer mismatch between property"
                                                " of type [{}] and created class of type [{}].",
                                                prop.get_name().to_string(),
                                                propertyType,
                                                createdType );

        return SerializationException::Create( deser, std::move( errorMessage ) );
	}
	else if( propertyType.is_wrapper() && createdType.is_wrapper() && propertyType != createdType )
	{
		// Classes types are the same, but wrappers are different.

		std::string errorMessage = fmt::format( "Error setting property [{}]. Wrappers mismatch between property"
                                                " of type [{}] and created class of type [{}].",
                                                prop.get_name().to_string(),
                                                propertyType,
                                                createdType );

        return SerializationException::Create( deser, std::move( errorMessage ) );
	}

	if( !GetRawWrappedType( createdType ).get_constructor().is_valid() )
	{
		std::string errorMessage = fmt::format( "Can't construct object of type [{}]. Zero arguments constructor"
                                                " wasn't declared in rttr for this class.",
                                                createdType );

        return SerializationException::Create( deser, std::move( errorMessage ) );
	}

    return SerializationException::Create( deser, fmt::format( "Unknown error while setting object of type [{}] for property [{}].",
                                                                createdType,
                                                                propertyType.get_name().to_string() ) );
}

// ================================ //
//
ReturnResult                        SerializationCore::SetArrayElement      ( const IDeserializer& deser, rttr::variant_sequential_view& arrayView, Size index, VariantWrapper& objectToSet )
{
    // Object didn't change, we don't have to set property.
    // Note: This can happen when we deserialize arrays with structures
    // of constant size.
    if( objectToSet.IsPrevious() )
        return Success::True;

    rttr::variant nullptrVariant = nullptr;
    rttr::variant& newObject = objectToSet.IsNullptr() ? nullptrVariant : objectToSet.GetNew();

    TypeID elementType = arrayView.get_value_type();
    if( ConvertVariant( newObject, elementType ) )
    {
        auto prevValue = arrayView.get_value( index );
        if( arrayView.set_value( index, newObject ) )
        {
            DestroyObject( prevValue );
            return Success::True;
        }

        return SerializationException::Create( deser, fmt::format( "Failed to set value of type [{}] into array of type [{}] at index {}.",
                                                                    newObject.get_type(), elementType, index ) );
    }
    else
    {
        std::string errorMessage = fmt::format( "Can't convert object of type [{}] to array element type [{}] at index {}.",
                                                newObject.get_type(), elementType, index );

        return SerializationException::Create( deser, std::move( errorMessage ) );
    }
}

// ================================ //
//
ReturnResult                        SerializationCore::SetNullptrProperty   ( const IDeserializer& deser, const rttr::instance& parent, rttr::property prop )
{
    // I don't know how to force RTTR to create nullptr variant in generic way.
    // The problem is, nullptr can't be set or wrappers, only for raw pointers.
    // We need this workround to set nullptr for both pointers and wrappers.

    // First let's take previous value. We need it, because we want to have typed value.
    rttr::variant prevValue = prop.get_value( parent );
    rttr::variant workValue = prevValue;
    rttr::variant nullptrValue;
    TypeID initialType = workValue.get_type();
    TypeID type = workValue.get_type();

    if( type.is_wrapper() )
    {
        // We extract value from wrapper. We expect that extracted type
        // is pointer. If it's reference, we can't set nullptr whatsoever.
        workValue = workValue.extract_wrapped_value();
        type = workValue.get_type();
    }
    
    if( type.is_pointer() )
    {
        // First let's make copy of pointer. Next set internal pointer to nullptr.
        // Note, that we didn't modified prevValue in reality, since nullptrValue
        // got only copy of pointer.
        // Cast to Object*& assumes, that all pointers have the same size, so it doesn't
        // matter on which type we operate.
        nullptrValue = workValue;
        Object*& value_ref = rttr::variant_cast< Object*& >( workValue );
        value_ref = nullptr;

        if( initialType.is_wrapper() )
        {
            // We must convert unwrapped wrapper back to wrapped type.
            // Note that we couldn't convert nullptr directly to wrapped type, because
            // such conversion is not supported.
            // Note: We don't check if it succeded - setting will fail, if it didn't.
            nullptrValue.convert( TypeID( prevValue.get_type() ) );
        }

        if( prop.set_value( parent, nullptrValue ) )
        {
            DestroyObject( prevValue );
            return Success::True;
        }
    }

    return SerializationException::Create( deser, fmt::format( "Can't set nullptr for property [{}] of type [{}].",
                                                                prop.get_name().to_string(),
                                                                prop.get_type().get_name().to_string() ) );
}

// ================================ //
//
Nullable< rttr::variant >		    SerializationCore::CreateInstance	    ( TypeID type )
{
    if( !type.is_valid() )
        return fmt::format( "Failed to create object. Invalid type." );

	TypeID typeToCreate = GetRawWrappedType( type );
	rttr::variant object = typeToCreate.create();

    if( object.is_valid() )
        return object;
    
    return fmt::format( "Failed to create object of type [{}].", typeToCreate );
}

// ================================ //
//
Nullable< rttr::variant >           SerializationCore::CreateInstance       ( rttr::string_view typeName )
{
    TypeID type = TypeID::get_by_name( typeName );
    
    if( !type.is_valid() )
        return fmt::format( "Failed to create object of type [{}]. No such type.", typeName.to_string() );

    return CreateInstance( type );
}

// ================================ //
//
ReturnResult                        SerializationCore::ResizeArray          ( const IDeserializer& deser, rttr::variant_sequential_view& arrayView, Size newSize )
{
    if( newSize != arrayView.get_size() )
    {
        if( arrayView.is_dynamic() )
        {
            if( newSize < arrayView.get_size() )
            {
                // Destroy elements that will disapear after resizing.
                for( long int idx = (long int)newSize - 1; idx < arrayView.get_size(); idx++ )
                    DestroyObject( arrayView.get_value( idx ) );
            }

            arrayView.set_size( newSize );
        }
        else
        {
            return SerializationException::Create( deser, fmt::format( "Can't resize readonly array of type: [{}]",
                                                                        arrayView.get_type() ) );
        }
    }
    return Success::True;
}

// ================================ //
//
Nullable< VariantWrapper >          SerializationCore::RemapBoundByValue    ( const IDeserializer& deser, Nullable< VariantWrapper >&& result, rttr::string_view name, TypeID expectedType )
{
    // If element was bound by value, we need different logic. Deserialize functions
    // will think, that they got reference to previous value from property, but in reality
    // we got copy of this value. That's why we must remap VariantWrapper from reference to new value.
    // Otherwise outside logic won't set property, thinking that it was deserialized in place.
    if( IsBoundByValue( expectedType ) )
    {
        // This means that structure was copied. It is not recomended to bind value as copy.
        // Probably someone forgot about it and we should warn him.
        ///@todo This warning should be conditional depending on flag in SerializationContext.
        Warn< SerializationException >( deser, fmt::format( "Performance Warning. Property [{}] value have been copied, while deserializing."
                                                            " Bind property as pointer or as reference to avoid copying.",
                                                            name.to_string() ) );

        if( !result.IsValid() )
            return std::move( result );

        if( result.Get().IsPrevious() )
            return VariantWrapper::FromNew( std::move( result.Get().GetPrevious().get() ) );

        // This is case when deserialization created new value anyway.
        return std::move( result );
    }

    return std::move( result );
}

// ================================ //
//
std::string			                SerializationCore::WstringToUTF		( const std::wstring& str )
{
	return Convert::ToString( str );
}

// ================================ //
//
std::wstring		                SerializationCore::UTFToWstring		( const std::string& str )
{
	return Convert::FromString< std::wstring >( str ).Get();
}

//====================================================================================//
//				SerializeProperty template specialization
//====================================================================================//

// ================================ //
//
template<>
static void		SerializationCore::SerializeProperty< char >			( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue )
{
	char character = propertyValue.get_value< char >();
	ser.SetAttribute( name.to_string(), std::string( 1, character ) );
}

// ================================ //
//
template<>
void			SerializationCore::SerializeProperty< std::wstring >	( ISerializer& ser, rttr::string_view name, const rttr::variant& propertyValue )
{
    std::wstring str = propertyValue.get_value< std::wstring >();
    ser.SetAttribute( name.to_string(), WstringToUTF( str ) );
}


//====================================================================================//
//				DeserializeProperty template specialization
//====================================================================================//


// ================================ //
//
template<>
std::wstring            SerializationCore::DeserializeProperty< std::wstring >			( const IDeserializer& deser, rttr::string_view name )
{
    return UTFToWstring( deser.GetAttribute( name.to_string(), TypeDefaultValue< std::string >() ) );
}

// ================================ //
//
template<>
char				    SerializationCore::DeserializeProperty< char >					( const IDeserializer& deser, rttr::string_view name )
{
    auto str = deser.GetAttribute( name.to_string(), std::string() );

    if( str.size() == 1 )
        return str[ 0 ];
    ///@todo Error handling.
    return 'e';     // rror :P
}

}	// sw
