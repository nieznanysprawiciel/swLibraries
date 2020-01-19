/**
@file SerialziationCore.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Serialization/stdafx.h"
#include "SerializationCore.h"


#include "swCommonLib/Common/Converters/Convert.h"
#include "swCommonLib/Common/fmt.h"



namespace sw
{


// ================================ //
//
const std::vector< rttr::property >&        SerializationCore::GetTypeFilteredProperties		( rttr::type objType, SerializationContext* context )
{
	objType = objType.get_raw_type();

	auto iter = context->TypeProperties.find( objType );
	if( iter == context->TypeProperties.end() )
	{
		auto result = context->TypeProperties.insert( std::make_pair( objType, std::vector< rttr::property >() ) );
		auto& propVec = result.first->second;

		//MetaDataType saveFlag;
		MetaDataType saveFlag = MetaDataType::Serialize;
		//if( context->SaveWholeMap )
		//	saveFlag = MetaDataType::Serialize;
		//else
		//	saveFlag = MetaDataType::AllowInSaveFile;


		auto properties = objType.get_properties();

		for( auto& property : properties )
		{
			if( ShouldSave( property, saveFlag ) )
				propVec.push_back( property );
		}

		return propVec;
	}
	else
		return iter->second;
}

// ================================ //
//
bool					SerializationCore::ShouldSave				( rttr::property prop, MetaDataType saveFlag )
{
	auto saveFlagMeta = prop.get_metadata( saveFlag );
	if( !saveFlagMeta.is_valid() )
		return true;

	assert( saveFlagMeta.is_type< bool >() );

	return saveFlagMeta.get_value< bool >();
}

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
    if( typeDesc.SerializeFun )
        typeDesc.SerializeFun( ser, value, typeDesc );
    else
        SerializePropertiesVec( ser, value, typeDesc.Properties );

    ser.Exit();	//	prop.get_name()
}

// ================================ //
//
void                    SerializationCore::SerializePolymorphic     ( ISerializer& ser, rttr::string_view name, const rttr::instance& value )
{
    auto dynamicType = SerializationCore::GetRealType( value );
    assert( IsPolymorphicType( dynamicType ) );

    ser.EnterObject( name.to_string() );
    SerializeObject( ser, dynamicType.get_name(), value );
    ser.Exit();	//	prop.get_name()
}

// ================================ //
//
void					SerializationCore::SerializePolymorphic		( ISerializer& ser, const rttr::instance& object, rttr::property prop )
{
    SerializePolymorphic( ser, prop.get_name(), prop.get_value( object ) );
}

// ================================ //
//
void					SerializationCore::SerializeNotPolymorphic	( ISerializer& ser, const rttr::instance& object, rttr::property prop )
{
    assert( !IsPolymorphicType( prop.get_type() ) );
    SerializeObject( ser, prop.get_name(), prop.get_value( object ) );
}

// ================================ //
//
void					SerializationCore::SerializePropertiesVec	( ISerializer& ser, const rttr::instance& object, const std::vector< rttr::property >& properties )
{
	for( auto& property : properties )
	{
		bool serialized = false;
		serialized = serialized || SerializeBasicTypes( ser, object, property );
		serialized = serialized || SerializeStringTypes( ser, object, property );
		serialized = serialized || SerializeEnumTypes( ser, object, property );
		serialized = serialized || SerializeArrayTypes( ser, object, property );
		serialized = serialized || SerializeObjectTypes( ser, object, property );
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
void					SerializationCore::DefaultDeserialize		( const IDeserializer& deser, Object* object )
{
	DefaultDeserializeImpl( deser, object, object->GetType() );
}

// ================================ //
//
void					SerializationCore::DefaultDeserializeImpl	( const IDeserializer& deser, const rttr::instance& object, rttr::type dynamicType )
{
	auto objectType = dynamicType;
	auto& properties = SerializationCore::GetTypeFilteredProperties( objectType, deser.GetContext< SerializationContext >() );

	for( auto& property : properties )
	{
		auto propertyType = property.get_type();

		bool deserialized = DeserializeBasicTypes( deser, object, property );
		deserialized = deserialized || DeserializeStringTypes( deser, object, property );
		deserialized = deserialized || DeserializeEnumTypes( deser, object, property );
		deserialized = deserialized || DeserializeArrayTypes( deser, object, property );
		deserialized = deserialized || DeserializeObjectTypes( deser, object, property );
	}
}



/**@brief Deserializuje podstawowe typy.

Funkcja sprawdza typ w³asciwoœci i deserializuje go tylko je¿eli jest jednym z obs³ugiwanych
przez ni¹ typów. W przeciwnym razie nie robi nic.

@return Funkcja zwraca true, je¿eli uda³o jej siê obs³u¿yæ podany typ.*/
bool			SerializationCore::DeserializeBasicTypes			( const IDeserializer& deser, const rttr::instance& object, rttr::property prop )
{
	auto propertyType = prop.get_type();

	if( !propertyType.is_arithmetic() )
		return false;

	if( propertyType == rttr::type::get< float >() )
		SerializationCore::DeserializeProperty< float >( deser, prop, object );
	else if( propertyType == rttr::type::get< bool >() )
		SerializationCore::DeserializeProperty< bool >( deser, prop, object );
	else if( propertyType == rttr::type::get< int32 >() )
		SerializationCore::DeserializeProperty< int32 >( deser, prop, object );
	else if( propertyType == rttr::type::get< uint32 >() )
		SerializationCore::DeserializeProperty< uint32 >( deser, prop, object );
	else if( propertyType == rttr::type::get< int16 >() )
		SerializationCore::DeserializeProperty< int16 >( deser, prop, object );
	else if( propertyType == rttr::type::get< uint16 >() )
		SerializationCore::DeserializeProperty< uint16 >( deser, prop, object );
	else if( propertyType == rttr::type::get< int8 >() )
		SerializationCore::DeserializeProperty< int8 >( deser, prop, object );
	else if( propertyType == rttr::type::get< uint8 >() )
		SerializationCore::DeserializeProperty< uint8 >( deser, prop, object );
	else if( propertyType == rttr::type::get< int64 >() )
		SerializationCore::DeserializeProperty< int64 >( deser, prop, object );
	else if( propertyType == rttr::type::get< uint64 >() )
		SerializationCore::DeserializeProperty< uint64 >( deser, prop, object );
	else if( propertyType == rttr::type::get< double >() )
		SerializationCore::DeserializeProperty< double >( deser, prop, object );
	else if( propertyType == rttr::type::get< char >() )
		SerializationCore::DeserializeProperty< char >( deser, prop, object );
	else
		return false;

	return true;
}

