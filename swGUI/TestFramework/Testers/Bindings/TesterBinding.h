#pragma once

#include "swGUI/Core/System/DataBinding/Binding.h"


namespace sw {
namespace gui
{

// ================================ //
//
class CLASS_TESTER( Binding )
{
protected:

	Nullable< void >	ValidateBinding			( Binding& binding, TypeID srcType, TypeID targetType )
	{
		return binding.ValidateBinding( srcType, targetType );
	}

};


}	// gui
}	// sw

