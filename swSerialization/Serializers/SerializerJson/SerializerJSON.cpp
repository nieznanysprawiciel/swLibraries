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
{}

//====================================================================================//
//			Loading and saving functionalities	
//====================================================================================//


// ================================ //
//
ReturnResult            SerializerJSON::SaveFile         ( const std::string& fileName, WritingMode mode ) const
{
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
    return Result::Error;
}

// ================================ //
//
ReturnResult            SerializerJSON::LoadFromString   ( std::string content )
{

    return Result::Error;
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
    assert( !"Implement me " );
    return SerializerJSON::AddObject( parent.ArrayView(), name );
}

// ================================ //
//
SerialArray             SerializerJSON::AddArray            ( const SerialObject& parent, std::string_view name )
{
    assert( !"Implement me " );
    // In xml array is the same as object.
    return SerializerJSON::AddObject( parent.ArrayView(), name ).ArrayView();
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

