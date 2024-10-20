/**
@file Convert.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



// Supress deprecation warning. We nned to remember to use
// replacement in future when it will be introduced in standard.
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING


#include "Convert.h"

#include <codecvt>


namespace sw::impl
{

// ================================ //
//
sw::ExceptionPtr        ConversionException     ()
{
    /**@brief Exception returned when conversion fails.

    This is hack to avoid allocating new exception each time conversion fails.
    Other solution would be to return std::optional when we move to c++17.*/
    static auto conversionException = std::make_shared< sw::RuntimeException >( "Conversion between types failed." );

    return std::static_pointer_cast< sw::Exception >( conversionException );
}

// ================================ //
//
std::string             ConvertWstringToString  ( const std::wstring& value )
{
    typedef std::codecvt_utf8< wchar_t > convert_type;
    std::wstring_convert< convert_type, wchar_t > converter;
    return converter.to_bytes( value );
}

// ================================ //
//
std::wstring            ConvertStringToWstring  ( std::string_view value )
{
    typedef std::codecvt_utf8< wchar_t > convert_type;
    std::wstring_convert< convert_type, wchar_t > converter;
    return converter.from_bytes( value.data(), value.data() + value.size() );
}

}   // impl

