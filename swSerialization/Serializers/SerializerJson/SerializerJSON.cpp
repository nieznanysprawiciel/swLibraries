/**
@file SerializerJSON.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#define RAPIDJSON_HAS_STDSTRING 1

#include "SerializerJSON.h"

#include "swCommonLib/System/Dir.h"
#include "swCommonLib/System/File.h"
#include "swCommonLib/Common/fmt.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include "ErrorCodes.h"

#include <fstream>



namespace sw
{


namespace impl
{

// ================================ //
//
impl::NodePointer       ToNodePtr       ( const rapidjson::Value& jsonNode )
{
    return &jsonNode;
}

// ================================ //
//
rapidjson::Value&       FromNodePtr     ( impl::NodePointer ptr )
{
    return *reinterpret_cast< rapidjson::Value* >( const_cast< void* >( ptr ) );
}

// ================================ //
//
rapidjson::Value&       FromSerialNode  ( const impl::SerialBase& node )
{
    return FromNodePtr( node.GetNodePtr() );
}


}   // impl




// ================================ //
//
SerializerJSON::SerializerJSON      ( ISerializationContextPtr serContext )
    :   ISerializer( std::move( serContext ) )
{
    m_root.SetObject();
}

//====================================================================================//
//			Loading and saving functionalities	
//====================================================================================//


// ================================ //
//
ReturnResult            SerializerJSON::SaveFile         ( const std::string& fileName, WritingMode mode ) const
{
    // Ensure directory exists.
    filesystem::Dir::CreateDirectory( fileName );

    std::ofstream file;
    file.open( fileName );
    if( !file.fail() )
    {
        file << SaveString( mode );

        file.close();
        return Result::Success;
    }
    return fmt::format( "Saving file [{}] failed. Error: {}", fileName, Convert::ErrnoToString( errno ) );
}

// ================================ //
//
std::string             SerializerJSON::SaveString       ( WritingMode mode ) const
{
    rapidjson::StringBuffer stringBuffer;
    
    if( mode == WritingMode::Sparing )
    {
        rapidjson::Writer< rapidjson::StringBuffer > writer( stringBuffer );
        m_root.Accept( writer );
    }
    else
    {
        rapidjson::PrettyWriter< rapidjson::StringBuffer > writer( stringBuffer );
        m_root.Accept( writer );
    }

    return stringBuffer.GetString();
}

// ================================ //
//
ReturnResult            SerializerJSON::LoadFromFile     ( const std::string& fileName )
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
ReturnResult            SerializerJSON::LoadFromString   ( std::string content )
{
    m_content = std::move( content );

    m_root.ParseInsitu( m_content.data() );

    if( m_root.HasParseError() )
    {
        rapidjson::ParseErrorCode code = m_root.GetParseError();
        auto lineNum = m_root.GetErrorOffset();

        return fmt::format( "Parsing failed. Error: {}, line: {}", GetStringFromCode( code ), lineNum );
    }

    return Result::Success;
}


//====================================================================================//
//			Serialization API	
//====================================================================================//

// ================================ //
//
SerialObject            SerializerJSON::Root                ()
{
    return SerialObject( this, impl::ToNodePtr( m_root ) );
}

// ================================ //
//
SerialObject            SerializerJSON::AddObject           ( const SerialObject& parent, std::string_view name )
{
    rapidjson::Value objectValue( rapidjson::kObjectType );
    rapidjson::Value objectName( rapidjson::kStringType );

    objectName.SetString( name.data(), ( rapidjson::SizeType )name.length(), m_root.GetAllocator() );

    auto& parentJsonNode = impl::FromSerialNode( parent );
    parentJsonNode.AddMember( std::move( objectName ), std::move( objectValue ), m_root.GetAllocator() );
    
    return SerialObject( this, impl::ToNodePtr( objectValue ) );
}

// ================================ //
//
SerialArray             SerializerJSON::AddArray            ( const SerialObject& parent, std::string_view name )
{
    rapidjson::Value arrayValue( rapidjson::kArrayType );
    rapidjson::Value arrayName( rapidjson::kStringType );

    arrayName.SetString( name.data(), ( rapidjson::SizeType )name.length(), m_root.GetAllocator() );

    auto& parentJsonNode = impl::FromSerialNode( parent );
    parentJsonNode.AddMember( std::move( arrayName ), std::move( arrayValue ), m_root.GetAllocator() );

    return SerialArray( this, impl::ToNodePtr( arrayValue ) );
}

// ================================ //
//
SerialObject            SerializerJSON::AddObject           ( const SerialArray& parent, std::string_view nameHint )
{
    assert( !"Implement me " );
    return SerialObject( this, nullptr );
}

// ================================ //
//
SerialArray             SerializerJSON::AddArray            ( const SerialArray& parent, std::string_view nameHint )
{
    assert( !"Implement me " );

    // In xml array is the same as object.
    return SerializerJSON::AddObject( parent, nameHint ).ArrayView();
}

// ================================ //
//
SerialObject            SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, std::string_view attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( m_root ) );
}

// ================================ //
//
SerialObject            SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, double attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( m_root ) );
}

// ================================ //
//
SerialObject            SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, uint64 attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( m_root ) );
}

// ================================ //
//
SerialObject            SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, int64 attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( m_root ) );
}

// ================================ //
//
SerialObject            SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, bool attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( m_root ) );
}

// ================================ //
//
SerialObject            SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, char attribute )
{
    assert( !"Implement me " );
    return SerialObject( this, impl::ToNodePtr( m_root ) );
}

//====================================================================================//
//			Deserialization API	
//====================================================================================//

// ================================ //
//
Size                                    SerializerJSON::GetNumElements       ( const SerialObject& parent ) const
{
    return Size();
}

// ================================ //
//
sw::FilePosition                        SerializerJSON::CurrentLineNumber    ( const SerialObject& node ) const
{
    return sw::FilePosition();
}

// ================================ //
//
std::optional< SerialObjectChild >      SerializerJSON::GetElement           ( const SerialObject& parent, Size index ) const
{
    return std::optional<SerialObjectChild>();
}

// ================================ //
//
std::optional< SerialGeneric >          SerializerJSON::GetElement           ( const SerialObject& parent, std::string_view name ) const
{
    return {};
}


}	// sw

