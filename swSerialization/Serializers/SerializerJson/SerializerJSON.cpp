/**
@file SerializerJSON.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
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
#include <sstream>



namespace sw
{


namespace impl
{

const NodePointer cRootPointer = NodesRegistry::ToNodePtr( NodePointerImpl( 0, InvalidIndex ) );


// ================================ //
//
SerialType      ToSerialType            ( rapidjson::Type type )
{
    switch( type )
    {
    case rapidjson::kNullType:
        return SerialType::Attribute;
    case rapidjson::kFalseType:
        return SerialType::Bool;
    case rapidjson::kTrueType:
        return SerialType::Bool;
    case rapidjson::kObjectType:
        return SerialType::Object;
    case rapidjson::kArrayType:
        return SerialType::Array;
    case rapidjson::kStringType:
        return SerialType::String;
    case rapidjson::kNumberType:
        return SerialType::Number;
    default:
        return SerialType::Attribute;
    }
}

// ================================ //
//
SerialType      ToSerialType            ( const rapidjson::Value& value )
{
    auto type = value.GetType();
    auto serialType = ToSerialType( type );

    // Set precise type.
    if( serialType == SerialType::Number )
    {
        if( value.IsUint64() )
            return SerialType::UInt64;
        if( value.IsInt64() )
            return SerialType::Int64;
        if( value.IsDouble() )
            return SerialType::Double;
    }

    return serialType;
}


}   // impl




// ================================ //
//
SerializerJSON::SerializerJSON      ( ISerializationContextPtr serContext )
    :   ISerializer( std::move( serContext ) )
    ,   m_nodesRegistry( &m_root.SetObject(), m_root.GetAllocator() )
{}

//====================================================================================//
//			Loading and saving functionalities	
//====================================================================================//


// ================================ //
//
ReturnResult            SerializerJSON::SaveFile         ( const std::string& fileName, WritingMode mode ) const
{
    // Ensure directory exists.
    fs::Dir::CreateDirectory( fileName );

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

    return Success::True;
}


//====================================================================================//
//			Serialization API	
//====================================================================================//

// ================================ //
//
SerialObject            SerializerJSON::Root                ()
{
    return SerialObject( this, impl::cRootPointer );
}

// ================================ //
//
impl::NodePointer       SerializerJSON::AddObjectMember     ( const SerialObject& parent, std::string_view name, rapidjson::Type memberType )
{
    rapidjson::Value objectValue( memberType );
    rapidjson::Value objectName( rapidjson::kStringType );

    objectName.SetString( name.data(), ( rapidjson::SizeType )name.length(), m_root.GetAllocator() );

    auto& parentJsonNode = *m_nodesRegistry.GetElement( parent.GetNodePtr() );
    bool reallocation = parentJsonNode.MemberCount() == parentJsonNode.MemberCapacity();

    parentJsonNode.AddMember( objectName, objectValue, m_root.GetAllocator() );

    // Values were moved. Get member pointer from parent node.
    assert( parentJsonNode.IsObject() );

    auto newMemberIter = --parentJsonNode.MemberEnd();      // Exists for sure, we already added it.
    auto newNodePointer = m_nodesRegistry.AddMember( parent, &newMemberIter->value );

    /// Update registry if reallocation occured.
    if( reallocation )
        m_nodesRegistry.UpdateChildren( parent.GetNodePtr() );

    return impl::NodesRegistry::ToNodePtr( newNodePointer );
}

// ================================ //
//
impl::NodePointer       SerializerJSON::AddArrayMember      ( const SerialArray& parent, rapidjson::Type memberType )
{
    rapidjson::Value objectValue( memberType );

    auto& parentJsonNode = *m_nodesRegistry.GetElement( parent.GetNodePtr() );
    bool reallocation = parentJsonNode.Size() == parentJsonNode.Capacity();

    parentJsonNode.PushBack( std::move( objectValue ), m_root.GetAllocator() );

    // Values were moved. Get member pointer from parent node.
    assert( parentJsonNode.IsArray() );

    auto newNodeIdx = parentJsonNode.Size() - 1;
    auto newNodePointer = m_nodesRegistry.AddMember( parent, &parentJsonNode[ newNodeIdx ] );

    /// Update registry if reallocation occured.
    if( reallocation )
        m_nodesRegistry.UpdateChildren( parent.GetNodePtr() );

    return impl::NodesRegistry::ToNodePtr( newNodePointer );
}

// ================================ //
//
SerialObject            SerializerJSON::AddObject           ( const SerialObject& parent, std::string_view name )
{
    return SerialObject( this, AddObjectMember( parent, name, rapidjson::kObjectType ) );
}

// ================================ //
//
SerialArray             SerializerJSON::AddArray            ( const SerialObject& parent, std::string_view name )
{
    return SerialArray( this, AddObjectMember( parent, name, rapidjson::kArrayType ) );
}

// ================================ //
//
SerialObject            SerializerJSON::AddObject           ( const SerialArray& parent, std::string_view nameHint )
{
    return SerialObject( this, AddArrayMember( parent, rapidjson::kObjectType ) );
}

// ================================ //
//
SerialArray             SerializerJSON::AddArray            ( const SerialArray& parent, std::string_view nameHint )
{
    return SerialArray( this, AddArrayMember( parent, rapidjson::kArrayType ) );
}

// ================================ //
//
void                    SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, std::string_view attribute )
{
    auto attributePtr = AddObjectMember( parent, name, rapidjson::Type::kStringType );
    auto& jsonNode = *m_nodesRegistry.GetElement( attributePtr );

    jsonNode.SetString( attribute.data(), (rapidjson::SizeType)attribute.length() );
}

// ================================ //
//
void                    SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, double attribute )
{
    auto attributePtr = AddObjectMember( parent, name, rapidjson::Type::kNumberType );
    auto& jsonNode = *m_nodesRegistry.GetElement( attributePtr );

    jsonNode.SetDouble( attribute );
}

// ================================ //
//
void                    SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, uint64 attribute )
{
    auto attributePtr = AddObjectMember( parent, name, rapidjson::Type::kNumberType );
    auto& jsonNode = *m_nodesRegistry.GetElement( attributePtr );

    jsonNode.SetUint64( attribute );
}

// ================================ //
//
void                    SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, int64 attribute )
{
    auto attributePtr = AddObjectMember( parent, name, rapidjson::Type::kNumberType );
    auto& jsonNode = *m_nodesRegistry.GetElement( attributePtr );

    jsonNode.SetInt64( attribute );
}

// ================================ //
//
void                    SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, bool attribute )
{
    auto attributePtr = AddObjectMember( parent, name, rapidjson::Type::kTrueType );
    auto& jsonNode = *m_nodesRegistry.GetElement( attributePtr );

    jsonNode.SetBool( attribute );
}

// ================================ //
//
void                    SerializerJSON::AddAttribute        ( const SerialObject& parent, std::string_view name, char attribute )
{
    auto attributePtr = AddObjectMember( parent, name, rapidjson::Type::kStringType );
    auto& jsonNode = *m_nodesRegistry.GetElement( attributePtr );

    jsonNode.SetString( &attribute, 1 );
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
    // First we should add all children to registry.
    // This function will do nothing if they are already registered.
    m_nodesRegistry.RegisterChildren( parent.GetNodePtr() );

    auto& parentJsonNode = *m_nodesRegistry.GetElement( parent.GetNodePtr() );

    // This way we avoid copying string from string_view, because there's no
    // FindMember function that takes pointer and string length.
    rapidjson::Value objectName( rapidjson::kStringType );
    objectName.SetString( name.data(), ( rapidjson::SizeType )name.length() );

    auto iter = parentJsonNode.FindMember( objectName );

    // Member under this name not found.
    if( iter == parentJsonNode.MemberEnd() )
        return {};

    auto index = std::distance( parentJsonNode.MemberBegin(), iter );
    auto elementOpt = m_nodesRegistry.GetElement( parent.GetNodePtr(), index );

    if( !elementOpt.has_value() )
        return {};

    return SerialGeneric{ const_cast< SerializerJSON* >( this ), elementOpt.value(), impl::ToSerialType( iter->value ) };
}

// ================================ //
//
std::string_view                        SerializerJSON::GetString           ( const SerialAttribute& attribute ) const
{
    auto& jsonNode = *m_nodesRegistry.GetElement( attribute.GetNodePtr() );
    return std::string_view( jsonNode.GetString(), jsonNode.GetStringLength() );
}

// ================================ //
//
double                                  SerializerJSON::GetDouble           ( const SerialAttribute& attribute ) const
{
    auto& jsonNode = *m_nodesRegistry.GetElement( attribute.GetNodePtr() );

    assert( jsonNode.IsDouble() );
    return jsonNode.GetDouble();
}

// ================================ //
//
uint64                                  SerializerJSON::GetUInt64           ( const SerialAttribute& attribute ) const
{
    auto& jsonNode = *m_nodesRegistry.GetElement( attribute.GetNodePtr() );

    assert( jsonNode.IsUint64() );
    return jsonNode.GetUint64();
}

// ================================ //
//
int64                                   SerializerJSON::GetInt64            ( const SerialAttribute& attribute ) const
{
    auto& jsonNode = *m_nodesRegistry.GetElement( attribute.GetNodePtr() );

    assert( jsonNode.IsInt64() );
    return jsonNode.GetInt64();
}

// ================================ //
//
bool                                    SerializerJSON::GetBool             ( const SerialAttribute& attribute ) const
{
    auto& jsonNode = *m_nodesRegistry.GetElement( attribute.GetNodePtr() );

    assert( jsonNode.IsBool() );
    return jsonNode.GetBool();
}

}	// sw

