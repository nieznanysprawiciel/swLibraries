#pragma once
/**
@file Exception.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/RTTR.h"

#include <exception>
#include <string>



namespace sw
{

/**@defgroup Exceptions
@ingroup Helpers*/


/**@brief Base exception class.
@ingroup Exceptions*/
class Exception : public std::exception
{
	RTTR_ENABLE();
private:
protected:
public:
	explicit		Exception		() = default;
	virtual			~Exception		() = default;

	/**@brief Returns human readable exception message.*/
	virtual std::string		ErrorMessage	() const = 0;


	/**@brief Compatibility with std c++ exceptions.*/
    virtual char const*		what			() const
    {
		static_cast< std::exception& >( *const_cast< Exception* >( this ) ) = std::exception( ErrorMessage().c_str() );
		return std::exception::what();
    }
};

DEFINE_PTR_TYPE( Exception )


/**@brief Base Sleeping Wombat exception class containing string error message.
@ingroup Exceptions*/
class RuntimeException : public Exception
{
	RTTR_ENABLE( Exception );
private:
protected:

	std::string		m_errorMessage;

public:

	// ================================ //
	//
	explicit		RuntimeException		( std::string message )
		: m_errorMessage( std::move( message ) )
	{}

	virtual			~RuntimeException		() = default;


	virtual std::string		ErrorMessage	() const { return m_errorMessage; }
};

DEFINE_PTR_TYPE( RuntimeException )


}	// sw

