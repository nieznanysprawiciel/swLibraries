/**
@file SerializerXML.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "SerializerXML.h"


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
    return ReturnResult();
}

// ================================ //
//
std::string             SerializerXML::SaveString       ( WritingMode mode ) const
{
    return std::string();
}

// ================================ //
//
ReturnResult            SerializerXML::LoadFromFile     ( const std::string& fileName )
{
    return ReturnResult();
}

// ================================ //
//
ReturnResult            SerializerXML::LoadFromString   ( const std::string& content )
{
    return ReturnResult();
}

// ================================ //
//
ReturnResult            SerializerXML::LoadFromString   ( std::string content )
{
    return ReturnResult();
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


