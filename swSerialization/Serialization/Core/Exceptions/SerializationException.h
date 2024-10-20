#pragma once

#include "swCommonLib/Common/Exceptions/Exception.h"
#include "swSerialization/Interfaces/FilePosition.h"



namespace sw
{

class SerializationException;
DEFINE_PTR_TYPE( SerializationException )



/**@brief Base class for serialization exceptions.

Contains line number and position of error or warning in deserialized content.*/
class SerializationException : public RuntimeException
{
private:

	FilePosition			m_filePosition;

public:

    explicit        SerializationException   ( std::string message, FilePosition filePos )
        :   RuntimeException( message )
        ,   m_filePosition( filePos )
    {}

	/**@brief Returns human readable exception message.*/
	virtual std::string		ErrorMessage		() const;


protected:

    std::string				PrintLineNumber		() const;
	std::string				PrintWarning		() const;
	std::string				PrintError			() const;

public:

    static SerializationExceptionPtr        Create      ( std::string message, FilePosition filePos );
    static SerializationExceptionPtr        Create      ( const IDeserializer& deser, std::string message );
};


}	// sw

