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


namespace sw
{


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
        return Result::Success;
    }
    return fmt::format( "Saving file [{}] failed. Error: {}", fileName, std::strerror( errno ) );
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
    std::ifstream file( fileName, std::ios::binary | std::ios::ate );

    if( file.fail() )
        return fmt::format( "Loading file [{}] failed. Error: {}", fileName, std::strerror( errno ) );

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
        auto errorOffset = static_cast<PtrOffset>( e.where< char >() - m_content.data() );
        return fmt::format( "Parsing failed. Error: {}, offset: {}", e.what(), errorOffset );
    }
    catch( const std::exception& e )
    {
        return fmt::format( "Parsing failed. Error: {}.", e.what() );
    }
    catch( ... )
    {
        return fmt::format( "Parsing failed. Unknown error." );
    }

    return Result::Success;
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
    auto parentXmlNode = impl::FromSerialNode( parent );
    auto newNode = ConstructNode( name );

    parentXmlNode->append_node( newNode );

    return SerialObject( this, impl::ToNodePtr( newNode ) );
}

// ================================ //
//
SerialArray             SerializerXML::AddArray         ( const SerialObject& parent, std::string_view name )
{
    assert( !"Implement me " );
    return SerialArray( this, impl::ToNodePtr( &m_root ) );
}

// ================================ //
//
SerialObject            SerializerXML::AddObject        ( const SerialArray& parent, std::string_view nameHint )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( &m_root ) );
}

// ================================ //
//
SerialArray             SerializerXML::AddArray         ( const SerialArray& parent, std::string_view nameHint )
{
    assert( !"Implement me " );
    return SerialArray( this, impl::ToNodePtr( &m_root ) );
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, std::string_view attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( &m_root ) );
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, double attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( &m_root ) );
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, uint64 attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( &m_root ) );
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, int64 attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( &m_root ) );
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, bool attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( &m_root ) );
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& parent, std::string_view name, char attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( &m_root ) );
}

// ================================ //
//
rapidxml::xml_node<>*   SerializerXML::ConstructNode    ( const std::string_view& name )
{
    char* nodeName = m_root.allocate_string( name.data(), name.size() );
    return m_root.allocate_node( rapidxml::node_type::node_element, nodeName );
}




}	// sw


