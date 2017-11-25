#pragma once
/**
@file IValueConverter.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Engine.
*/


namespace sw {
namespace gui
{

/**@defgroup BindingConversions
@ingroup DataBindingSystem*/


/**@brief Class converts bound values to proper type.

@todo Add interface functions and implement conversion in data binding.

@ingroup DataBindingSystem
@ingroup BindingConversions*/
class IValueConverter
{
private:
protected:
public:
	explicit		IValueConverter		() = default;
	virtual			~IValueConverter	() = default;

};




}	// gui
}	// sw

