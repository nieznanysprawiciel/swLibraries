#pragma once
/**
@file ConvertTraits.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <type_traits>

#include <string>



template< typename Type >
struct is_not_specialized
{
    static const bool value =   !std::is_enum< Type >::value &&
                                !std::is_same< Type, std::wstring >::value &&
                                !std::is_arithmetic< Type >::value;
};