/**@brief Deserializuje std::string i std::wstring.

@return Returns true when object have been deserialized. Otherwise you should try with functions deserializing other types.*/
bool	SerializationCore::DeserializeStringTypes				( const IDeserializer& deser, const rttr::instance& object, rttr::property prop )
{
	auto propertyType = prop.get_type();

	if( propertyType == rttr::type::get< std::string >() )
		SerializationCore::DeserializeProperty< std::string >( deser, prop, object );
	else if( propertyType == rttr::type::get< std::wstring >() )
		SerializationCore::DeserializeProperty< std::wstring >( deser, prop, object );
	else
		return false;

	return true;
}

/**@brief Deserializes enum properties from string.

@return Returns true when object have been deserialized. Otherwise you should try with functions deserializing other types.*/
bool	SerializationCore::DeserializeEnumTypes					( const IDeserializer& deser, const rttr::instance& object, rttr::property prop )
{
	auto propertyType = prop.get_type();

	if( !propertyType.is_enumeration() )
		return false;

	assert( propertyType.is_valid() );		/// Type haven't been registered.
	assert( propertyType.is_enumeration() );

	rttr::enumeration enumVal = propertyType.get_enumeration();

	auto enumString = deser.GetAttribute( prop.get_name().to_string(), "" );
	rttr::variant value = enumVal.name_to_value( enumString );

	prop.set_value( object, value );

	return true;
}

