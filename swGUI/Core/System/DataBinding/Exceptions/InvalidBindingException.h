#pragma once
/**
@file InvalidBindingException.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Common/Exceptions/Exception.h"



namespace sw {
namespace gui
{

/**@defgroup BindingExceptions
@ingroup DataBindingSystem*/


/**@brief Exceptions tells that two types cannot be bound.
@ingroup BindingExceptions*/
class InvalidBindingException : public Exception
{
private:
protected:

	TypeID			m_sourceType;
	TypeID			m_targetType;

public:
	explicit		InvalidBindingException		( TypeID src, TypeID dst );
	virtual			~InvalidBindingException	() = default;

	std::string		ErrorMessage				() const override;
};


}	// gui
}	// sw

