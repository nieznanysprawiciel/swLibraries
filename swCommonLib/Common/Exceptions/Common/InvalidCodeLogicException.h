#pragma once
/**
@file InvalidCodeLogicException.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Exception.h"
#include "swCommonLib/System/Path.h"


namespace sw
{

class InvalidCodeLogicException;
DEFINE_PTR_TYPE( InvalidCodeLogicException );



/**@brief Exception thrown when code reaches state, that it shouldn't reach.
It indicates, that something is wrong in program logic.
@ingroup Helpers*/
class InvalidCodeLogicException : public RuntimeException
{
	RTTR_ENABLE( RuntimeException );
private:
protected:

	std::string				m_path;
	uint32					m_line;

public:
	explicit		InvalidCodeLogicException		( std::string message, std::string filePath, uint32 line );
	virtual			~InvalidCodeLogicException		() = default;

public:

	virtual std::string			ErrorMessage		() const;

public:

	static InvalidCodeLogicExceptionPtr		Create		( std::string message, std::string filePath, uint32 line );
};




}	// sw

