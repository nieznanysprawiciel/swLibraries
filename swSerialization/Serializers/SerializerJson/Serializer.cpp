/**
@file Serializer.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#define RAPIDJSON_HAS_STDSTRING 1

#include "swSerialization/Interfaces/Serializer.h"
#include "ErrorCodes.h"

#include "swCommonLib/System/Dir.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include <fstream>
#include <stack>

using namespace sw;


/**@defgroup SerializerJSON JSON Serializer
@ingroup Serialization
@brief Implementation of JSON serialization.

Project SerializerJSON contains implementation of JSON serialization based on RapidJSON library.
http://rapidjson.org/md_doc_tutorial.html*/




struct SerializerImpl
{
	rapidjson::Document				root;
	std::stack< rapidjson::Value >	valuesStack;
};

namespace
{

// ================================ //
//
inline void				AddArrayAttribute			( SerializerImpl* impl, rapidjson::Value&& valueName, rapidjson::Value&& attribute )
{
	// This should be array.
	rapidjson::Value& currentObject = impl->valuesStack.top();
	assert( currentObject.IsArray() );

	// First element of array should be object storing array attribute.
	rapidjson::Value::ValueIterator firstElement = currentObject.Begin();
	assert( firstElement->IsObject() );

	firstElement->AddMember( std::move( valueName ), std::move( attribute ), impl->root.GetAllocator() );
}

// ================================ //
//
inline void				SetAttributeHelper			( SerializerImpl* impl, const std::string& name, rapidjson::Value& value )
{
	rapidjson::Value& currentObject = impl->valuesStack.top();	// Obiekt, do kt�rego przyczepiamy atrybut.
	rapidjson::Value valueName;
	valueName.SetString( name.c_str(), (rapidjson::SizeType)name.length(), impl->root.GetAllocator() );

	if( currentObject.IsObject() )
		currentObject.AddMember( std::move( valueName ), std::move( value ), impl->root.GetAllocator() );
	else
	{
		// Handle arrays.
		AddArrayAttribute( impl, std::move( valueName ), std::move( value ) );
	}
}

// ================================ //
//
inline void				WriteToStreamBuffer			( rapidjson::StringBuffer& buffer, rapidjson::Document& document, WritingMode mode )
{
	if( mode == WritingMode::Sparing )
	{
		rapidjson::Writer<rapidjson::StringBuffer> writer( buffer );
		document.Accept( writer );
	}
	else
	{
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer( buffer );
		document.Accept( writer );
	}
}

} // annonymous


/**@brief Konstruktor*/
ISerializer::ISerializer( ISerializationContextPtr serContext )
	: context( serContext )
{
	impl = new SerializerImpl;
	rapidjson::Value newObject( rapidjson::kObjectType );
	impl->valuesStack.push( std::move( newObject ) );
}

/**@brief Destruktor*/
ISerializer::~ISerializer()
{ delete impl; }


// ================================ //
//
ReturnResult            ISerializer::SaveFile         ( const std::string& fileName, WritingMode mode )
{
    // Ensure directory exists.
    filesystem::Dir::CreateDirectory( fileName );

    std::ofstream file;
    file.open( fileName );
    if( !file.fail() )
    {
        file << SaveString( mode );

        file.close();
        return Success::True;
    }
    return fmt::format( "Saving file [{}] failed. Error: {}", fileName, Convert::ErrnoToString( errno ) );
}

// ================================ //
//
std::string             ISerializer::SaveString       ( WritingMode mode )
{
    rapidjson::StringBuffer stringBuffer;

    while( impl->valuesStack.size() > 1 )
        this->Exit();

    rapidjson::Value& topValue = impl->valuesStack.top();
    rapidjson::Value& documentObject = impl->root.SetObject();
    documentObject = topValue.Move();

    if( mode == WritingMode::Sparing )
    {
        rapidjson::Writer< rapidjson::StringBuffer > writer( stringBuffer );
        impl->root.Accept( writer );
    }
    else
    {
        rapidjson::PrettyWriter< rapidjson::StringBuffer > writer( stringBuffer );
        impl->root.Accept( writer );
    }

    return stringBuffer.GetString();
}

/**@brief Creates object of provided name.

@param[in] name Object name.*/
void			ISerializer::EnterObject			( const std::string& name )
{
	rapidjson::Value newObject( rapidjson::kObjectType );

	// Nazwa jest potrzebna tylko, je�eli przyczepiamy si� do obiektu.
	// W przypadku tablic wszystkie obiekty s� bez nazwy, wi�c unikamy alokacji pami�ci i wrzucamy pustego stringa.
	rapidjson::Value newName( rapidjson::kStringType );
	if( impl->valuesStack.top().IsObject() )
		newName.SetString( name.c_str(), (rapidjson::SizeType)name.length(), impl->root.GetAllocator() );

	// Wrzucamy nazw� jako pierwsz�, a potem sam obiekt.
	impl->valuesStack.push( std::move( newName ) );
	impl->valuesStack.push( std::move( newObject ) );
}

