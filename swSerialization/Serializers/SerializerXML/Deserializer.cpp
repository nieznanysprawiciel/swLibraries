/**
@file Deserializer.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swSerialization/Interfaces/Deserializer.h"
#include "swSerialization/External/RapidXML/rapidxml.hpp"

#include "swCommonLib/Common/fmt.h"
#include "swCommonLib/Common/Converters/Convert.h"

#include <fstream>
#include <sstream>
#include <stack>
#include <stdlib.h>


using namespace sw;


// ================================ //
//
struct DeserializerImpl
{
	rapidxml::xml_document<>				root;
	std::stack< rapidxml::xml_node<>* >		valuesStack;
    std::string 							fileContent;
	std::string								errorString;

	DeserializerImpl()  {}
};

sw::FilePosition					ComputeXmlPosition(const char* fileBegin, const char* nodeFirstChar);


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
//			Loading and parsing	
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
    impl->valuesStack.push( &impl->root );

    try
    {
        // This line will modify m_content. XML tree will reference
        // strings in m_content.
        impl->root.parse< rapidxml::parse_default >( impl->fileContent.data() );
    }
    catch( const rapidxml::parse_error & e )
    {
        auto position = ComputeXmlPosition(impl->fileContent.data(), e.where< char >());
        return fmt::format( "Parsing failed. Error: {}, line: {} at position: {}", e.what(), position.Line, position.CharPosition );
    }
    catch( const std::exception & e )
    {
        return fmt::format( "Parsing failed. Error: {}.", e.what() );
    }
    catch( ... )
    {
        return fmt::format( "Parsing failed. Unknown error." );
    }

    return Success::True;
}

//====================================================================================//
//			Iterating Tree	
//====================================================================================//

/**@brief Returns the name of the node in which the deserializer is located.*/
const char*		IDeserializer::GetName			() const
{
	return impl->valuesStack.top()->name();
}


/**@brief Searches for an object with the given name and enters the tree.

@param[in] name Object name.
@return Returns false if an object with the given name does not exist.*/
bool			IDeserializer::EnterObject		( const std::string& name ) const
{
	return EnterObject( name.c_str() );
}

/**@brief Searches for an object with the given name and enters the tree.

@param[in] name Object name.
@return Returns false if an object with the given name does not exist.*/
bool			IDeserializer::EnterObject		( const char* name ) const
{
	assert( !impl->valuesStack.empty() );
	auto value = impl->valuesStack.top();

	auto enterNode = value->first_node( name );
	if( enterNode == nullptr )
		return false;

	//assert( enterNode->type() == rapidxml::node_type:: );

	impl->valuesStack.push( enterNode );
	return true;
}

/**@brief Wyszukuje tablicê o podanej nazwie i wchodzi w g³¹b drzewa.

@param[in] name Nazwa tablicy.
@return Zwraca false, je¿eli tablica o danej nazwie nie istnieje.*/
bool			IDeserializer::EnterArray		( const std::string& name ) const
{
	return EnterArray( name.c_str() );
}

/**@brief Wyszukuje tablicê o podanej nazwie i wchodzi w g³¹b drzewa.

@param[in] name Nazwa tablicy.
@return Zwraca false, je¿eli tablica o danej nazwie nie istnieje.*/
bool			IDeserializer::EnterArray		( const char* name ) const
{
	assert( !impl->valuesStack.empty() );
	auto value = impl->valuesStack.top();

	auto enterNode = value->first_node( name );
	if( enterNode == nullptr )
		return false;

	//assert( enterNode->type() == rapidxml::node_type:: );

	impl->valuesStack.push( enterNode );
	return true;
}

/**@brief */
void			IDeserializer::Exit			() const
{
	auto value = impl->valuesStack.top();
	impl->valuesStack.pop();
}

//=========================================================//
//				
//=========================================================//

/**@brief Wchodzi do pierwszego elementu tablicy lub obiektu.

Je¿eli wêze³, w którym jesteœmy, nie ma ¿adnych dzieci, pozostajemy w nim
i stan serializatora nie zmienia siê.

@return Zwaca false, je¿eli nie ma ¿adnego obiektu w tablicy (lub obiekcie).*/
bool			IDeserializer::FirstElement() const
{
	auto value = impl->valuesStack.top();
	
	auto firstChild = value->first_node( nullptr );		// Wstawienie nullptra oznacza wybranie pierwszego dziecka w kolejnoœci.
	if( firstChild == nullptr )
		return false;

	impl->valuesStack.push( firstChild );
	return true;
}