/**@brief Deserializes arrays.

@return Returns true when object have been deserialized. Otherwise you should try with functions deserializing other types.*/
bool	SerializationCore::DeserializeArrayTypes				( const IDeserializer& deser, const rttr::instance& object, rttr::property prop )
{
	TypeID propertyType = SerializationCore::GetWrappedType( prop.get_type() );
	if( !propertyType.is_sequential_container() )
		return false;

	auto arrayVariant = prop.get_value( object );
	auto arrayView = arrayVariant.create_sequential_view();

	assert( arrayView.is_valid() );
	assert( arrayView.get_rank() == 1 );
	if( arrayView.get_rank() != 1 )
		return true;

	TypeID arrayElementType = arrayView.get_rank_type( 1 );
	assert( arrayElementType.is_class() || arrayElementType.get_raw_type().is_class() );
	if( !arrayElementType.is_class() && !arrayElementType.get_raw_type().is_class() )
		return true;

	if( deser.EnterArray( prop.get_name().to_string() ) )
	{
		if( arrayView.is_dynamic() )
		{
			// Array size should be only hint for deserialization.
			auto arraySize = deser.GetAttribute( "ArraySize", 0 );
			if( arraySize != 0 && !prop.is_readonly() )
				arrayView.set_size( arraySize );
		}


		int idx = 0;
		auto element = arrayView.begin();

		if( deser.FirstElement() )
		{
			do
			{
				// Resize array if it's posible.
				if( arrayView.get_size() <= idx )
				{
					if( arrayView.is_dynamic() && !prop.is_readonly() )
						arrayView.set_size( idx + 1 );	// Performance penalty. Resizing vector each time by one element.
					else
					{
						Warn< SerializationException >( deser, fmt::format( "Trying to insert into readonly array of type: [{}]"
														                    " more elements then array's capacity. Rest of elements will be ignored.",
                                                                            propertyType ) );
						break;
					}
				}

				// Process generic objects. We must get real object type.
				if( IsPolymorphicType( arrayElementType ) )
				{
                    if( deser.FirstElement() )
                    {
                        auto newClassResult = DefaultDeserializePolymorphicImpl( deser, deser.GetName(), DeserialTypeDesc() );
                        if( newClassResult.IsValid() )
                        {
                            rttr::variant newClass = std::move( newClassResult ).Get();
                            if( newClass.convert( TypeID( arrayElementType ) ) )
                            {
                                arrayView.set_value( idx, newClass );
                            }
                            else
                            {
                                Warn< SerializationException >( deser, fmt::format( "Type [{}] can't be converted to array element type [{}].",
                                                                                    newClass.get_type(),
                                                                                    arrayElementType ) );
                            }
                        }
                        else
                        {
                            Warn< SerializationException >( deser, fmt::format( "Deserialization of array element of type [{}] failed with error: {}",
                                                                                arrayElementType,
                                                                                newClassResult.GetErrorReason() ) );
                        }

                        if( deser.NextElement() )
                        {
                            // Warning: Property shouldn't have multiple objects.
                            Warn< SerializationException >( deser, fmt::format( "Deserialization of array element of type [{}]. Multiple polymorphic "
                                                                                "objects defined. Deserializing only first.",
                                                                                arrayElementType ) );
                        }

                        deser.Exit();
                    }
                    else
                    {
                        Warn< SerializationException >( deser, fmt::format( "Deserialization of array element of type [{}]. Type of polymorphic object not specified.",
                                                                            arrayElementType ) );
                    }
				}
				else
				{

					// Non generic objects use default deserialization.
					DefaultDeserializeImpl( deser, *element, arrayElementType );
				}

				idx++;
				element++;
			} while( deser.NextElement() );

			deser.Exit();
		}

		if( !arrayView.is_dynamic() && !propertyType.is_pointer() )
		{
			// Static arrays should be declared as readonly properties bound by reference.
			// If they are not bound by reference, variant makes copy of array and we must set this
			// copy to real field in class.
			prop.set_value( object, arrayVariant );

			///@todo This warning should be conditional depending on flag in SerializationContext.
			Warn< SerializationException >( deser, fmt::format( "Performance Warning. Property [{}] value have been copied, while deserializing."
											                    " Bind property as pointer or as reference to avoid copying.",
                                                                prop.get_name().to_string() ) );
		}

		deser.Exit();

		return true;
	}
	else
	{
		///@todo This warning should be conditional depending on flag in SerializationContext.
		Warn< SerializationException >( deser, fmt::format( "Property [{}] not found in file. Value remained unchanged.", prop.get_name().to_string() ) );
	}

	return false;
}

