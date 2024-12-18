/**
@file Deserializer.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#define RAPIDJSON_HAS_STDSTRING 1

#include "swSerialization/Interfaces/Deserializer.h"

#include "swCommonLib/Common/fmt.h"
#include "swCommonLib/Common/Converters/Convert.h"


#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#ifdef _WIN32
	#define _CRT_SECURE_NO_DEPRECATE
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <fstream>
#include <sstream>
#include <stack>

#include "ErrorCodes.h"

using namespace sw;


// ================================ //
//
struct DeserializerImpl
{
	rapidjson::Document				root;
	std::stack< rapidjson::Value* >	valuesStack;
	std::string 					fileContent;
	ParsingMode						mode;

	DeserializerImpl() {}
};


// ================================ //
//
struct NameValue
{
	rapidjson::Value*		Name;
	rapidjson::Value*		Value;
};

// ================================ //
//
NameValue		PopTopNodes		( DeserializerImpl* impl )
{
	NameValue result;

	result.Value = impl->valuesStack.top();
	impl->valuesStack.pop();

	result.Name = impl->valuesStack.top();
	impl->valuesStack.pop();

	return result;
}

// ================================ //
//
void			RestoreTopNodes	( DeserializerImpl* impl, const NameValue& nameValue )
{
	impl->valuesStack.push( nameValue.Name );
	impl->valuesStack.push( nameValue.Value );
}


// ================================ //
//
IDeserializer::IDeserializer()
	:	context( nullptr )
{
	impl = new DeserializerImpl;
}


// ================================ //
//
IDeserializer::IDeserializer( ISerializationContextPtr serContext )
	: context( serContext )
{
	impl = new DeserializerImpl;
}

// ================================ //
//
IDeserializer::~IDeserializer()
{	
	delete impl;
}

//====================================================================================//
//			Wczytywanie i parsowanie	
//====================================================================================//

// ================================ //
//
ReturnResult            IDeserializer::LoadFromFile     ( const std::string& fileName )
{
    std::ifstream file( fileName );

    if( file.fail() )
        return fmt::format( "Loading file [{}] failed. Error: {}", fileName, Convert::ErrnoToString( errno ) );

    // Note: I would prefere filesystem::File::Load, but it doesn't report errors.
    std::stringstream buffer;
    buffer << file.rdbuf();

    auto content = buffer.str();

    file.close();

    return LoadFromString( std::move( content ) );
}

// ================================ //
//
ReturnResult            IDeserializer::LoadFromString   ( std::string content )
{
    impl->fileContent = std::move( content );
    impl->mode = ParsingMode::ParseInsitu;
    impl->root.ParseInsitu( impl->fileContent.data() );

    if( impl->root.HasParseError() )
    {
        rapidjson::ParseErrorCode code = impl->root.GetParseError();
        auto lineNum = impl->root.GetErrorOffset();

        return fmt::format( "Parsing failed. Error: {}, line: {}", GetStringFromCode( code ), lineNum );
    }

    impl->valuesStack.push( &impl->root );
    return Success::True;
}

//====================================================================================//
//			Iterowanie po drzewie	
//====================================================================================//


// ================================ //
//
const char*		IDeserializer::GetName			() const
{
	assert( impl->valuesStack.size() >= 2 );

	auto value = impl->valuesStack.top();	// Value
	impl->valuesStack.pop();

	auto name = impl->valuesStack.top();
	impl->valuesStack.pop();

	bool isArray = impl->valuesStack.top()->IsArray();

	impl->valuesStack.push( name );			// Restore name.
	impl->valuesStack.push( value );		// Restore value.

	// Objects in array don't have names.
	if( isArray )
		return "";

	return name->GetString();
}

/**@brief Wyszukuje obiekt o podanej nazwie i wchodzi w g��b drzewa.

@param[in] name Nazwa obiektu.
@return Zwraca false, je�eli obiekt o danej nazwie nie istnieje.*/
bool			IDeserializer::EnterObject		( const std::string& name ) const
{
	return EnterObject( name.c_str() );
}

/**@brief Wyszukuje obiekt o podanej nazwie i wchodzi w g��b drzewa.

@param[in] name Nazwa obiektu.
@return Zwraca false, je�eli obiekt o danej nazwie nie istnieje.*/
bool			IDeserializer::EnterObject		( const char* name ) const
{
	assert( !impl->valuesStack.empty() );
	auto value = impl->valuesStack.top();

	auto iterator = value->FindMember( name );
	if( iterator == value->MemberEnd() )
		return false;

	assert( iterator->value.IsObject() );

	impl->valuesStack.push( &iterator->name );
	impl->valuesStack.push( &iterator->value );
	return true;
}