/**@brief Goes to next element in current object.

@return Returns false if there're no elements left..*/
bool			IDeserializer::NextElement() const
{
	auto value = impl->valuesStack.top();
		
	auto nextValue = value->next_sibling( nullptr );		// Nullptr means taking next element in order.
	if( nextValue == nullptr )
		return false;

	impl->valuesStack.pop();
	impl->valuesStack.push( nextValue );
	return true;
}

/**@brief Przechodzi do poprzedniego elementu w tablicy lub w obiekcie.*/
bool			IDeserializer::PrevElement() const
{
	auto value = impl->valuesStack.top();
	
	auto prevValue = value->previous_sibling( nullptr );	// Nullptr means taking next element in order.
	if( prevValue == nullptr )
		return false;

	impl->valuesStack.pop();
	impl->valuesStack.push( prevValue );
	return true;
}

/**@brief Wchodzi do ostatniego elementu tablicy lub obiektu.

Je¿eli wêze³, w którym jesteœmy, nie ma ¿adnych dzieci, pozostajemy w nim
i stan serializatora nie zmienia siê.

@return Zwaca false, je¿eli nie ma ¿adnego obiektu w tablicy (lub obiekcie).*/
bool			IDeserializer::LastElement() const
{
	auto value = impl->valuesStack.top();
	
	auto lastChild = value->last_node( nullptr );		// Wstawienie nullptra oznacza wybranie pierwszego dziecka w kolejnoœci.
	if( lastChild == nullptr )
		return false;

	impl->valuesStack.push( lastChild );
	return true;
}

//=========================================================//
//			GetAttribute funkcje pomocnicze
//=========================================================//

namespace
{

/**@brief Converts a string to numeric values using the `strol` function and returns the same values.
See the documentation for the C++ standard library.*/
template< typename ElementType >
inline ElementType Convert							( const char* valueBegin, char** checkEndPtr )
{
	assert( false );
	return false;
}

const char* convertCharNullTerminator = "\0";

template<>
inline const char*	Convert< const char* >			( const char* valueBegin, char** checkEndPtr )
{
	// @fixme This is a terrible hack. If someone outside this function wanted to compare
	// the returned checkEndPtr pointer with the pointer they provided, they would be very surprised.
	// But somehow, I still don't want to check the length of this string when it's not necessary.
	*checkEndPtr = const_cast<char*>( convertCharNullTerminator );
	return valueBegin;
}

template<>
inline std::string	Convert< std::string >			( const char* valueBegin, char** checkEndPtr )
{
	return Convert< const char* >( valueBegin, checkEndPtr );
}


template<>
inline uint32		Convert< uint32 >				( const char* valueBegin, char** checkEndPtr )
{	return strtoul( valueBegin, checkEndPtr, 10 );	}

template<>
inline int32		Convert< int32 >				( const char* valueBegin, char** checkEndPtr )
{	return strtol( valueBegin, checkEndPtr, 10 );	}

template<>
inline uint64		Convert< uint64 >				( const char* valueBegin, char** checkEndPtr )
{	return strtoull( valueBegin, checkEndPtr, 10 );	}

template<>
inline int64		Convert< int64 >				( const char* valueBegin, char** checkEndPtr )
{	return strtoll( valueBegin, checkEndPtr, 10 );	}


const char* trueString = "true";
const char* falseString = "false";

template<>
inline bool			Convert< bool >					( const char* valueBegin, char** checkEndPtr )
{
	*checkEndPtr = const_cast<char*>( valueBegin );
	const char* referenceString;
	bool returnValue;

	if( **checkEndPtr == 't' )
	{
		returnValue = true;
		referenceString = trueString;
	}
	else if( **checkEndPtr == 'f' )
	{
		returnValue = false;
		referenceString = falseString;
	}
	else
		return false;

	int i = 0;
	do
	{
		++i;
		*checkEndPtr += 1;
	} while( **checkEndPtr == *( referenceString + i ) && **checkEndPtr != '\0' );

	return returnValue;
}

template<>
inline double		Convert< double >				( const char* valueBegin, char** checkEndPtr )
{	return strtod( valueBegin, checkEndPtr );	}



template<typename Type>
inline Type		GetAttribTemplate( DeserializerImpl* impl, const char* name, Type& defaultValue )
{
	rapidxml::xml_node<>* currentNode = impl->valuesStack.top();

	rapidxml::xml_attribute<>* attribute = currentNode->first_attribute( name );
	if( attribute == nullptr )
		return defaultValue;

	const char* attribValue = attribute->value();
	char* checkEndPtr = nullptr;	// Po konwersji dostaniemy tutaj wskaŸnik na bajt tu¿ za koñcem parsowanego elementu

	errno = 0;	// Funkcje strto** mog¹ zwróciæ ERANGE w przypadku przekroczenia wartoœci.

	auto value = Convert<Type>( attribValue, &checkEndPtr );
	if( *checkEndPtr != '\0' || errno == ERANGE )	// Je¿eli przy parsowaniu stringa nie doszliœmy do koñca, to znaczy, ¿e pojawi³ siê b³¹d.
		return defaultValue;

	return value;
}

}	// anonymous


