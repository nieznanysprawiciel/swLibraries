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
                                !std::is_arithmetic< Type >::value;
};


// ================================ //
//
template< typename SrcType, typename DstType >
struct at_least_one_boolean
{
    static const bool value = std::is_same< SrcType, bool >::value || std::is_same< DstType, bool >::value;
};

// ================================ //
//
template< typename SrcType, typename DstType >
struct both_arithmetic
{
    static const bool value = std::is_arithmetic< SrcType >::value && std::is_arithmetic< DstType >::value &&
        !at_least_one_boolean< SrcType, DstType >::value;
};


