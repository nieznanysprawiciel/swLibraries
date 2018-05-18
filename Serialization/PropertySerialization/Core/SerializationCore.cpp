/**
@file SerialziationCore.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Serialization/PropertySerialization/stdafx.h"
#include "SerializationCore.h"


#include <codecvt>



namespace sw
{


// ================================ //
//
std::vector< rttr::property >&		SerializationCore::GetTypeFilteredProperties		( rttr::type objType, SerializationContext* context )
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
bool					SerializationCore::ShouldSave				( const rttr::property& prop, MetaDataType saveFlag )
{
	auto saveFlagMeta = prop.get_metadata( saveFlag );
	if( !saveFlagMeta.is_valid() )
		return true;

	assert( saveFlagMeta.is_type< bool >() );

	return saveFlagMeta.get_value< bool >();
}

// ================================ //
/// We support only polymorphic types derived from EngineObject.
bool					SerializationCore::IsPolymorphicType		( TypeID type )
{
	return type.is_derived_from< EngineObject >();
}

// ================================ //
//
void					SerializationCore::DefaultSerialize			( ISerializer& ser, const EngineObject* object )
{
	DefaultSerializeImpl( ser, object, object->GetType() );
}


// ================================ //
//
void					SerializationCore::DefaultSerializeImpl		( ISerializer& deser, const rttr::instance& object, rttr::type dynamicType )
{
	auto wrappedType = SerializationCore::GetRealType( object );

	auto& properties = GetTypeFilteredProperties( wrappedType, deser.GetContext< SerializationContext >() );

	deser.EnterObject( wrappedType.get_raw_type().get_name().to_string() );

	SerializePropertiesVec( &deser, object, properties );

	deser.Exit();	// objectType.get_name()
}

// ================================ //
//
void					SerializationCore::SerializePropertiesVec	( ISerializer* ser, const rttr::instance& object, std::vector< rttr::property >& properties )
{
	for( auto& property : properties )
	{
		bool serialized = false;
		serialized = serialized || SerializeBasicTypes( ser, object, property );
		serialized = serialized || SerializeVectorTypes( ser, object, property );
		serialized = serialized || SerializeStringTypes( ser, object, property );
		serialized = serialized || SerializeEnumTypes( ser, object, property );
		serialized = serialized || SerializeArrayTypes( ser, object, property );
		serialized = serialized || SerializeObjectTypes( *ser, object, property );
	}
}


// ================================ //
//
bool				SerializationCore::SerializeBasicTypes			( ISerializer* ser, const rttr::instance& object, rttr::property& prop )
{
	return SerializeBasicTypes( ser, prop.get_name(), prop.get_value( object ) );
}

// ================================ //
//
bool				SerializationCore::SerializeBasicTypes			( ISerializer* ser, rttr::string_view name, const rttr::variant& propertyValue )
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
bool			SerializationCore::SerializeVectorTypes				( ISerializer* ser, const rttr::instance& object, rttr::property& prop )
{
	auto propertyType = prop.get_type();

	if( propertyType == rttr::type::get< DirectX::XMFLOAT2* >() )
		SerializeProperty< DirectX::XMFLOAT2* >( ser, prop, object );
	else if( propertyType == rttr::type::get< DirectX::XMFLOAT3* >() )
		SerializeProperty< DirectX::XMFLOAT3* >( ser, prop, object );
	else if( propertyType == rttr::type::get< DirectX::XMFLOAT4* >() )
		SerializeProperty< DirectX::XMFLOAT4* >( ser, prop, object );
	else
		return false;

	return true;
}

// ================================ //
//
bool			SerializationCore::SerializeStringTypes				( ISerializer* ser, const rttr::instance& object, rttr::property& prop )
{
	auto propertyType = prop.get_type();

	if( propertyType == rttr::type::get< std::string >() )
		SerializeProperty< std::string >( ser, prop, object );
	else if( propertyType == rttr::type::get< std::wstring >() )
		SerializeProperty< std::wstring >( ser, prop, object );
	else
		return false;

	return true;
}

// ================================ //
//
bool			SerializationCore::SerializeEnumTypes				( ISerializer* ser, const rttr::instance& object, rttr::property& prop )
{
	auto propertyType = prop.get_type();

	if( !propertyType.is_enumeration() )
		return false;

	assert( propertyType.is_valid() );		/// Type haven't been registered.
	assert( propertyType.is_enumeration() );

	rttr::enumeration enumVal = propertyType.get_enumeration();

	ser->SetAttribute( prop.get_name().to_string(), enumVal.value_to_name( prop.get_value( object ) ).to_string() );

	return true;
}

// ================================ //
//
bool			SerializationCore::SerializeArrayTypes				( ISerializer* ser, const rttr::instance& object, rttr::property& prop )
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

	ser->EnterArray( prop.get_name().to_string() );

	if( arrayView.is_dynamic() )
		ser->SetAttribute( "ArraySize", arrayView.get_size() );

	for( auto& element : arrayView )
	{
		// Process generic objects. We must get real object type.
		if( element.get_type().is_pointer() )
		{
			EngineObject* engineObject = element.get_value< EngineObject* >();
			engineObject->Serialize( *ser );
		}
		else
		{
			// Non generic objects use default serialization.
			DefaultSerializeImpl( *ser, element, arrayElementType );
		}
	}

	ser->Exit();

	return false;
}

// ================================ //
//
bool			SerializationCore::SerializeObjectTypes				( ISerializer& ser, const rttr::instance& object, rttr::property& prop )
{
	auto propertyType = prop.get_type();
	if( propertyType.is_wrapper() )
		propertyType = propertyType.get_wrapped_type();

	// Here can be serialized:
	// - structs
	// - structs pointers and references
	// - classes derived from EngineObject (as reference, pointer or value ??)



	bool serialized = true;

	if( propertyType.is_derived_from< EngineObject >() )
		SerializeProperty< EngineObject* >( &ser, prop, object );
	else if( propertyType.is_pointer() )
		SerializeProperty< void* >( &ser, prop, object );
	else
		serialized = false;

	return serialized;
}

// ================================ //
//
void					SerializationCore::DefaultDeserialize		( IDeserializer& deser, EngineObject* object )
{
	DefaultDeserializeImpl( deser, object, object->GetType() );
}

// ================================ //
//
void					SerializationCore::DefaultDeserializeImpl	( IDeserializer& deser, const rttr::instance& object, rttr::type dynamicType )
{
	auto objectType = dynamicType;
	auto& properties = SerializationCore::GetTypeFilteredProperties( objectType, deser.GetContext< SerializationContext >() );

	for( auto& property : properties )
	{
		auto propertyType = property.get_type();

		bool deserialized = DeserializeBasicTypes( &deser, object, property );
		deserialized = deserialized || DeserializeVectorTypes( &deser, object, property );
		deserialized = deserialized || DeserializeStringTypes( &deser, object, property );
		deserialized = deserialized || DeserializeEnumTypes( &deser, object, property );
		deserialized = deserialized || DeserializeArrayTypes( &deser, object, property );
		deserialized = deserialized || DeserializeObjectTypes( &deser, object, property );
	}
}



/**@brief Deserializuje podstawowe typy.

Funkcja sprawdza typ w³asciwoœci i deserializuje go tylko je¿eli jest jednym z obs³ugiwanych
przez ni¹ typów. W przeciwnym razie nie robi nic.

@return Funkcja zwraca true, je¿eli uda³o jej siê obs³u¿yæ podany typ.*/
bool			SerializationCore::DeserializeBasicTypes			( IDeserializer* deser, const rttr::instance& object, rttr::property& prop )
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