/**@brief Wyszukuje tablic� o podanej nazwie i wchodzi w g��b drzewa.

@param[in] name Nazwa tablicy.
@return Zwraca false, je�eli tablica o danej nazwie nie istnieje.*/
bool			IDeserializer::EnterArray		( const std::string& name ) const
{
	return EnterArray( name.c_str() );
}

/**@brief Wyszukuje tablic� o podanej nazwie i wchodzi w g��b drzewa.

@param[in] name Nazwa tablicy.
@return Zwraca false, je�eli tablica o danej nazwie nie istnieje.*/
bool			IDeserializer::EnterArray		( const char* name ) const
{
	assert( !impl->valuesStack.empty() );
	auto value = impl->valuesStack.top();

	auto iterator = value->FindMember( name );
	if( iterator == value->MemberEnd() )
		return false;

	assert( iterator->value.IsArray() );

	impl->valuesStack.push( &iterator->name );
	impl->valuesStack.push( &iterator->value );
	return true;
}

/**@brief Wychodzi z tablicy albo obiektu, w kt�rym znaleziono
si� przy pomocy funkcji EnterObject lub EnterArray.*/
void			IDeserializer::Exit			() const
{
	assert( !impl->valuesStack.empty() );

	assert( impl->valuesStack.top()->IsArray() || impl->valuesStack.top()->IsObject() );
	impl->valuesStack.pop();		// Pop array or object.
	impl->valuesStack.pop();		// Pop object or array name. Note that objects in arrays don't have names, so here lies mock object.
}

//=========================================================//
//				
//=========================================================//

void			PushArrayObjectName					( DeserializerImpl* impl, rapidjson::Value* object )
{
	auto name = object->FindMember( "Name" );
	if( name != object->MemberEnd() )
		impl->valuesStack.push( &name->value );
	else
		impl->valuesStack.push( &name->value );	//@todo Wpisa� tu jak�� warto��, gdy nie ma nazwy jako atrybutu.
}


/**@brief Wchodzi do pierwszego elementu tablicy lub obiektu.

Je�eli w�ze�, w kt�rym jeste�my, nie ma �adnych dzieci, pozostajemy w nim
i stan serializatora nie zmienia si�.

@return Zwaca false, je�eli nie ma �adnego obiektu w tablicy (lub obiekcie).*/
bool			IDeserializer::FirstElement			() const
{
	auto value = impl->valuesStack.top();
	if( value->IsArray() && value->Size() > 1 )
	{
		rapidjson::Value::ValueIterator firstElement = value->Begin();
		firstElement++;		// First element is always Array attributes object, so we iterate to next element.

		PushArrayObjectName( impl, firstElement );
		impl->valuesStack.push( firstElement );
		return true;
	}
	else if( value->IsObject() )
	{
		auto firstElement = value->MemberBegin();
		while( firstElement != value->MemberEnd() )
		{
			// We enter only objects and arrays. Filter out attributes.
			if( firstElement->value.IsObject() || firstElement->value.IsArray() )
			{
				impl->valuesStack.push( &firstElement->name );
				impl->valuesStack.push( &firstElement->value );
				return true;
			}

			firstElement++;
		}
	}
	else
	{
		assert( false );
		return false;
	}

	return false;
}

/**@brief Przechodzi do nast�pnego elementu w tablicy lub w obiekcie.*/
bool			IDeserializer::NextElement			() const
{
	rapidjson::Value::ValueIterator value = impl->valuesStack.top();
	auto topNodes = PopTopNodes( impl );
	auto valueParent = impl->valuesStack.top();		// Parent

	if( valueParent->IsArray() )
	{
		++value;
		// Sprawdzamy czy nie dotarli�my do ko�ca - wersja dla tablic.
		if( value == valueParent->End() )
		{
			RestoreTopNodes( impl, topNodes );
			return false;
		}

		PushArrayObjectName( impl, value );
		impl->valuesStack.push( value );
		return true;
	}
	else if( valueParent->IsObject() )
	{
		// Sprawdzamy czy nie dotarli�my do ko�ca - wersja dla obiekt�w.
		rapidjson::Value::MemberIterator iter = valueParent->MemberBegin();
		while( iter != valueParent->MemberEnd() )
		{
			if( &iter->value == value )
				break;
			++iter;
		}

		if( iter == valueParent->MemberEnd() )
		{
			RestoreTopNodes( impl, topNodes );
			return false;
		}

		while( ++iter != valueParent->MemberEnd() )
		{
			// We enter only objects and arrays. Filter out attributes.
			if( iter->value.IsObject() || iter->value.IsArray() )
			{
				impl->valuesStack.push( &iter->name );
				impl->valuesStack.push( &iter->value );
				return true;
			}
		}
	}
	else
	{
		assert( !"Wrong rapidjson::Value type" );
		RestoreTopNodes( impl, topNodes );
		return false;
	}

	RestoreTopNodes( impl, topNodes );
	return false;
}

