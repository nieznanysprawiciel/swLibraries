#pragma once
/**
@file IValueConverter.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Engine.
*/


#include "swCommonLib/Common/RTTR.h"

#include "swGUI/Core/Cultures/CultureInfo.h"


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


	virtual rttr::variant			Convert			( const rttr::variant& object, TypeID targetType, const rttr::variant& params, const CultureInfo* culture ) const = 0;
	virtual rttr::variant			ConvertBack		( const rttr::variant& object, TypeID targetType, const rttr::variant& params, const CultureInfo* culture ) const = 0;

	/**@brief Should return true if conversion to type is valid.*/
	virtual bool					CanConvert		( TypeID srcType, TypeID targetType ) const = 0;

	/**@brief Should return true if conversion to type is valid.*/
	virtual bool					CanConvertBack	( TypeID srcType,TypeID targetType ) const = 0;
};




}	// gui
}	// sw