/**@brief Deserializuje typy DirectXMath.

@return Returns true when object have been deserialized. Otherwise you should try with functions deserializing other types.*/
bool	SerializationCore::DeserializeVectorTypes				( IDeserializer* deser, const rttr::instance& object, rttr::property& prop )
{
	auto propertyType = prop.get_type();

	if( propertyType == rttr::type::get< DirectX::XMFLOAT2* >() )
		SerializationCore::DeserializeProperty< DirectX::XMFLOAT2* >( deser, prop, object );
	else if( propertyType == rttr::type::get< DirectX::XMFLOAT3* >() )
		SerializationCore::DeserializeProperty< DirectX::XMFLOAT3* >( deser, prop, object );
	else if( propertyType == rttr::type::get< DirectX::XMFLOAT4* >() )
		SerializationCore::DeserializeProperty< DirectX::XMFLOAT4* >( deser, prop, object );
	else
		return false;

	return true;
}

/**@brief Deserializuje std::string i std::wstring.

@return Returns true when object have been deserialized. Otherwise you should try with functions deserializing other types.*/
bool	SerializationCore::DeserializeStringTypes				( IDeserializer* deser, const rttr::instance& object, rttr::property& prop )
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
bool	SerializationCore::DeserializeEnumTypes					( IDeserializer* deser, const rttr::instance& object, rttr::property& prop )
{
	auto propertyType = prop.get_type();

	if( !propertyType.is_enumeration() )
		return false;

	assert( propertyType.is_valid() );		/// Type haven't been registered.
	assert( propertyType.is_enumeration() );

	rttr::enumeration enumVal = propertyType.get_enumeration();

	auto enumString = deser->GetAttribute( prop.get_name().to_string(), "" );
	rttr::variant value = enumVal.name_to_value( enumString );

	prop.set_value( object, value );

	return true;
}

