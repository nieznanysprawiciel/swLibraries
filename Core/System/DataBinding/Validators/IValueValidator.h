#pragma once
/**
@file IValueValidator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Engine.
*/


namespace sw {
namespace gui
{

/**@defgroup BindingValidation
@ingroup DataBindingSystem*/


/**@brief Class converts bound values to proper type.

@todo Add interface functions and implement conversion in data binding.

@ingroup DataBindingSystem
@ingroup BindingValidation*/
class IValueValidator
{
private:
protected:
public:
	explicit		IValueValidator		() = default;
	virtual			~IValueValidator	() = default;

};




}	// gui
}	// sw