/**@brief Deserializes structures and generic objects.

@return Returns true when object have been deserialized. Otherwise you should try with functions deserializing other types.*/
bool	SerializationCore::DeserializeObjectTypes				( const IDeserializer& deser, const rttr::instance& object, rttr::property prop )
{
	TypeID propertyType = prop.get_type();
	TypeID rawType = propertyType.get_raw_type();

	if( !rawType.is_class() )
		return false;

    if( deser.EnterObject( prop.get_name().to_string() ) )
    {
        if( IsPolymorphicType( propertyType ) )
        {
            // Retrieve dynamic type of object from deserializer and create new object.
            DeserializePolymorphic( deser, object, prop );
        }
        else
        {
            DeserializeNotPolymorphic( deser, object, prop );
        }

        deser.Exit();	// prop.get_name
    }
    else
    {
        ///@todo This warning should be conditional depending on flag in SerializationContext.
        Warn< SerializationException >( deser, fmt::format( "Property [{}] not found in file. Value remained unchanged.", prop.get_name().to_string() ) );
    }

	return true;        // Tell outside world, that it doesn't need to look for other function to deal with this property.
}

// ================================ //
//
Nullable< rttr::variant >           SerializationCore::DeserializeBasicTypes        ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    return Nullable<rttr::variant>();
}

// ================================ //
//
Nullable< rttr::variant >           SerializationCore::DeserializeStrings           ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    if( expectedType == rttr::type::get< std::string >() )
        return rttr::variant( SerializationCore::DeserializeProperty< std::string >( deser, name ) );
    else if( expectedType == rttr::type::get< std::wstring >() )
        return rttr::variant( SerializationCore::DeserializeProperty< std::wstring >( deser, name ) );
    else
        return SerializationException::Create( deser, fmt::format( "Type [{}] was none of string types.", expectedType ) );
}

// ================================ //
//
Nullable< rttr::variant >           SerializationCore::DeserializeEnums             ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    /// @todo Consider checking these conditions and returning exception on fail.
    assert( expectedType.is_enumeration() );    /// Should be checked by caller.
    assert( expectedType.is_valid() );		    /// Type haven't been registered.

    rttr::enumeration enumVal = expectedType.get_enumeration();

    auto enumFieldString = deser.GetAttribute( name.to_string(), "" );
    rttr::variant value = enumVal.name_to_value( enumFieldString );

    if( value.is_valid() )
        return value;
    
    return SerializationException::Create( deser, fmt::format( "Enum of type [{}] has no field [{}], while deserializing [{}].",
                                                                expectedType,
                                                                enumFieldString,
                                                                name.to_string() ) );
}

// ================================ //
//
Nullable< rttr::variant >           SerializationCore::DeserializeArrays            ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    return Nullable<rttr::variant>();
}

// ================================ //
//
Nullable< rttr::variant >           SerializationCore::DeserializeObjects           ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    if( deser.EnterObject( name.to_string() ) )
    {
        auto result = DeserializeObjectsSelector( deser, name, prevValue, expectedType );
        deser.Exit();	// EnterObject( name )

        return result;
    }
    else
    {
        ///@todo This warning should be conditional depending on flag in SerializationContext.
        Warn< SerializationException >( deser, fmt::format( "Property [{}] not found in file. Value remained unchanged.", name.to_string() ) );
        return prevValue;
    }
}

// ================================ //
//
Nullable< rttr::variant >           SerializationCore::DeserializeObjectsSelector   ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    TypeID expectedTypeUnwrapped = SerializationCore::GetRawWrappedType( expectedType );
    
    // Consider returning exception on false.
    assert( !expectedTypeUnwrapped.is_class() );

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
Nullable< rttr::variant >           SerializationCore::DeserializePolymorphic       ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    return Nullable<rttr::variant>();
}

// ================================ //
//
Nullable< rttr::variant >           SerializationCore::DeserializeNotPolymorphic    ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    return Nullable<rttr::variant>();
}

// ================================ //
//
Nullable< rttr::variant >           SerializationCore::DeserializeTypesDispatcher   ( const IDeserializer& deser, rttr::string_view name, rttr::variant& prevValue, TypeID expectedType )
{
    auto expectedTypeUnwrapped = SerializationCore::GetRawWrappedType( expectedType );

    if( expectedTypeUnwrapped.is_arithmetic() )
        return DeserializeBasicTypes( deser, name, prevValue, expectedType );
    if( expectedTypeUnwrapped.is_enumeration() )
        return DeserializeEnums( deser, name, prevValue, expectedType );
    if( SerializationCore::IsStringType( expectedTypeUnwrapped ) )
        return DeserializeStrings( deser, name, prevValue, expectedType );
    if( expectedTypeUnwrapped.is_array() )
        return DeserializeArrays( deser, name, prevValue, expectedType );
    if( expectedTypeUnwrapped.is_class() )
        return DeserializeObjects( deser, name, prevValue, expectedType );

    return SerializationException::Create( deser, fmt::format( "Type [{}] isn't any of class types known to serialization.", expectedType ) );
}