/**@brief Deserializes arrays.

@return Returns true when object have been deserialized. Otherwise you should try with functions deserializing other types.*/
bool	SerializationCore::DeserializeArrayTypes				( IDeserializer* deser, const rttr::instance& object, rttr::property& prop )
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

	deser->EnterArray( prop.get_name().to_string() );

	if( arrayView.is_dynamic() )
	{
		// Array size is should be only hint for deserialization.
		auto arraySize = deser->GetAttribute( "ArraySize", 0 );
		if( arraySize != 0 )
			arrayView.set_size( arraySize );
	}


	int idx = 0;
	auto element = arrayView.begin();

	if( deser->FirstElement() )
	{
		do
		{
			// Resize array if it's posible.
			if( arrayView.get_size() <= idx )
			{
				if( arrayView.is_dynamic() )
					arrayView.set_size( idx + 1 );	// Performance penalty. Resizing vector each time by one element.
				else
				{
					assert( !"Trying to insert to static array more elements then exists." );
					/// @todo Error handling.
				}
			}

			// Process generic objects. We must get real object type.
			if( arrayElementType.is_pointer() )
			{
				assert( !"Implement me" );

				//EngineObject* engineObject = element.get_value< EngineObject* >();
				//engineObject->Deserialize( deser );
			}
			else
			{

				// Non generic objects use default deserialization.
				DefaultDeserializeImpl( *deser, *element, arrayElementType );
			}

			idx++;
			element++;
		} while( deser->NextElement() );
	}

	if( !arrayView.is_dynamic() && !propertyType.is_pointer() )
	{
		// Static arrays should be decalred as readonly properties bound by reference.
		// If they are not bound by reference, variant makes copy of array and we must set this
		// copy to real field in class.
		prop.set_value( object, arrayVariant );
	}

	deser->Exit();

	return false;
}

/**@brief Deserializes structures and generic objects.

@return Returns true when object have been deserialized. Otherwise you should try with functions deserializing other types.*/
bool	SerializationCore::DeserializeObjectTypes	( IDeserializer* deser, const rttr::instance& object, rttr::property& prop )
{
	auto propertyType = prop.get_type();

	if( !propertyType.get_raw_type().is_class() )
		return false;

	if( IsPolymorphicType( propertyType ) )
	{
		// Retrieve dynamic type of object from deserializer and create new object.
		assert( !"Implement me" );

		return true;
	}
	else
	{
		// We must find out whether type is a structure or pointer to structure.
		// Checking type.is_pointer() tell us nothing, because every structure must be bound as pointer.
		// Better get value of property from class and check if it is nullptr.
		auto structVal = prop.get_value( object );
		if( structVal == nullptr )
		{
			// We could construct object, but maybe it would be better, if objects have created it in constructor.
			// @todo Think if we should create structure in deserialization if it is nullptr.
			return true;	// Tell outside world, that it doesn't need to look for other function to deal with this property.
		}
		else
		{
			DeserializeProperty< void* >( deser, prop, object );
		}
	}

	return true;
}

// ================================ //
//
std::string			SerializationCore::WstringToUTF		( const std::wstring& str )
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes( str );
}

// ================================ //
//
std::wstring		SerializationCore::UTFToWstring		( const std::string& str )
{
	std::wstring_convert< std::codecvt_utf8< wchar_t > > myconv;
	return myconv.from_bytes( str );
}

//====================================================================================//
//				SerializeProperty template specialization
//====================================================================================//

template	void	SerializationCore::SerializeProperty< unsigned int >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< float >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< double >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< int >		( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< bool >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< int8 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< uint8 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< int16 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< uint16 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< int32 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< uint32 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< int64 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::SerializeProperty< uint64 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );

