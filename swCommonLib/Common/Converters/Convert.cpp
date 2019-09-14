/**
@file Convert.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "Convert.h"



namespace impl
{

/**@brief Exception returned when conversion fails.

This is hack to avoid allocating new exception each time conversion fails.
Other solution would be to return std::optional when we move to c++17.*/
auto conversionException = std::make_shared< sw::RuntimeException >( "Conversion between types failed." );

// ================================ //
//
sw::ExceptionPtr        ConversionException     ()
{
    return std::static_pointer_cast< sw::Exception >( conversionException );
}

}

