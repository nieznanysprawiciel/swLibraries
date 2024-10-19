/**
@file Serializer.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swSerialization/Interfaces/Serializer.h"


#include "swCommonLib/System/Dir.h"


#include "swSerialization/External/RapidXML/rapidxml.hpp"
#include "swSerialization/External/RapidXML/rapidxml_print.hpp"

#include "swSerialization/Serializers/SerializerXML/Escaping.h"

#include <fstream>
#include <stack>
#include <stdio.h>
#include <float.h>


using namespace sw;

/**@defgroup SerializerXML XML Serializer
@ingroup Serialization
@brief Implementation of XML serialization.

Project SerializerXML contains implementation of XML serialization based on RapidXML library.
http://rapidxml.sourceforge.net/*/




struct SerializerImpl
{
	rapidxml::xml_document<>			root;
	std::stack< rapidxml::xml_node<>* >	valuesStack;
};

namespace
{

/// Helper
inline void SetAttributeHelper( SerializerImpl* impl, const char* name, Size nameSize, const char* value, Size valueSize )
{
	char* attribName = impl->root.allocate_string( name, nameSize );
	char* attribValue = impl->root.allocate_string( value, valueSize );

	rapidxml::xml_attribute<>* attribute = impl->root.allocate_attribute( attribName, attribValue, nameSize, valueSize );
	auto currentNode = impl->valuesStack.top();
	currentNode->append_attribute( attribute );
}

} //anonymous

/**@brief Konstruktor*/
ISerializer::ISerializer( ISerializationContextPtr serContext )
	: context( serContext )
{
	impl = new SerializerImpl;
	impl->valuesStack.push( &impl->root );
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

    while( impl->valuesStack.size() > 1 )
        this->Exit();

    std::ofstream file;
    file.open( fileName, std::ios::out | std::ios::trunc );
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
    int printingFlag = 0;
    if( mode == WritingMode::Sparing )
        printingFlag = rapidxml::print_no_indenting;

    std::string xmlString;
    rapidxml::print( std::back_inserter( xmlString ), impl->root, printingFlag );
    return xmlString;
}

/**@brief Creates an object with the given name.

@param[in] name The name of the object.*/
void ISerializer::EnterObject( const std::string& name )
{
	char* nodeName = AllocateEscaped(impl->root, name);
	rapidxml::xml_node<>* node = impl->root.allocate_node( rapidxml::node_type::node_element, nodeName );
	impl->valuesStack.push( node );
}

/**@brief Koniec tworzenia obiektu.
EnterObject i ExitObject powinny by� stosowane parami.*/
void ISerializer::Exit()
{
	rapidxml::xml_node<>* attachNode = impl->valuesStack.top();		// Obiekt, kt�rego konstruowanie skonczyli�my.
	impl->valuesStack.pop();
	rapidxml::xml_node<>* attachTo = impl->valuesStack.top();		// Nazwa obiektu.

	attachTo->append_node( attachNode );
}

/**@brief Tworzy tablic� o podanej nazwie.

@param[in] name Nazwa tablicy.*/
void ISerializer::EnterArray( const std::string& name )
{
	char* nodeName = AllocateEscaped(impl->root, name);
	rapidxml::xml_node<>* node = impl->root.allocate_node( rapidxml::node_type::node_element, nodeName );
	impl->valuesStack.push( node );
}

/**@brief Sets a pair (name, value) in the current object.

@param[in] name The name of the variable to be set.
@param[in] value The value to be assigned to the variable.*/
void ISerializer::SetAttribute( const std::string& name, const std::string& value )
{
	SetAttributeHelper( impl, name.c_str(), name.length(), value.c_str(), value.length() );
}

/**@brief Sets a pair (name, value) in the current object.

@param[in] name The name of the variable to be set.
@param[in] value The value to be assigned to the variable.*/
void ISerializer::SetAttribute( const std::string& name, const char* value )
{
	SetAttributeHelper( impl, name.c_str(), name.length(), value, strlen( value ) );
}


/**@brief Sets a pair (name, value) in the current object.

@param[in] name The name of the variable to be set.
@param[in] value The value to be assigned to the variable.*/
void ISerializer::SetAttribute( const std::string& name, uint32 value )
{
#define MAX_UINT32_SIGNS 11
	char numericString[ MAX_UINT32_SIGNS ];
	Size valueLength = sprintf_s( numericString, "%u", value );

	SetAttributeHelper( impl, name.c_str(), name.length(), numericString, valueLength );
}

/**@brief Sets a pair (name, value) in the current object.

@param[in] name The name of the variable to be set.
@param[in] value The value to be assigned to the variable.*/
void ISerializer::SetAttribute( const std::string& name, uint64 value )
{
#define MAX_UINT64_SIGNS 21
	char numericString[ MAX_UINT64_SIGNS ];
	Size valueLength = sprintf_s( numericString, "%llu", value );

	SetAttributeHelper( impl, name.c_str(), name.length(), numericString, valueLength );
}

/**@brief Sets a pair (name, value) in the current object.

@param[in] name The name of the variable to be set.
@param[in] value The value to be assigned to the variable.*/
void ISerializer::SetAttribute( const std::string& name, int32 value )
{
#define MAX_INT32_SIGNS 12
	char numericString[ MAX_INT32_SIGNS ];
	Size valueLength = sprintf_s( numericString, "%i", value );

	SetAttributeHelper( impl, name.c_str(), name.length(), numericString, valueLength );
}

/**@brief Sets a pair (name, value) in the current object.

@param[in] name The name of the variable to be set.
@param[in] value The value to be assigned to the variable.*/
void ISerializer::SetAttribute( const std::string& name, int64 value )
{
#define MAX_INT64_SIGNS 22
	char numericString[ MAX_INT64_SIGNS ];
	Size valueLength = sprintf_s( numericString, "%lli", value );

	SetAttributeHelper( impl, name.c_str(), name.length(), numericString, valueLength );
}

/**@brief Sets a pair (name, value) in the current object.

@param[in] name The name of the variable to be set.
@param[in] value The value to be assigned to the variable.*/
void ISerializer::SetAttribute( const std::string& name, bool value )
{
	if( value )
		SetAttributeHelper( impl, name.c_str(), name.length(), "true", 4 );
	else
		SetAttributeHelper( impl, name.c_str(), name.length(), "false", 5 );
}

/**@brief Sets a pair (name, value) in the current object.

@param[in] name The name of the variable to be set.
@param[in] value The value to be assigned to the variable.*/
void ISerializer::SetAttribute( const std::string& name, double value )
{
#define MAX_DOUBLE_SIGNS 52
	char numericString[ MAX_DOUBLE_SIGNS ];
	Size valueLength = std::snprintf( numericString, MAX_DOUBLE_SIGNS, "%.19f", value );

	SetAttributeHelper( impl, name.c_str(), name.length(), numericString, valueLength );
}