/**@brief Template specialization for classes derived from @ref EngineObject.

Function serializes property name as first. Then EngineObject::Serialize method is invoked.*/
template<>
void			SerializationCore::SerializeProperty< EngineObject* >( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	EngineObject* engineObj = GetPropertyValue< EngineObject* >( prop, object );
	if( engineObj )
	{
		ser->EnterObject( prop.get_name().to_string() );
		engineObj->Serialize( *ser );
		ser->Exit();	//	prop.get_name()
	}
}

/**@brief Specjalizacja dla wszystkich obiektów, które nie dziedzicz¹ po EngineObject.

Musz¹ to byæ struktury bez hierarchii dziedziczenia, poniewa¿ nie mo¿na ustaliæ ich dynamicznego typu.*/
template<>
void			SerializationCore::SerializeProperty< void* >( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	void* engineObj = GetPropertyValue< void* >( prop, object );
	if( engineObj )
	{
		ser->EnterObject( prop.get_name().to_string() );

		rttr::variant objVariant( engineObj );
		TypeID realType = prop.get_type();
		objVariant.unsafe_convert_void( realType );

		auto& properties = GetTypeFilteredProperties( realType, ser->GetContext< SerializationContext >() );

		SerializePropertiesVec( ser, objVariant, properties );

		ser->Exit();	//	prop.get_name()
	}
}

/**@brief Specjalizacja dla DirectX::XMFLOAT3.*/
template<>
void			SerializationCore::SerializeProperty< DirectX::XMFLOAT3* >	( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	DirectX::XMFLOAT3* xmFloat = GetPropertyValue< DirectX::XMFLOAT3* >( prop, object );
	ser->EnterObject( prop.get_name().to_string() );

	ser->SetAttribute( "X", xmFloat->x );
	ser->SetAttribute( "Y", xmFloat->y );
	ser->SetAttribute( "Z", xmFloat->z );

	ser->Exit();	// prop.get_name()
}

/**@brief Specjalizacja dla DirectX::XMFLOAT2.*/
template<>
void			SerializationCore::SerializeProperty< DirectX::XMFLOAT2* >	( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	DirectX::XMFLOAT2* xmFloat = GetPropertyValue< DirectX::XMFLOAT2* >( prop, object );
	ser->EnterObject( prop.get_name().to_string() );

	ser->SetAttribute( "X", xmFloat->x );
	ser->SetAttribute( "Y", xmFloat->y );

	ser->Exit();	// prop.get_name()
}

/**@brief Specjalizacja dla DirectX::XMFLOAT4.*/
template<>
void			SerializationCore::SerializeProperty< DirectX::XMFLOAT4* >	( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	DirectX::XMFLOAT4* xmFloat = GetPropertyValue< DirectX::XMFLOAT4* >( prop, object );
	ser->EnterObject( prop.get_name().to_string() );

	ser->SetAttribute( "X", xmFloat->x );
	ser->SetAttribute( "Y", xmFloat->y );
	ser->SetAttribute( "Z", xmFloat->z );
	ser->SetAttribute( "W", xmFloat->w );

	ser->Exit();	// prop.get_name()
}

/**@brief Specjalizacja dla std::wstring.*/
template<>
void			SerializationCore::SerializeProperty< std::wstring >	( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	std::wstring str = GetPropertyValue< std::wstring >( prop, object );
	ser->SetAttribute( prop.get_name().to_string(), WstringToUTF( str ) );
}

// ================================ //
//
template<>
static void		SerializationCore::SerializeProperty< char >			( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	char character = GetPropertyValue< char >( prop, object );
	ser->SetAttribute( prop.get_name().to_string(), std::string( 1, character ) );
}

// ================================ //
//
template<>
static void		SerializationCore::SerializeProperty< char >			( ISerializer* ser, rttr::string_view name, const rttr::variant& propertyValue )
{
	char character = propertyValue.get_value< char >();
	ser->SetAttribute( name.to_string(), std::string( 1, character ) );
}


//====================================================================================//
//				DeserializeProperty template specialization
//====================================================================================//