// ================================ //
//
void				SerializationCore::DeserializePolymorphic		( const IDeserializer& deser, const rttr::instance& parent, rttr::property prop )
{
	auto prevClassVal = prop.get_value( parent );
	TypeID prevClassType = GetRawWrappedType( rttr::instance( prevClassVal ).get_derived_type() );

    // Parent class default constructor could have created this property.
    // We must destroy it, before we assign new value.
    if( prevClassVal != nullptr )
    {
        // Destroy object and set nullptr.
        DestroyObject( prevClassVal );
        prop.set_value( parent, nullptr );

        Warn< SerializationException >( deser, fmt::format( "Property [{}], value of type [{}] already existed but was destroyed.",
                                                            prop.get_name().to_string(),
                                                            prevClassType ) );
    }

    if( deser.FirstElement() )
    {
        auto objectResult = DefaultDeserializePolymorphicImpl( deser, deser.GetName(), DeserialTypeDesc() );
        if( objectResult.IsValid() )
        {
            auto result = SetObjectProperty( deser, parent, prop, objectResult.Get() );
        
            if( !result.IsValid() )
            {
                // Destroy object and set nullptr.
                DestroyObject( objectResult.Get() );
                prop.set_value( parent, nullptr );

                Warn< SerializationException >( deser, fmt::format( "Deserialization of property [{}] failed with error: {}",
                                                                    prop.get_name().to_string(),
                                                                    result.GetErrorReason() ) );
            }
        }
        else
        {
            Warn< SerializationException >( deser, fmt::format( "Deserialization of property [{}] failed with error: {}",
                                                                prop.get_name().to_string(),
                                                                objectResult.GetErrorReason() ) );
        }

        if( deser.NextElement() )
        {
            // Warning: Property shouldn't have multiple objects.
            Warn< SerializationException >( deser, fmt::format( "Deserialization of property [{}]. Multiple polymorphic objects defined. Deserializing only first.",
                                                                prop.get_name().to_string() ) );
        }

        deser.Exit();	// FirstElement
    }
    else
    {
        Warn< SerializationException >( deser, fmt::format( "Deserialization of property [{}]. Type of polymorphic object not specified.",
                                                            prop.get_name().to_string() ) );
    }
}

// ================================ //
//
void				SerializationCore::DeserializeNotPolymorphic	( const IDeserializer& deser, const rttr::instance& object, rttr::property prop )
{
    TypeID propertyType = prop.get_type();
    TypeID wrappedType = GetWrappedType( propertyType );
 
    // We must handle cases, when structure is nullptr. First we must create new object and then deserialize it.
    auto structVal = prop.get_value( object );
    if( structVal == nullptr )
    {
        structVal = CreateAndSetObjectProperty( deser, object, prop, propertyType );

        if( !structVal.is_valid() )
            // Warning will be added in CreateAndSetObjectProperty function.
            return;
    }

	DefaultDeserializeImpl( deser, structVal, wrappedType );

	if( !propertyType.is_wrapper() && !propertyType.is_pointer() )
	{
		// This means that structure was copied. We must set property value to this copy.
		prop.set_value( object, structVal );

		///@todo This warning should be conditional depending on flag in SerializationContext.
		Warn< SerializationException >( deser, fmt::format( "Performance Warning. Property [{}] value have been copied, while deserializing."
										                    " Bind property as pointer or as reference to avoid copying.",
                                                            prop.get_name().to_string() ) );
	}
}

// ================================ //
//
Nullable< rttr::variant >           SerializationCore::DefaultDeserializePolymorphicImpl        ( const IDeserializer& deser, rttr::string_view typeName, DeserialTypeDesc& desc )
{
    // Check what type of object we should create.
    auto newClassResult = CreateInstance( typeName );

    if( !newClassResult.IsValid() )
    {
        deser.Exit();	// FirstElement
        return SerializationException::Create( deser, fmt::format( "Failed to create object. {}",
                                                                    newClassResult.GetErrorReason() ) );
    }

    rttr::variant newClass = newClassResult.Get();

    DefaultDeserializeImpl( deser, newClassResult.Get(), GetRawWrappedType( newClass.get_type() ) );
    
    return newClassResult.Get();
}