/**@brief Przechodzi do poprzedniego elementu w tablicy lub w obiekcie.*/
bool			IDeserializer::PrevElement			() const
{
	assert( impl->valuesStack.size() >= 3 );

	rapidjson::Value::ValueIterator value = impl->valuesStack.top();
	auto topNodes = PopTopNodes( impl );
	auto valueParent = impl->valuesStack.top();

	if( valueParent->IsArray() )
	{
		// Check if we reached begin of array.
		rapidjson::Value::ValueIterator arrayBegin = valueParent->Begin();
		arrayBegin++;		// First element is always Array attributes object, so we iterate to next element.

		if( value == arrayBegin )
		{
			RestoreTopNodes( impl, topNodes );
			return false;
		}

		--value;

		PushArrayObjectName( impl, value );
		impl->valuesStack.push( value );
		return true;
	}
	else if( valueParent->IsObject() )
	{
		// Check if we aren't on the beginning of members - version for objects.
		rapidjson::Value::MemberIterator iter = valueParent->MemberEnd();
		--iter;
		while( iter != valueParent->MemberBegin() )
		{
			if( &iter->value == value )
				break;
			--iter;
		}

		if( iter == valueParent->MemberBegin() )
		{
			RestoreTopNodes( impl, topNodes );
			return false;
		}

		--iter;
		do
		{
			// We enter only objects and arrays. Filter out attributes.
			if( iter->value.IsObject() || iter->value.IsArray() )
			{
				impl->valuesStack.push( &iter->name );
				impl->valuesStack.push( &iter->value );
				return true;
			}

			--iter;

		} while( iter != valueParent->MemberBegin() );
	}
	else
	{
		assert( !"Wrong rapidjson::Value type" );
		RestoreTopNodes( impl, topNodes );
		return false;
	}

	RestoreTopNodes( impl, topNodes );
	return false;
}

/**@brief Wchodzi do ostatniego elementu tablicy lub obiektu.

Je�eli w�ze�, w kt�rym jeste�my, nie ma �adnych dzieci, pozostajemy w nim
i stan serializatora nie zmienia si�.

@return Zwaca false, je�eli nie ma �adnego obiektu w tablicy (lub obiekcie).*/
bool			IDeserializer::LastElement			() const
{
	auto value = impl->valuesStack.top();
	if( value->IsArray() && value->Size() > 1 )
	{
		rapidjson::Value::ValueIterator lastElement = value->End();
		lastElement--;

		if( lastElement == value->Begin() )
			return false;

		PushArrayObjectName( impl, lastElement );
		impl->valuesStack.push( lastElement );
		return true;
	}
	else if( value->IsObject() )
	{
		auto lastElement = value->MemberEnd();
		lastElement--;

		if( lastElement == value->MemberBegin() )
			return false;

		impl->valuesStack.push( &lastElement->name );
		impl->valuesStack.push( &lastElement->value );
	}
	else
	{
		assert( false );
		return false;
	}

	return true;
}

//=========================================================//
//			GetAttribute funkcje pomocnicze
//=========================================================//

