#pragma once
/**
@file ConvertTraits.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <type_traits>

#include <string>



// ================================ //
//
template< typename Type >
struct is_not_specialized
{
    static const bool value =   !std::is_enum< Type >::value &&
                                !std::is_same< Type, std::wstring >::value &&
                                !std::is_arithmetic< Type >::value &&
                                !std::is_same< Type, std::string_view >::value;
};


// ================================ //
//
template< typename SrcType, typename DstType >
struct is_one_boolean
{
    // At least one value is bool. We don't accept two bools, because we will catch all conversion between
    // the same types with other template.
    // Conversion to std::string_view is not allowed, but it will be caught by other template.
    static const bool value = std::is_same< SrcType, bool >::value != std::is_same< DstType, bool >::value
                           && !std::is_same< DstType, std::string_view >::value;
};

// ================================ //
//
template< typename SrcType, typename DstType >
struct both_arithmetic
{
    // Conversion between the same type will be caught by other template.
    static const bool value = std::is_arithmetic< SrcType >::value
                           && std::is_arithmetic< DstType >::value
                           && !is_one_boolean< SrcType, DstType >::value
                           && !std::is_same< SrcType, DstType >::value;
};


