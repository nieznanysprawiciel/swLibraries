#pragma once

#include "swCommonLib/Common/Exceptions/Exception.h"
#include "swCommonLib/Serialization/FilePosition.h"



namespace sw
{

/**@brief Base class for serialization exceptions.

Contains line number and position of error or warning in deserialized content.*/
class SerializationException : public RuntimeException
{
private:

	FilePosition			m_filePosition;

public:

    explicit        SerializationException   ( const std::string& message, FilePosition filePos )
        :   RuntimeException( message )
        ,   m_filePosition( filePos )
    {}

	/**@brief Returns human readable exception message.*/
	virtual std::string		ErrorMessage		() const;


protected:

    std::string				PrintLineNumber		() const;
	std::string				PrintWarning		() const;
	std::string				PrintError			() const;
};

DEFINE_PTR_TYPE( SerializationException )

}	// sw

