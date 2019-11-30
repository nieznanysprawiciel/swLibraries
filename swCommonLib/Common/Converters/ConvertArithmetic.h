#pragma once
/**
@file ConvertArithmetic.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include <string_view>
#include <charconv>


namespace impl
{

// ================================ //
//
template< typename ElementType >
inline sw::Nullable< ElementType >      ConvertArithmetic   ( std::string_view str )
{
    ElementType value;

    auto [ lastChar, error ] = std::from_chars( str.data(), str.data() + str.size(), value );

    // Check if conversion was succesfull.
    ///< @todo We could return fail reason here. Consider this in future.
    if( error != std::errc() )
        return ::impl::ConversionException();

    // Whole string should be processed. std::from_chars could parse only part of string.
    if( lastChar != str.data() + str.size() )
        return ::impl::ConversionException();

    return value;
}

// ================================ //
//
template<>
inline sw::Nullable< bool >             ConvertArithmetic   ( std::string_view str )
{
    using namespace std::literals;

    std::string_view trueString = "true"sv;
    std::string_view falseString = "false"sv;

    if( str == trueString )
        return true;

    if( str == falseString )
        return false;

    return ::impl::ConversionException();
}

}	// impl