namespace
{

template< typename ElementType >
inline bool Is					( rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{
	assert( false );
	return false;
}

template<>
inline bool Is< const char* >	(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.IsString();	}

template<>
inline bool Is< uint32 >	(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.IsUint();	}

template<>
inline bool Is< int32 >		(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.IsInt();	}

template<>
inline bool Is< uint64 >	(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.IsUint64();	}

template<>
inline bool Is< int64 >		(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.IsInt64();	}

template<>
inline bool Is< bool >		(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.IsBool();	}

template<>
inline bool Is< double >	(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.IsDouble();	}

//====
//====
template< typename ElementType >
inline ElementType Get					( rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{
	assert( false );
	return false;
}

template<>
inline const char* Get< const char* >	(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.GetString();	}

template<>
inline uint32 Get< uint32 >	(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.GetUint();	}

template<>
inline int32 Get< int32 >		(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.GetInt();	}

template<>
inline uint64 Get< uint64 >	(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.GetUint64();	}

template<>
inline int64 Get< int64 >		(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.GetInt64();	}

template<>
inline bool Get< bool >		(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.GetBool();	}

template<>
inline double Get< double >	(  rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >& iterator )
{	return iterator->value.GetDouble();	}



template<typename Type>
inline Type		GetAttribTemplate( DeserializerImpl* impl, const char* name, Type& defaultValue )
{
	rapidjson::Value* currentObject = impl->valuesStack.top();	// Obiekt, w kt�rym szukamy atrybut�w

	if( currentObject->IsObject() )
	{
		auto iterator = currentObject->FindMember( name );
		if( iterator == currentObject->MemberEnd() || !Is< Type >( iterator ) )
			return defaultValue;

		return Get< Type >( iterator );
	}
	else if( currentObject->IsArray() )
	{
		///@todo Add error handling.
		assert( currentObject->Size() >= 1 );

		rapidjson::Value::ValueIterator firstElement = currentObject->Begin();

		auto iterator = firstElement->FindMember( name );
		if( iterator == firstElement->MemberEnd() || !Is< Type >( iterator ) )
			return defaultValue;

		return Get< Type >( iterator );
	}

	return defaultValue;
}

}	// anonymous


//=========================================================//
//			GetAttribute string
//=========================================================//


/**@brief Pobiera par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
std::string			IDeserializer::GetAttribute		( const std::string& name, std::string& defaultValue ) const
{
	rapidjson::Value* currentObject = impl->valuesStack.top();	// Obiekt, w kt�rym szukamy atrybut�w

	auto iterator = currentObject->FindMember( name );
	if( iterator == currentObject->MemberEnd() || !iterator->value.IsString() )
		return defaultValue;

	return iterator->value.GetString();
}

/**@brief Zwraca atrybut o podanej nazwie.

@attention Zwracany string przestanie istnie� w momencie usuni�cia serializatora lub zmiany zawarto�ci.

@param[in] name Nazwa atrybutu
@param[in] defaultValue Je�eli element o podanej nazwie nie istnieje, zostanie zwr�cona warto�� domy�lna.*/
const char*			IDeserializer::GetAttribute		( const std::string& name, const char* defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}


/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
uint32				IDeserializer::GetAttribute		( const std::string& name, uint32 defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
uint64				IDeserializer::GetAttribute		( const std::string& name, uint64 defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
int32				IDeserializer::GetAttribute		( const std::string& name, int32 defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
int64				IDeserializer::GetAttribute		( const std::string& name, int64 defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
bool				IDeserializer::GetAttribute		( const std::string& name, bool defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
double				IDeserializer::GetAttribute		( const std::string& name, double defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}


//=========================================================//
//			GetAttribute const char
//=========================================================//

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
std::string		IDeserializer::GetAttribute		( const char* name, std::string& defaultValue ) const
{
	rapidjson::Value* currentObject = impl->valuesStack.top();	// Obiekt, w kt�rym szukamy atrybut�w

	auto iterator = currentObject->FindMember( name );
	if( iterator == currentObject->MemberEnd() || !iterator->value.IsString() )
		return defaultValue;

	return iterator->value.GetString();
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
const char*		IDeserializer::GetAttribute		( const char* name, const char* defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
uint32			IDeserializer::GetAttribute		( const char* name, uint32 defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
uint64			IDeserializer::GetAttribute		( const char* name, uint64 defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
int32			IDeserializer::GetAttribute		( const char* name, int32 defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
int64			IDeserializer::GetAttribute		( const char* name, int64 defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
bool			IDeserializer::GetAttribute		( const char* name, bool defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Warto��, jaka zostanie wpisana do podanej zmiennej.*/
double			IDeserializer::GetAttribute		( const char* name, double defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

//====================================================================================//
//			Error handling
//====================================================================================//

/**@brief Returns parsing error if it occured.

Aby si� dowiedzie� czy parsowanie powiod�o si�, sprawd� warto�� zwracan� przez
funkcje @ref LoadFromString lub @ref LoadFromFile.*/
std::string		IDeserializer::GetError			() const
{
	rapidjson::ParseErrorCode code = impl->root.GetParseError();
	auto lineNum = impl->root.GetErrorOffset();
	
	std::string errorMessage = "Error: " + std::string( GetStringFromCode( code ) ) + " Offset: " + std::to_string( lineNum );
	return std::move( errorMessage );
}


// ================================ //
//
bool								IsInsideArray			( DeserializerImpl* impl )
{
	auto value = impl->valuesStack.top();	// Value
	impl->valuesStack.pop();

	auto name = impl->valuesStack.top();
	impl->valuesStack.pop();

	bool isArray = impl->valuesStack.top()->IsArray();

	impl->valuesStack.push( name );			// Restore name.
	impl->valuesStack.push( value );		// Restore value.

	return isArray;
}

// ================================ //
//
const char*							FindArrayBegin			( DeserializerImpl* impl )
{
	// This function doesn't support nested arrays.
	auto objectValue = impl->valuesStack.top();	// Value
	impl->valuesStack.pop();

	auto objectName = impl->valuesStack.top();
	impl->valuesStack.pop();

	auto arrayValue = impl->valuesStack.top();
	impl->valuesStack.pop();

	assert( arrayValue->IsArray() );

	auto arrayName = impl->valuesStack.top();

	impl->valuesStack.push( arrayValue );			// Restore array name.
	impl->valuesStack.push( objectName );			// Restore object name.
	impl->valuesStack.push( objectValue );			// Restore object value.
	
	return arrayName->GetString();
}

// ================================ //
//
Size								FindIndexInArray		( DeserializerImpl* impl )
{
	auto objectValue = impl->valuesStack.top();	// Value
	impl->valuesStack.pop();

	auto objectName = impl->valuesStack.top();
	impl->valuesStack.pop();

	auto arrayValue = impl->valuesStack.top();

	rapidjson::Value::ValueIterator element = arrayValue->Begin();

	Size arrayIdx = 0;
	while( element != objectValue && element != arrayValue->End() )
	{
		element++;
		arrayIdx++;
	}

	// Restore previous state.
	impl->valuesStack.push( objectName );			// Restore object name.
	impl->valuesStack.push( objectValue );			// Restore object value.

	return arrayIdx;
}


// ================================ //
//
sw::FilePosition					ComputeJsonPosition     ( const char* fileBegin, const char* nodeFirstChar )
{
    sw::FilePosition pos;
    pos.Line = 1;
    pos.CharPosition = 0;

    const char* jsonPosition = fileBegin;
    const char* processedLineBegin = jsonPosition;

    while( jsonPosition < nodeFirstChar )
    {
        if( *jsonPosition == '\n' )
        {
            pos.Line++;
            processedLineBegin = jsonPosition + 1;
        }

        jsonPosition++;
    }

    // Note: numerate position from 1.
    pos.CharPosition = nodeFirstChar - processedLineBegin + 1;

    return pos;
}

// ================================ //
//
sw::FilePosition					ComputeJsonPosition		( const char* arrayBegin, Size arrayIdx )
{
    sw::FilePosition pos;
    pos.Line = 0;
    pos.CharPosition = 0;

    const char* jsonPosition = arrayBegin;
    const char* processedLineBegin = jsonPosition;

	// Find opening bracket of current array.
	while( *jsonPosition != '[' )
		jsonPosition++;

	int32 nesting = 1;		// Nesting 1 means that we are still in processed array.
	uint32 currentArrayIdx = 0;

    while( nesting >= 1  )
    {
		if( *jsonPosition == '\n' )
		{
			pos.Line++;
			processedLineBegin = jsonPosition + 1;
		}
		else if( *jsonPosition == '{' )
		{
			nesting++;

			// Check if we found opening of object under expected array index.
			if( nesting == 2 )
			{
				if( currentArrayIdx == arrayIdx )
				{
					pos.CharPosition = jsonPosition - processedLineBegin + 1;
					return pos;
				}

				currentArrayIdx++;
			}
		}
		else if( *jsonPosition == '}' )
			nesting--;

        jsonPosition++;
    }

	// If we are here, that means that we haven't found object under arrayIdx.
	// We can return begin of array.
	return pos;
}

// ================================ //
//
sw::FilePosition					IDeserializer::CurrentLineNumber      () const
{
	// Note: this will only work in insitu parsing mode.
	///@todo Think how to do this in AllocStrings mode.
	if( impl->mode == ParsingMode::ParseInsitu )
	{
		if( IsInsideArray( impl ) )
		{
			const char* fileFirstChar = impl->fileContent.data();
			const char* arrayFirstChar = FindArrayBegin( impl );

			// Compute number of lines to the beginning of array.
			auto arrayPosition = ComputeJsonPosition( fileFirstChar, arrayFirstChar );

			// Compute number of lines to object in array.
			Size objectArrayIdx = FindIndexInArray( impl );
			auto posInArray = ComputeJsonPosition( arrayFirstChar, objectArrayIdx );

			posInArray.Line += arrayPosition.Line;
			return posInArray;
		}
		else
		{
			const char* fileFirstChar = impl->fileContent.data();
			const char* nodeFirstChar = GetName();

			return ComputeJsonPosition( fileFirstChar, nodeFirstChar );
		}
	}
	else
	{
		sw::FilePosition pos;
		pos.Line = 0;
		pos.CharPosition = 0;

		return pos;
	}
}