/**@brief Koniec tworzenia obiektu.
EnterObject i ExitObject powinny by� stosowane parami.*/
void			ISerializer::Exit					()
{
	rapidjson::Value& objectValue = impl->valuesStack.top();		// Obiekt, kt�rego konstruowanie skonczyli�my.
	impl->valuesStack.pop();
	rapidjson::Value& objectName = impl->valuesStack.top();			// Nazwa obiektu.
	impl->valuesStack.pop();

	rapidjson::Value& newCurrentObject = impl->valuesStack.top();
	if( newCurrentObject.IsObject() )
		newCurrentObject.AddMember( std::move( objectName ), std::move( objectValue ), impl->root.GetAllocator() );
	else if( newCurrentObject.IsArray() )
		newCurrentObject.PushBack( std::move( objectValue ), impl->root.GetAllocator() );
}

/**@brief Tworzy tablic� o podanej nazwie.

@param[in] name Nazwa tablicy.*/
void			ISerializer::EnterArray				( const std::string& name )
{
	rapidjson::Value newArray( rapidjson::kArrayType );

	// Nazwa jest potrzebna tylko, je�eli przyczepiamy si� do obiektu.
	// W przypadku tablic wszystkie obiekty s� bez nazwy, wi�c unikamy alokacji pami�ci i wrzucamy pustego stringa.
	rapidjson::Value newName( rapidjson::kStringType );
	if( impl->valuesStack.top().IsObject() )
		newName.SetString( name.c_str(), (rapidjson::SizeType)name.length(), impl->root.GetAllocator() );

	// Add array info object to store array attributes.
	rapidjson::Value arrayInfoObject( rapidjson::kObjectType );
	newArray.PushBack( std::move( arrayInfoObject ), impl->root.GetAllocator() );

	// First goes name and then object.
	impl->valuesStack.push( std::move( newName ) );
	impl->valuesStack.push( std::move( newArray ) );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void			ISerializer::SetAttribute			( const std::string& name, const std::string& value )
{
	rapidjson::Value& currentObject = impl->valuesStack.top();	// Obiekt, do kt�rego przyczepiamy atrybut.
	rapidjson::Value newObject;
	rapidjson::Value valueName;
	valueName.SetString( name.c_str(), (rapidjson::SizeType)name.length(), impl->root.GetAllocator() );
	newObject.SetString( value.c_str(), (rapidjson::SizeType)value.length(), impl->root.GetAllocator() );

	if( currentObject.IsObject() )
		currentObject.AddMember( std::move( valueName ), std::move( newObject ), impl->root.GetAllocator() );
	else
		AddArrayAttribute( impl, std::move( valueName ), std::move( newObject ) );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void			ISerializer::SetAttribute			( const std::string& name, const char* value )
{
	rapidjson::Value& currentObject = impl->valuesStack.top();	// Obiekt, do kt�rego przyczepiamy atrybut.
	rapidjson::Value newObject;
	rapidjson::Value valueName;
	valueName.SetString( name.c_str(), (rapidjson::SizeType)name.length(), impl->root.GetAllocator() );
	newObject.SetString( value, (rapidjson::SizeType)strlen( value ), impl->root.GetAllocator() );

	if( currentObject.IsObject() )
		currentObject.AddMember( std::move( valueName ), std::move( newObject ), impl->root.GetAllocator() );
	else
		AddArrayAttribute( impl, std::move( valueName ), std::move( newObject ) );
}


/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void			ISerializer::SetAttribute			( const std::string& name, uint32 value )
{
	rapidjson::Value newObject;
	newObject.SetUint( value );
	SetAttributeHelper( impl, name, newObject );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void			ISerializer::SetAttribute			( const std::string& name, uint64 value )
{
	rapidjson::Value newObject;
	newObject.SetUint64( value );
	SetAttributeHelper( impl, name, newObject );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void			ISerializer::SetAttribute			( const std::string& name, int32 value )
{
	rapidjson::Value newObject;
	newObject.SetInt( value );
	SetAttributeHelper( impl, name, newObject );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void			ISerializer::SetAttribute			( const std::string& name, int64 value )
{
	rapidjson::Value newObject;
	newObject.SetInt64( value );
	SetAttributeHelper( impl, name, newObject );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void			ISerializer::SetAttribute			( const std::string& name, bool value )
{
	rapidjson::Value newObject;
	newObject.SetBool( value );
	SetAttributeHelper( impl, name, newObject );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void			ISerializer::SetAttribute			( const std::string& name, double value )
{
	rapidjson::Value newObject;
	newObject.SetDouble( value );
	SetAttributeHelper( impl, name, newObject );
}