//=========================================================//
//			GetAttribute string
//=========================================================//


/**@brief Pobiera parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
std::string				IDeserializer::GetAttribute			( const std::string& name, std::string& defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}

/**@brief Zwraca atrybut o podanej nazwie.

@attention Zwracany string przestanie istnieæ w momencie usuniêcia serializatora lub zmiany zawartoœci.

@param[in] name Nazwa atrybutu
@param[in] defaultValue Je¿eli element o podanej nazwie nie istnieje, zostanie zwrócona wartoœæ domyœlna.*/
const char*				IDeserializer::GetAttribute			( const std::string& name, const char* defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}


/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
uint32					IDeserializer::GetAttribute			( const std::string& name, uint32 defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
uint64					IDeserializer::GetAttribute			( const std::string& name, uint64 defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
int32					IDeserializer::GetAttribute			( const std::string& name, int32 defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
int64					IDeserializer::GetAttribute			( const std::string& name, int64 defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
bool					IDeserializer::GetAttribute			( const std::string& name, bool defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
double					IDeserializer::GetAttribute			( const std::string& name, double defaultValue ) const
{
	return GetAttribTemplate( impl, name.c_str(), defaultValue );
}


//=========================================================//
//			GetAttribute const char
//=========================================================//

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
std::string		IDeserializer::GetAttribute		( const char* name, std::string& defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
const char*		IDeserializer::GetAttribute		( const char* name, const char* defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
uint32			IDeserializer::GetAttribute		( const char* name, uint32 defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
uint64			IDeserializer::GetAttribute		( const char* name, uint64 defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
int32			IDeserializer::GetAttribute		( const char* name, int32 defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
int64			IDeserializer::GetAttribute		( const char* name, int64 defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
bool			IDeserializer::GetAttribute		( const char* name, bool defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

/**@brief Ustawia parê ( nazwa, wartoœæ ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] defaultValue Wartoœæ, jaka zostanie wpisana do podanej zmiennej.*/
double			IDeserializer::GetAttribute		( const char* name, double defaultValue ) const
{
	return GetAttribTemplate( impl, name, defaultValue );
}

//====================================================================================//
//			Error handling
//====================================================================================//

/**@brief Returns parsing error if it occured.

Aby siê dowiedzieæ czy parsowanie powiod³o siê, sprawdŸ wartoœæ zwracan¹ przez
funkcje @ref LoadFromString lub @ref LoadFromFile.*/
std::string		IDeserializer::GetError			() const
{
	return impl->errorString;
}


// ================================ //
//
sw::FilePosition					ComputeXmlPosition     ( const char* fileBegin, const char* nodeFirstChar )
{
    sw::FilePosition pos;
    pos.Line = 1;
    pos.CharPosition = 0;

    const char* xmlPosition = fileBegin;
    const char* processedLineBegin = xmlPosition;

    while( xmlPosition < nodeFirstChar )
    {
        if( *xmlPosition == '\n' )
        {
            pos.Line++;
            processedLineBegin = xmlPosition + 1;
        }

        xmlPosition++;
    }

    // Note: numerate position from 1.
    pos.CharPosition = nodeFirstChar - processedLineBegin + 1;

    return pos;
}

// ================================ //
//
sw::FilePosition					IDeserializer::CurrentLineNumber      () const
{
    auto& curNode = impl->valuesStack.top();
	const char* fileFirstChar = impl->fileContent.data();
	const char* nodeFirstChar = curNode->name();

    return ComputeXmlPosition( fileFirstChar, nodeFirstChar );
}


