#pragma once
/**
@file SerializerXML.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Interfaces/ISerializer.h"

#include "swSerialization/External/RapidXML/rapidxml.hpp"



namespace sw
{


/**@defgroup SerializerXML XML Serializer
@ingroup Serialization
@brief Implementation of XML serialization.

Project SerializerXML contains implementation of XML serialization based on RapidXML library.
http://rapidxml.sourceforge.net/*/



/**@brief XML serializer.
@ingroup Serialization
@ingroup SerializerXML*/
class SerializerXML : public ISerializer
{
private:

    rapidxml::xml_document<>            m_root;

protected:
public:

    explicit		SerializerXML		( ISerializationContextPtr serContext );
    virtual         ~SerializerXML	    () = default;

public:

    /**@brief Writes serialized content to file.
    @todo Consider using filesystem::Path or std::filesystem::path*/
    virtual ReturnResult		SaveFile			( const std::string& fileName, WritingMode mode ) const;

    /**@brief Returns strign with serialized content.
    @todo Could this function fail? Maybe we should use Nullable. But Nullable doesn't support strings yet.*/
    virtual std::string	        SaveString			( WritingMode mode ) const;

    /**@brief Loads content of file to this serializer.
    @todo Consider using filesystem::Path or std::filesystem::path*/
    virtual ReturnResult        LoadFromFile	    ( const std::string& fileName );

    /**@brief Deserializes content of string.
    @note: This function doesn't modify string, so it can't use more efficient insitu parsing.
    Use overloads instead for better performance.*/
    virtual ReturnResult        LoadFromString	    ( const std::string& content );

    /**@brief Deserializes content of string.
    Insitu parsing of string.*/
    virtual ReturnResult        LoadFromString	    ( std::string content );

public:

    virtual SerialObject        AddObject           ( const SerialObject& node, std::string_view name );
    virtual SerialArray         AddArray            ( const SerialObject& node, std::string_view name );

    /**@brief Adds serialization node to array.
    nameHint is optional, not all serializers will support it.*/
    virtual SerialObject        AddObject           ( const SerialArray& node, std::string_view nameHint );
    virtual SerialArray         AddArray            ( const SerialArray& node, std::string_view nameHint );

    virtual SerialObject        AddAttribute        ( const SerialObject& node, std::string_view name, std::string_view attribute );
    virtual SerialObject        AddAttribute        ( const SerialObject& node, std::string_view name, double attribute );
    virtual SerialObject        AddAttribute        ( const SerialObject& node, std::string_view name, uint64 attribute );
    virtual SerialObject        AddAttribute        ( const SerialObject& node, std::string_view name, int64 attribute );
    virtual SerialObject        AddAttribute        ( const SerialObject& node, std::string_view name, bool attribute );
    virtual SerialObject        AddAttribute        ( const SerialObject& node, std::string_view name, char attribute );
};





}	// sw