// ================================ //
//
rttr::variant		SerializationCore::CreateAndSetObjectProperty	( const IDeserializer& deser, const rttr::instance& parent, rttr::property prop, TypeID dynamicType )
{
    /// @todo Proper error handling. This function probably will be splitted in future.
    auto newClassResult = CreateInstance( dynamicType );
	rttr::variant newClass = newClassResult.IsValid() ? newClassResult.Get() : rttr::variant();

	TypeID propertyType = prop.get_type();
	TypeID createdType = newClass.get_type();

	if( !( propertyType.is_wrapper() && !createdType.is_wrapper() ) &&
		!( !propertyType.is_wrapper() && createdType.is_wrapper() ) )
	{
		if( newClass.convert( prop.get_type() ) &&
			prop.set_value( parent, newClass ) )
		{
			return newClass;
		}
	}

	// Error diagnostic. Determine why setting object failed and set warning in context.
	// RTTR should do this internally in covert and set_property functions, so we can delay
	// some checks to handle error cases.


	// We created object so we must destroy it. Otherwise it could lead to memory leaks especially
	// in case of raw pointers. Shared pointers in variants should be destroyed automatic after scope end.
	DestroyObject( newClass );

	TypeID wrappedPropType = GetRawWrappedType( propertyType );
	TypeID wrappedClassType = GetRawWrappedType( dynamicType );

	if( !wrappedClassType.is_derived_from( wrappedPropType ) )
	{
		std::string errorMessage = "Property type [" + wrappedPropType.get_name().to_string()
								+ "] is not base class of created object type ["
								+ wrappedClassType.get_name().to_string() + "].";

		Warn< SerializationException >( deser, errorMessage );
	}

	// Wrapped and raw pointer mismatch.

	if( propertyType.is_wrapper() && !createdType.is_wrapper() )
	{
		/// @todo When created type is raw pointer and property is wrapped type, we could handle this case
		/// by creating wrapper from pointer. Consider this in future. Many problems could apear, when it comes to
		/// ownership of memory and so on.
		std::string errorMessage = "Property [" + prop.get_name().to_string()
									+ "] setting error. Wrapper and raw pointer mismatch between property of type ["
									+ propertyType.get_name().to_string()
									+ "] and created class of type ["
									+ createdType.get_name().to_string() + "].";

		Warn< SerializationException >( deser, errorMessage );
	}
	else if( !propertyType.is_wrapper() && createdType.is_wrapper() )
	{
		// If propertyType is raw pointer and createdType is wrapper we can't do anything with this.
		// There's no way in rttr to steal wrapped value from shared_ptr.
		/// @todo We must take into considerations other wrapper types which not necessary take ownership of
		/// object. To do this we must be able to determine wrapper template type and have some traits connected
		/// to ownership. Think about it in future.
		std::string errorMessage = "Property [" + prop.get_name().to_string()
									+ "] setting error. Wrapper and raw pointer mismatch between property of type ["
									+ propertyType.get_name().to_string()
									+ "] and created class of type ["
									+ createdType.get_name().to_string() + "].";

		Warn< SerializationException >( deser, errorMessage );
	}
	else if( propertyType.is_wrapper() && createdType.is_wrapper() && propertyType != createdType )
	{
		// Classes types are the same, but wrappers are different.

		std::string errorMessage = "Property [" + prop.get_name().to_string()
									+ "] setting error. Wrappers mismatch between property of type ["
									+ propertyType.get_name().to_string()
									+ "] and created class of type ["
									+ createdType.get_name().to_string() + "].";

		Warn< SerializationException >( deser, errorMessage );
	}

	if( !GetRawWrappedType( createdType ).get_constructor().is_valid() )
	{
		std::string errorMessage = "Can't construct object of type ["
									+ createdType.get_name().to_string()
									+ "]. Zero arguments constructor wasn't declared in rttr for this class.";

		Warn< SerializationException >( deser, errorMessage );
	}

	return rttr::variant();
}