template	void	SerializationCore::DeserializeProperty< unsigned int >	( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< float >			( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< double >		( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< int >			( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< bool >			( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< int16 >			( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< uint16 >		( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< int32 >			( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< uint32 >		( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< int64 >			( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< uint64 >		( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< int8 >			( IDeserializer* deser, rttr::property prop, const rttr::instance& object );
template	void	SerializationCore::DeserializeProperty< uint8 >			( IDeserializer* deser, rttr::property prop, const rttr::instance& object );



/**@brief Specialization for deserializing generic objects inheriting EngineObject.*/
template<>
void				SerializationCore::DeserializeProperty< EngineObject* >		( IDeserializer* deser, rttr::property prop, const rttr::instance& object )
{
	assert( !"Implement me" );
}

/**@brief Specialization for deserializing non generic structures..*/
template<>
void				SerializationCore::DeserializeProperty< void* >				( IDeserializer* deser, rttr::property prop, const rttr::instance& object )
{
	if( deser->EnterObject( prop.get_name().to_string() ) )
	{
		TypeID propertyType = prop.get_type();
		auto deserObject = prop.get_value( object );

		DefaultDeserializeImpl( *deser, deserObject, propertyType );

		deser->Exit();	//	prop.get_name()
	}
	// Error handling ??
}


/**@brief Specjalizacja dla DirectX::XMFLOAT3.*/
template<>
void			SerializationCore::DeserializeProperty< DirectX::XMFLOAT3* >	( IDeserializer* deser, rttr::property prop, const rttr::instance& object )
{
	if( deser->EnterObject( prop.get_name().to_string() ) )
	{
		DirectX::XMFLOAT3 value;
		value.x = static_cast<float> ( deser->GetAttribute( "X", TypeDefaultValue< float >() ) );
		value.y = static_cast<float> ( deser->GetAttribute( "Y", TypeDefaultValue< float >() ) );
		value.z = static_cast<float> ( deser->GetAttribute( "Z", TypeDefaultValue< float >() ) );

		SetPropertyValue( prop, object, &value );

		deser->Exit();	// prop.get_name()
	}
	// Error handling ??
}

/**@brief Specjalizacja dla DirectX::XMFLOAT2.*/
template<>
void			SerializationCore::DeserializeProperty< DirectX::XMFLOAT2* >	( IDeserializer* deser, rttr::property prop, const rttr::instance& object )
{
	if( deser->EnterObject( prop.get_name().to_string() ) )
	{
		DirectX::XMFLOAT2 value;
		value.x = static_cast<float> ( deser->GetAttribute( "X", TypeDefaultValue< float >() ) );
		value.y = static_cast<float> ( deser->GetAttribute( "Y", TypeDefaultValue< float >() ) );

		SetPropertyValue( prop, object, &value );

		deser->Exit();	// prop.get_name()
	}
	// Error handling ??
}

/**@brief Specjalizacja dla DirectX::XMFLOAT4.*/
template<>
void			SerializationCore::DeserializeProperty< DirectX::XMFLOAT4* >	( IDeserializer* deser, rttr::property prop, const rttr::instance& object )
{
	if( deser->EnterObject( prop.get_name().to_string() ) )
	{
		DirectX::XMFLOAT4 value;
		value.x = static_cast<float> ( deser->GetAttribute( "X", TypeDefaultValue< float >() ) );
		value.y = static_cast<float> ( deser->GetAttribute( "Y", TypeDefaultValue< float >() ) );
		value.z = static_cast<float> ( deser->GetAttribute( "Z", TypeDefaultValue< float >() ) );
		value.w = static_cast<float> ( deser->GetAttribute( "W", TypeDefaultValue< float >() ) );

		SetPropertyValue( prop, object, &value );

		deser->Exit();	// prop.get_name()
	}
	// Error handling ??
}

/**@brief Specjalizacja dla std::wstring.*/
template<>
void			SerializationCore::DeserializeProperty< std::wstring >	( IDeserializer* deser, rttr::property prop, const rttr::instance& object )
{
	std::wstring str = GetPropertyValue< std::wstring >( prop, object );
	SetPropertyValue( prop, object, UTFToWstring( deser->GetAttribute( prop.get_name().to_string(), TypeDefaultValue< std::string >() ) ) );
}

// ================================ //
//
template<>
static void		SerializationCore::DeserializeProperty< char >			( IDeserializer* deser, rttr::property prop, const rttr::instance& object )
{
	auto str = deser->GetAttribute( prop.get_name().to_string(), std::string() );

	if( str.size() == 1 )
		SetPropertyValue( prop, object, str[ 0 ] );
	///@todo Error handling.
}

}	// sw
