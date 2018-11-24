#pragma once
/**
@file ExceptionsList.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Exception.h"

#include <vector>



namespace sw
{

class ExceptionsList;
DEFINE_PTR_TYPE( ExceptionsList )


/**@brief Exception that can store multiple nested exceptions.
@ingroup Helpers*/
class ExceptionsList : public Exception
{
private:
protected:

	std::vector< ExceptionPtr >		m_nestedExceptions;

public:
	explicit		ExceptionsList		() = default;
	virtual			~ExceptionsList		() = default;

	/**@brief Returns human readable exception message.*/
	virtual std::string		ErrorMessage	() const;

public:

	void					MergeExceptions	( ExceptionsListPtr list );
	void					AddException	( ExceptionPtr except );

public:

	const std::vector< ExceptionPtr >&		GetNestedExceptions		() const { return m_nestedExceptions; }
};




}	// sw