// ================================ //
//
ReturnResult                        SerializationCore::SetObjectProperty    ( const IDeserializer& deser, const rttr::instance& parent, rttr::property prop, rttr::variant& newObject )
{
    TypeID propertyType = prop.get_type();
    TypeID createdType = newObject.get_type();

    if( !( propertyType.is_wrapper() && !createdType.is_wrapper() ) &&
        !( !propertyType.is_wrapper() && createdType.is_wrapper() ) )
    {
        if( newObject.convert( prop.get_type() ) &&
            prop.set_value( parent, newObject ) )
        {
            return Success::True;
        }
        else
        {
		    std::string errorMessage = fmt::format( "Property [{}] setting error. Can't convert object of type [{}].",
                                                    prop.get_name().to_string(),
                                                    createdType );

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
        std::string errorMessage = fmt::format( "Property [{}] setting error. Wrapper and raw pointer mismatch between"
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
        std::string errorMessage = fmt::format( "Property [{}] setting error. Wrapper and raw pointer mismatch between property"
                                                " of type [{}] and created class of type [{}].",
                                                prop.get_name().to_string(),
                                                propertyType,
                                                createdType );

        return SerializationException::Create( deser, std::move( errorMessage ) );
	}
	else if( propertyType.is_wrapper() && createdType.is_wrapper() && propertyType != createdType )
	{
		// Classes types are the same, but wrappers are different.

		std::string errorMessage = fmt::format( "Property [{}] setting error. Wrappers mismatch between property"
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

    return SerializationException::Create( deser, fmt::format( "Unknown error while setting object for property [{}].", propertyType.get_name().to_string() ) );
}

// ================================ //
//
Nullable< rttr::variant >		    SerializationCore::CreateInstance	( TypeID type )
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
Nullable< rttr::variant >           SerializationCore::CreateInstance   ( rttr::string_view typeName )
{
    TypeID type = TypeID::get_by_name( typeName );
    
    if( !type.is_valid() )
        return fmt::format( "Failed to create object of type [{}]. No such type.", typeName.to_string() );

    return CreateInstance( type );
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

template	void	SerializationCore::SerializeProperty< unsigned int >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< float >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< double >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< int >		( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< bool >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< int8 >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< uint8 >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< int16 >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< uint16 >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< int32 >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< uint32 >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< int64 >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< uint64 >	( ISerializer& ser, rttr::property prop, const rttr::instance& object );



/**@brief Specjalizacja dla std::wstring.*/
template<>
void			SerializationCore::SerializeProperty< std::wstring >	( ISerializer& ser, rttr::property prop, const rttr::instance& object )
{
	std::wstring str = GetPropertyValue< std::wstring >( prop, object );
	ser.SetAttribute( prop.get_name().to_string(), WstringToUTF( str ) );
}

// ================================ //
//
template<>
static void		SerializationCore::SerializeProperty< char >			( ISerializer& ser, rttr::property prop, const rttr::instance& object )
{
	char character = GetPropertyValue< char >( prop, object );
	ser.SetAttribute( prop.get_name().to_string(), std::string( 1, character ) );
}

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

template	void	SerializationCore::DeserializeProperty< unsigned int >	( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< float >			( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< double >		( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< int >			( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< bool >			( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< int16 >			( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< uint16 >		( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< int32 >			( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< uint32 >		( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< int64 >			( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< uint64 >		( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< int8 >			( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< uint8 >			( const IDeserializer& deser, rttr::property prop, const rttr::instance& object );




/**@brief Specjalizacja dla std::wstring.*/
template<>
void			        SerializationCore::DeserializeProperty< std::wstring >	( const IDeserializer& deser, rttr::property prop, const rttr::instance& object )
{
	std::wstring str = GetPropertyValue< std::wstring >( prop, object );
	SetPropertyValue( prop, object, UTFToWstring( deser.GetAttribute( prop.get_name().to_string(), TypeDefaultValue< std::string >() ) ) );
}

// ================================ //
//
template<>
void		            SerializationCore::DeserializeProperty< char >			( const IDeserializer& deser, rttr::property prop, const rttr::instance& object )
{
	auto str = deser.GetAttribute( prop.get_name().to_string(), std::string() );

	if( str.size() == 1 )
		SetPropertyValue( prop, object, str[ 0 ] );
	///@todo Error handling.
}

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
}

}	// sw
