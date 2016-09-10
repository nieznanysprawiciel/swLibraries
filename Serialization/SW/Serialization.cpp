#include "EngineCore/stdafx.h"
#include "Serialization.h"

#include <codecvt>



/**@brief Zwraca wektor propertiesów dla danego typu.

Propertisy s¹ pobierane z contextu, je¿eli ju¿ tam istniej¹. Je¿eli nie to s¹ rejestrowane.
W ten sposób unikamy filtrowania w³aœciwoœci przy ka¿dym obiekcie.*/
std::vector< rttr::property >&	Serialization::GetTypeFilteredProperties( rttr::type objType, EngineSerializationContext* context )
{
	objType = objType.get_raw_type();

	auto iter = context->TypeProperties.find( objType );
	if( iter == context->TypeProperties.end() )
	{
		auto result = context->TypeProperties.insert( std::make_pair( objType, std::vector< rttr::property >() ) );
		auto& propVec = result.first->second;

		MetaDataType saveFlag;
		if( context->SaveWholeMap )
			saveFlag = MetaDataType::Serialize;
		else
			saveFlag = MetaDataType::AllowInSaveFile;


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

/**@brief Sprawdza czy w³aœciwoœæ powinna zostaæ zapisana.

Domyœlnie:
Je¿eli nie zarejestrowano metadanych, to domyœlnie w³aœciwoœæ jest serializowana.*/
bool Serialization::ShouldSave( rttr::property& prop, MetaDataType saveFlag )
{
	auto saveFlagMeta = prop.get_metadata( saveFlag );
	if( !saveFlagMeta.is_valid() )
		return true;

	assert( saveFlagMeta.is_type< bool >() );

	return saveFlagMeta.get_value< bool >();
}

/**@brief Domyœlny tryb serialziacji obiektów.

Serializowane s¹ wszystkie w³aœciwoœci, które nie zosta³y w metadanych oznaczone
jako nieserializowalne.*/
void	Serialization::DefaultSerialize	( ISerializer* ser, const EngineObject* object )
{
	DefaultSerializeImpl( ser, object, object->GetType() );
}



void	Serialization::DefaultSerializeImpl( ISerializer* ser, const rttr::instance& object, rttr::type dynamicType  )
{
	auto objectType = dynamicType;
	auto& properties = GetTypeFilteredProperties( objectType, ser->GetContext< EngineSerializationContext >() );

	ser->EnterObject( objectType.get_name() );

	SerializePropertiesVec( ser, object, properties );

	ser->Exit();	// objectType.get_name()
}

void	Serialization::SerializePropertiesVec	( ISerializer* ser, const rttr::instance& object, std::vector< rttr::property >& properties )
{
	for( auto& property : properties )
	{
		auto propertyType = property.get_type();
		
		bool serialized =	SerializeBasicTypes( ser, object, property ) ||
							SerializeVectorTypes( ser, object, property ) ||
							SerializeStringTypes( ser, object, property ) ||
							SerializeEnumTypes( ser, object, property ) ||
							SerializeArrayTypes( ser, object, property );

		if( !serialized && propertyType.is_derived_from< EngineObject >() )
			SerializeProperty< EngineObject* >( ser, property, object );
		else if( !serialized && propertyType.is_pointer() )
			SerializeProperty< void* >( ser, property, object );
	}
}

/**@brief Domyœlny tryb deserialziacji obiektów.

Deserializowane s¹ wszystkie typy podstawowe.*/
void	Serialization::DefaultDeserialize	( IDeserializer* deser, EngineObject* object )
{
	auto objectType = object->GetType();
	auto& properties = Serialization::GetTypeFilteredProperties( objectType, deser->GetContext< EngineSerializationContext >() );

	for( auto& property : properties )
	{
		auto propertyType = property.get_type();
		
		DeserializeBasicTypes( deser, object, property ) ||
		DeserializeVectorTypes( deser, object, property ) ||
		DeserializeStringTypes( deser, object, property );
	}
}

/**@brief Serializuje podstawowe typy.

Funkcja sprawdza typ w³asciwoœci i serializuje go tylko je¿eli jest jednym z obs³ugiwanych
przez ni¹ typów. W przeciwnym razie nie robi nic.

@return Funkcja zwraca true, je¿eli uda³o jej siê obs³u¿yæ podany typ.*/
bool Serialization::SerializeBasicTypes( ISerializer* ser, const rttr::instance& object, rttr::property& prop )
{
	auto propertyType = prop.get_type();

	if( !propertyType.is_arithmetic() )
		return false;
		
	if( propertyType == rttr::type::get< float >() )
		SerializeProperty< float >( ser, prop, object );
	else if( propertyType == rttr::type::get< bool >() )
		SerializeProperty< bool >( ser, prop, object );
	else if( propertyType == rttr::type::get< int32 >() )
		SerializeProperty< int32 >( ser, prop, object );
	else if( propertyType == rttr::type::get< uint32 >() )
		SerializeProperty< uint32 >( ser, prop, object );
	else if( propertyType == rttr::type::get< int16 >() )
		SerializeProperty< int16 >( ser, prop, object );
	else if( propertyType == rttr::type::get< uint16 >() )
		SerializeProperty< uint16 >( ser, prop, object );
	else if( propertyType == rttr::type::get< int8 >() )
		SerializeProperty< int8 >( ser, prop, object );
	else if( propertyType == rttr::type::get< int64 >() )
		SerializeProperty< int64 >( ser, prop, object );
	else if( propertyType == rttr::type::get< uint64 >() )
		SerializeProperty< uint64 >( ser, prop, object );
	else if( propertyType == rttr::type::get< double >() )
		SerializeProperty< double >( ser, prop, object );
	else
		return false;

	return true;
}

/**@brief Serializuje typy DirectXMath.*/
bool Serialization::SerializeVectorTypes( ISerializer* ser, const rttr::instance& object, rttr::property& prop )
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

bool	Serialization::SerializeStringTypes( ISerializer* ser, const rttr::instance& object, rttr::property& prop )
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

bool	Serialization::SerializeEnumTypes( ISerializer* ser, const rttr::instance& object, rttr::property& prop )
{
	auto propertyType = prop.get_type();

	if( !propertyType.is_enumeration() )
		return false;
	
	assert( propertyType.is_valid() );		/// Type haven't been registered.
	assert( propertyType.is_enumeration() );
	
	rttr::enumeration enumVal = propertyType.get_enumeration();

	ser->SetAttribute( prop.get_name(), enumVal.value_to_name( prop.get_value( object ) ) );

	return true;
}

/**@brief Serializes static or dynamic array.

Only one dimensional arrays are supported. If this condition is not met, function returns true in Release mode
and asserts in Debug mode. In both cases nothing will be serialized.*/
bool	Serialization::SerializeArrayTypes		( ISerializer* ser, const rttr::instance& object, rttr::property& prop )
{
	TypeID propertyType = prop.get_type();
	if( !propertyType.is_array() )
		return false;

	auto arrayVariant = prop.get_value( object );
	auto arrayView = arrayVariant.create_array_view();
	
	assert( arrayView.is_valid() );
	assert( arrayView.get_rank() == 1 );
	if( arrayView.get_rank() != 1 )
		return true;

	TypeID arrayElementType = arrayView.get_rank_type( 1 );
	assert( arrayElementType.is_class() || arrayElementType.get_raw_type().is_class() );
	if( !arrayElementType.is_class() && !arrayElementType.get_raw_type().is_class() )
		return true;

	ser->EnterArray( prop.get_name() );
	
	if( arrayView.is_dynamic() )
		ser->SetAttribute( "ArraySize", arrayView.get_size() );

	for( int i = 0; i < arrayView.get_size(); ++i )
	{
		auto element = arrayView.get_value_as_ptr( i );

		// Process generic objects. We must get real object type.
		if( arrayElementType.is_pointer() )
		{
			element = arrayView.get_value( i );
			
			EngineObject* engineObject = element.get_value< EngineObject* >();
			engineObject->Serialize( ser );
		}
		else
		{
			// Non generic objects use default serialization.
			DefaultSerializeImpl( ser, element, arrayElementType );
		}
	}

	ser->Exit();

	return false;
}

/**@brief Deserializuje podstawowe typy.

Funkcja sprawdza typ w³asciwoœci i deserializuje go tylko je¿eli jest jednym z obs³ugiwanych
przez ni¹ typów. W przeciwnym razie nie robi nic.

@return Funkcja zwraca true, je¿eli uda³o jej siê obs³u¿yæ podany typ.*/
bool Serialization::DeserializeBasicTypes( IDeserializer* deser, const EngineObject* object, rttr::property& prop )
{
	auto propertyType = prop.get_type();
		
	if( propertyType == rttr::type::get< float >() )
		Serialization::DeserializeProperty< float >( deser, prop, object );
	else if( propertyType == rttr::type::get< double >() )
		Serialization::DeserializeProperty< double >( deser, prop, object );
	else if( propertyType == rttr::type::get< int >() )
		Serialization::DeserializeProperty< int >( deser, prop, object );
	else if( propertyType == rttr::type::get< bool >() )
		Serialization::DeserializeProperty< bool >( deser, prop, object );
	else
		return false;

	return true;
}

/**@brief Deserializuje typy DirectXMath.*/
bool Serialization::DeserializeVectorTypes( IDeserializer* deser, const EngineObject* object, rttr::property& prop )
{
	auto propertyType = prop.get_type();

	if( propertyType == rttr::type::get< DirectX::XMFLOAT2* >() )
		Serialization::DeserializeProperty< DirectX::XMFLOAT2* >( deser, prop, object );
	else if( propertyType == rttr::type::get< DirectX::XMFLOAT3* >() )
		Serialization::DeserializeProperty< DirectX::XMFLOAT3* >( deser, prop, object );
	else if( propertyType == rttr::type::get< DirectX::XMFLOAT4* >() )
		Serialization::DeserializeProperty< DirectX::XMFLOAT4* >( deser, prop, object );
	else
		return false;

	return true;
}

/**@brief Deserializuje std::string i std::wstring.*/
bool Serialization::DeserializeStringTypes( IDeserializer* deser, const EngineObject* object, rttr::property& prop )
{
	auto propertyType = prop.get_type();

	if( propertyType == rttr::type::get< std::string >() )
		Serialization::DeserializeProperty< std::string >( deser, prop, object );
	else if( propertyType == rttr::type::get< std::wstring >() )
		Serialization::DeserializeProperty< std::wstring >( deser, prop, object );
	else
		return false;

	return true;
}


std::string Serialization::WstringToUTF( const std::wstring & str )
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(str);
}

std::wstring Serialization::UTFToWstring( const std::string & str )
{
	std::wstring_convert< std::codecvt_utf8< wchar_t > > myconv;
	return myconv.from_bytes( str );
}

//====================================================================================//
//				SerializeProperty template specialization
//====================================================================================//

template	void	Serialization::SerializeProperty< unsigned int >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	Serialization::SerializeProperty< float >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	Serialization::SerializeProperty< double >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	Serialization::SerializeProperty< int >		( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	Serialization::SerializeProperty< bool >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	Serialization::SerializeProperty< int16 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	Serialization::SerializeProperty< uint16 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	Serialization::SerializeProperty< int32 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	Serialization::SerializeProperty< uint32 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	Serialization::SerializeProperty< int64 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );
template	void	Serialization::SerializeProperty< uint64 >	( ISerializer* ser, rttr::property prop, const rttr::instance& object );

/**@brief Template specialization for classes derived from @ref EngineObject.

Function serializes property name as first. Then EngineObject::Serialize method is invoked.*/
template<>
void			Serialization::SerializeProperty< EngineObject* >( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	EngineObject* engineObj = GetPropertyValue< EngineObject* >( prop, object );
	if( engineObj )
	{
		ser->EnterObject( prop.get_name() );
		engineObj->Serialize( ser );
		ser->Exit();	//	prop.get_name()
	}
}

/**@brief Specjalizacja dla wszystkich obiektów, które nie dziedzicz¹ po EngineObject.

Musz¹ to byæ struktury bez hierarchii dziedziczenia, poniewa¿ nie mo¿na ustaliæ ich dynamicznego typu.*/
template<>
void			Serialization::SerializeProperty< void* >( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	void* engineObj = GetPropertyValue< void* >( prop, object );
	if( engineObj )
	{
		ser->EnterObject( prop.get_name() );
		
		rttr::variant objVariant( engineObj );
		TypeID realType = prop.get_type();
		objVariant.unsafe_convert_void( realType );

		auto& properties = GetTypeFilteredProperties( realType, ser->GetContext< EngineSerializationContext >() );

		SerializePropertiesVec( ser, objVariant, properties );

		ser->Exit();	//	prop.get_name()
	}
}

/**@brief Specjalizacja dla DirectX::XMFLOAT3.*/
template<>
void			Serialization::SerializeProperty< DirectX::XMFLOAT3* >	( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	DirectX::XMFLOAT3* xmFloat = GetPropertyValue< DirectX::XMFLOAT3* >( prop, object );
	ser->EnterObject( prop.get_name() );

	ser->SetAttribute( "X", xmFloat->x );
	ser->SetAttribute( "Y", xmFloat->y );
	ser->SetAttribute( "Z", xmFloat->z );

	ser->Exit();	// prop.get_name()
}

/**@brief Specjalizacja dla DirectX::XMFLOAT2.*/
template<>
void			Serialization::SerializeProperty< DirectX::XMFLOAT2* >	( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	DirectX::XMFLOAT2* xmFloat = GetPropertyValue< DirectX::XMFLOAT2* >( prop, object );
	ser->EnterObject( prop.get_name() );

	ser->SetAttribute( "X", xmFloat->x );
	ser->SetAttribute( "Y", xmFloat->y );

	ser->Exit();	// prop.get_name()
}

/**@brief Specjalizacja dla DirectX::XMFLOAT4.*/
template<>
void			Serialization::SerializeProperty< DirectX::XMFLOAT4* >	( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	DirectX::XMFLOAT4* xmFloat = GetPropertyValue< DirectX::XMFLOAT4* >( prop, object );
	ser->EnterObject( prop.get_name() );

	ser->SetAttribute( "X", xmFloat->x );
	ser->SetAttribute( "Y", xmFloat->y );
	ser->SetAttribute( "Z", xmFloat->z );
	ser->SetAttribute( "W", xmFloat->w );

	ser->Exit();	// prop.get_name()
}

/**@brief Specjalizacja dla std::wstring.*/
template<>
void			Serialization::SerializeProperty< std::wstring >	( ISerializer* ser, rttr::property prop, const rttr::instance& object )
{
	std::wstring str = GetPropertyValue< std::wstring >( prop, object );
	ser->SetAttribute( prop.get_name(), WstringToUTF( str ) );
}

//====================================================================================//
//				DeserializeProperty template specialization
//====================================================================================//

template	void	Serialization::DeserializeProperty< unsigned int >	( IDeserializer* deser, rttr::property prop, const EngineObject* object );
template	void	Serialization::DeserializeProperty< float >			( IDeserializer* deser, rttr::property prop, const EngineObject* object );
template	void	Serialization::DeserializeProperty< double >		( IDeserializer* deser, rttr::property prop, const EngineObject* object );
template	void	Serialization::DeserializeProperty< int >			( IDeserializer* deser, rttr::property prop, const EngineObject* object );
template	void	Serialization::DeserializeProperty< bool >			( IDeserializer* deser, rttr::property prop, const EngineObject* object );
template	void	Serialization::DeserializeProperty< int16 >			( IDeserializer* deser, rttr::property prop, const EngineObject* object );
template	void	Serialization::DeserializeProperty< uint16 >		( IDeserializer* deser, rttr::property prop, const EngineObject* object );
template	void	Serialization::DeserializeProperty< int32 >			( IDeserializer* deser, rttr::property prop, const EngineObject* object );
template	void	Serialization::DeserializeProperty< uint32 >		( IDeserializer* deser, rttr::property prop, const EngineObject* object );
template	void	Serialization::DeserializeProperty< int64 >			( IDeserializer* deser, rttr::property prop, const EngineObject* object );
template	void	Serialization::DeserializeProperty< uint64 >		( IDeserializer* deser, rttr::property prop, const EngineObject* object );


/**@brief Specjalizacja dla DirectX::XMFLOAT3.*/
template<>
void			Serialization::DeserializeProperty< DirectX::XMFLOAT3* >	( IDeserializer* deser, rttr::property prop, const EngineObject* object )
{
	deser->EnterObject( prop.get_name() );

	DirectX::XMFLOAT3 value;
	value.x = static_cast< float > ( deser->GetAttribute( "X", TypeDefaultValue< float >() ) );
	value.y = static_cast< float > ( deser->GetAttribute( "Y", TypeDefaultValue< float >() ) );
	value.z = static_cast< float > ( deser->GetAttribute( "Z", TypeDefaultValue< float >() ) );

	SetPropertyValue( prop, object, &value );

	deser->Exit();	// prop.get_name()
}

/**@brief Specjalizacja dla DirectX::XMFLOAT2.*/
template<>
void			Serialization::DeserializeProperty< DirectX::XMFLOAT2* >	( IDeserializer* deser, rttr::property prop, const EngineObject* object )
{
	deser->EnterObject( prop.get_name() );

	DirectX::XMFLOAT2 value;
	value.x = static_cast< float > ( deser->GetAttribute( "X", TypeDefaultValue< float >() ) );
	value.y = static_cast< float > ( deser->GetAttribute( "Y", TypeDefaultValue< float >() ) );

	SetPropertyValue( prop, object, &value );

	deser->Exit();	// prop.get_name()
}

/**@brief Specjalizacja dla DirectX::XMFLOAT4.*/
template<>
void			Serialization::DeserializeProperty< DirectX::XMFLOAT4* >	( IDeserializer* deser, rttr::property prop, const EngineObject* object )
{
	deser->EnterObject( prop.get_name() );

	DirectX::XMFLOAT4 value;
	value.x = static_cast< float > ( deser->GetAttribute( "X", TypeDefaultValue< float >() ) );
	value.y = static_cast< float > ( deser->GetAttribute( "Y", TypeDefaultValue< float >() ) );
	value.z = static_cast< float > ( deser->GetAttribute( "Z", TypeDefaultValue< float >() ) );
	value.w = static_cast< float > ( deser->GetAttribute( "W", TypeDefaultValue< float >() ) );

	SetPropertyValue( prop, object, &value );

	deser->Exit();	// prop.get_name()
}

/**@brief Specjalizacja dla std::wstring.*/
template<>
void			Serialization::DeserializeProperty< std::wstring >	( IDeserializer* deser, rttr::property prop, const EngineObject* object )
{
	std::wstring str = GetPropertyValue< std::wstring >( prop, object );
	SetPropertyValue( prop, object, UTFToWstring( deser->GetAttribute( prop.get_name(), TypeDefaultValue< std::string >() ) ) );
}
