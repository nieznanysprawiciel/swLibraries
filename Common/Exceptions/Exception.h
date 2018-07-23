#pragma once


#include "swCommonLib/Common/TypesDefinitions.h"

#include <exception>
#include <string>



namespace sw
{


/**@brief Base exception class.
@ingroup Helpers*/
class Exception : public std::exception
{
private:
protected:
public:
	explicit		Exception		() = default;
	virtual			~Exception		() = default;

	/**@brief Returns human readable exception message.*/
	virtual std::string		ErrorMessage	() const = 0;
};

DEFINE_PTR_TYPE( Exception )


/**@brief Base Sleeping Wombat exception class containing string error message.
@ingroup Helpers*/
class RuntimeException : public Exception
{
private:
protected:

	std::string		m_errorMessage;

public:

	// ================================ //
	//
	explicit		RuntimeException		( const std::string& message )
		: m_errorMessage( message )
	{}

	virtual			~RuntimeException		() = default;


	virtual std::string		ErrorMessage	() const { return m_errorMessage; }
};

DEFINE_PTR_TYPE( RuntimeException )


}	// sw

