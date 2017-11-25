#pragma once


#include "swCommonLib/Common/TypesDefinitions.h"


namespace sw {
namespace gui
{


/**@brief Binding modes enumaration
@ingroup DataBindingSystem*/
enum class BindingMode : uint8
{
	OneWay,
	TwoWay,
	OneWayToSource,
	OneTime,

	Total
};

/**@brief What causes bound property to update.

Check WPF documentation for details.

@ingroup DataBindingSystem*/
enum class UpdateSourceTrigger : uint8
{
	Default,
	PropertyChanged,
	LostFocus,
	Explicit,

	Total
};

}	// gui
}	// sw
