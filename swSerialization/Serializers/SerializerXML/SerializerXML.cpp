/**
@file SerializerXML.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "SerializerXML.h"

#include "swCommonLib/System/Dir.h"
#include "swCommonLib/System/File.h"
#include "swCommonLib/Common/fmt.h"

#include "swSerialization/External/RapidXML/rapidxml.hpp"
#include "swSerialization/External/RapidXML/rapidxml_print.hpp"

#include <fstream>
#include <sstream>


namespace sw
{

sw::FilePosition ComputeXmlPosition(const char* fileBegin, const char* nodeFirstChar);

namespace impl
{

// ================================ //
//
impl::NodePointer       ToNodePtr       ( const rapidxml::xml_node<>* xmlNode )
{
    return xmlNode;
}

// ================================ //
//
impl::NodePointer       ToNodePtr       ( const rapidxml::xml_attribute<>* xmlAttribute )
{
    return xmlAttribute;
}


// ================================ //
//
rapidxml::xml_node<>*   FromNodePtr     ( impl::NodePointer ptr )
{
    return reinterpret_cast< rapidxml::xml_node<>* >( const_cast< void* >( ptr ) );
}

// ================================ //
//
rapidxml::xml_node<>*   FromSerialNode  ( const impl::SerialBase& node )
{
    return FromNodePtr( node.GetNodePtr() );
}


}   // impl


// ================================ //
//
SerializerXML::SerializerXML( ISerializationContextPtr serContext )
    : ISerializer( std::move( serContext ) )
{}

// ================================ //
//
ReturnResult            SerializerXML::SaveFile         ( const std::string& fileName, WritingMode mode ) const
{
    // Ensure directory exists.
    filesystem::Dir::CreateDirectory( fileName );

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
std::string             SerializerXML::SaveString       ( WritingMode mode ) const
{
    int printingFlag = 0;
    if( mode == WritingMode::Sparing )
        printingFlag = rapidxml::print_no_indenting;

    std::string xmlString;
    rapidxml::print( std::back_inserter( xmlString ), m_root, printingFlag );
    return xmlString;
}

// ================================ //
//
ReturnResult            SerializerXML::LoadFromFile     ( const std::string& fileName )
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
ReturnResult            SerializerXML::LoadFromString   ( std::string content )
{
    m_content = std::move( content );

    try
    {
        // This line will modify m_content. XML tree will reference
        // strings in m_content.
        m_root.parse< rapidxml::parse_default >( m_content.data() );
    }
    catch( const rapidxml::parse_error& e )
    {
        auto position = ComputeXmlPosition(m_content.data(), e.where< char >());
        return fmt::format("Parsing failed. Error: {}, line: {} at position: {}", e.what(), position.Line, position.CharPosition);
    }
    catch( const std::exception& e )
    {
        return fmt::format( "Parsing failed. Error: {}.", e.what() );
    }
    catch( ... )
    {
        return fmt::format( "Parsing failed. Unknown error." );
    }

    return Success::True;
}

// ================================ //
//
SerialObject            SerializerXML::Root             ()
{
    return SerialObject( this, impl::ToNodePtr( &m_root ) );
}

// ================================ //
//
SerialObject            SerializerXML::AddObject        ( const SerialObject& parent, std::string_view name )
{
    return SerializerXML::AddObject( parent.ArrayView(), name );
}

// ================================ //
//
SerialArray             SerializerXML::AddArray         ( const SerialObject& parent, std::string_view name )
{
    // In xml array is the same as object.
    return SerializerXML::AddObject( parent.ArrayView(), name ).ArrayView();
}

// ================================ //
//
SerialObject            SerializerXML::AddObject        ( const SerialArray& parent, std::string_view nameHint )
{
    auto parentXmlNode = impl::FromSerialNode( parent );
    auto newNode = ConstructNode( nameHint );

    parentXmlNode->append_node( newNode );

    return SerialObject( this, impl::ToNodePtr( newNode ) );
}

// ================================ //
//
SerialArray             SerializerXML::AddArray         ( const SerialArray& parent, std::string_view nameHint )
{
    // In xml array is the same as object.
    return SerializerXML::AddObject( parent, nameHint ).ArrayView();
}

// ================================ //
//
void                    SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, std::string_view attribute )
{
    assert( !"Implement me " );
}

// ================================ //
//
void                    SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, double attribute )
{
    assert( !"Implement me " );
}

// ================================ //
//
void                    SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, uint64 attribute )
{
    assert( !"Implement me " );
}

// ================================ //
//
void                    SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, int64 attribute )
{
    assert( !"Implement me " );
}

// ================================ //
//
void                    SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, bool attribute )
{
    assert( !"Implement me " );
}

// ================================ //
//
void                    SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, char attribute )
{
    assert( !"Implement me " );
}

//====================================================================================//
//			Deserialization API	
//====================================================================================//

// ================================ //
//
Size                                    SerializerXML::GetNumElements       ( const SerialObject& parent ) const
{
    //auto parentXmlNode = impl::FromSerialNode( parent );
    //
    //Size numChildren = 0;
    //while( auto child = parentXmlNode-> )

    return Size();
}

// ================================ //
//
sw::FilePosition                        SerializerXML::CurrentLineNumber    ( const SerialObject& node ) const
{
    return sw::FilePosition();
}

// ================================ //
//
std::optional< SerialObjectChild >      SerializerXML::GetElement           ( const SerialObject& parent, Size index ) const
{
    return std::optional<SerialObjectChild>();
}

// ================================ //
//
std::optional< SerialGeneric >          SerializerXML::GetElement           ( const SerialObject& parent, std::string_view name ) const
{
    auto parentXmlNode = impl::FromSerialNode( parent );

    if( auto child = parentXmlNode->first_node( name.data(), name.size() ) )
        return SerialGeneric( const_cast< SerializerXML* >( this ), impl::ToNodePtr( child ), SerialType::Object );

    if( auto attribute = parentXmlNode->first_attribute( name.data(), name.size() ) )
        return SerialGeneric( const_cast< SerializerXML* >( this ), impl::ToNodePtr( attribute ), SerialType::Attribute );

    return {};
}

// ================================ //
//
std::string_view                        SerializerXML::GetString            ( const SerialAttribute& attribute ) const
{
    return std::string_view();
}

// ================================ //
//
double                                  SerializerXML::GetDouble            ( const SerialAttribute& attribute ) const
{
    return 0.0;
}

// ================================ //
//
uint64                                  SerializerXML::GetUInt64            ( const SerialAttribute& attribute ) const
{
    return uint64();
}

// ================================ //
//
int64                                   SerializerXML::GetInt64             ( const SerialAttribute& attribute ) const
{
    return int64();
}

// ================================ //
//
bool                                    SerializerXML::GetBool              ( const SerialAttribute& attribute ) const
{
    return false;
}

//====================================================================================//
//			Internal implementation helpers	
//====================================================================================//

// ================================ //
//
rapidxml::xml_node<>*   SerializerXML::ConstructNode    ( const std::string_view& name )
{
    char* nodeName = m_root.allocate_string( name.data(), name.size() );
    return m_root.allocate_node( rapidxml::node_type::node_element, nodeName, 0, name.size() );
}




}	// sw


