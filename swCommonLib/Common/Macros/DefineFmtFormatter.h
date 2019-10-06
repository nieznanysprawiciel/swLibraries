#pragma once
/**
@file DefineFmtFormatter.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "ForEach.h"
#include "swCommonLib/Common/fmt.h"


#define _MAKE_STR( x ) #x
#define MAKE_STR( x ) _MAKE_STR( x )

#define _APPEND_INST( member ) d.member


/**@brief Defines formatter for fmt library.
Use this macro outside namespace.*/
#define DEFINE_FMT_FORMATTER( ClassType, FormatString, ... )                \
template<>                                                                  \
struct ::fmt::formatter< ClassType >                                        \
{                                                                           \
    template< typename ParseContext >                                       \
    auto parse( ParseContext& ctx ) { return ctx.begin(); }                 \
                                                                            \
    template< typename FormatContext >                                      \
    auto format( const ClassType& d, FormatContext& ctx ) {                 \
        return format_to( ctx.out(), FormatString, FOR_EACH( _APPEND_INST ,__VA_ARGS__ ) );   \
    }                                                                       \
};


#define _FORMAT_STRING_STRUCT_ENTRY( member )  member={}

#define _FORMAT_STRING_STRUCT( ... )\
[ FOR_EACH( _FORMAT_STRING_STRUCT_ENTRY, __VA_ARGS__ ) ]


/**@brief Defines fmt formatter for structure using default format.*/
#define DEFINE_DEFAULT_FMT_STRUCT_FORMATTER( ClassType, ... )               \
    DEFINE_FMT_FORMATTER( ClassType, MAKE_STR( _FORMAT_STRING_STRUCT( __VA_ARGS__ ) ), __VA_ARGS__ )    


/**@brief Defines formatter for fmt library.
Use this macro outside namespace.*/
#define DEFINE_FMT_FORMATTER_ATOMIC_TYPE( ClassType, Function )             \
template<>                                                                  \
struct ::fmt::formatter< ClassType >                                        \
{                                                                           \
    template< typename ParseContext >                                       \
    auto parse( ParseContext& ctx ) { return ctx.begin(); }                 \
                                                                            \
    template< typename FormatContext >                                      \
    auto format( const ClassType& d, FormatContext& ctx ) {                 \
        return format_to( ctx.out(), "{}", Function( d ) );                 \
    }                                                                       \
};


/**@brief Defines fmt library formatter for enum type. Uses Convert::ToString.
To use formatter for enum, it must be defined in rttr.
Use this macro outside namespace.*/
#define DEFINE_FMT_FORMATTER_ENUM( EnumType )                               \
    DEFINE_FMT_FORMATTER_ATOMIC_TYPE( EnumType, Convert::ToString )

