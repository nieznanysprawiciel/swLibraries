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


// ================================ //
//
SerializerXML::SerializerXML( ISerializationContextPtr serContext )
    :   ISerializer( std::move( serContext ) )
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
SerialObject            SerializerXML::AddObject        ( const SerialObject& node, std::string_view name )
{
    return SerialObject();
}

// ================================ //
//
SerialArray             SerializerXML::AddArray         ( const SerialObject& node, std::string_view name )
{
    return SerialArray();
}

// ================================ //
//
SerialObject            SerializerXML::AddObject        ( const SerialArray& node, std::string_view nameHint )
{
    return SerialObject();
}

// ================================ //
//
SerialArray             SerializerXML::AddArray         ( const SerialArray& node, std::string_view nameHint )
{
    return SerialArray();
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& node, std::string_view name, std::string_view attribute )
{
    return SerialObject();
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& node, std::string_view name, double attribute )
{
    return SerialObject();
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& node, std::string_view name, uint64 attribute )
{
    return SerialObject();
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& node, std::string_view name, int64 attribute )
{
    return SerialObject();
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& node, std::string_view name, bool attribute )
{
    return SerialObject();
}

// ================================ //
//
SerialObject            SerializerXML::AddAttribute     ( const SerialObject& node, std::string_view name, char attribute )
{
    return SerialObject();
}




}	// sw


