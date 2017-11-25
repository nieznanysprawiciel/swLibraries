#pragma once
/**
@file Binding.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Engine.
*/


#include "swCommonLib/Common/RTTR.h"

#include "BindingMode.h"


#include "Converters/IValueConverter.h"
#include "Validators/IValueValidator.h"

#include <string>
#include <vector>



namespace sw {
namespace gui
{


/**@brief Holds information about single binding.
@ingroup DataBindingSystem*/
struct Binding
{
	rttr::property			SourceProperty;
	rttr::variant			SourceObject;
	rttr::property			TargetProperty;
	rttr::variant			TargetObject;

	BindingMode				Mode;
	UpdateSourceTrigger		UpdateTrigger;

	bool					IsEmpty : 1;			///< This Binding object can be empty.
	bool					UseConverter : 1;		
	bool					UseValidation : 1;		///< Optimization: Don't try to access Validator since it can be in another cache line.

	IValueConverter*		Converter;
	IValueValidator*		Validator;
};




}	// gui
}	// sw



