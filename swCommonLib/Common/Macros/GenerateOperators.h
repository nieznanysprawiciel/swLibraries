#pragma once
/**
@file GenerateOperators.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "ForEach.h"
#include <tuple>


namespace sw
{

#define _APPEND_INSTANCE( instance, member ) instance.member
#define _APPEND_INSTANCE_OBJ1( member ) _APPEND_INSTANCE( obj1, member )
#define _APPEND_INSTANCE_OBJ2( member ) _APPEND_INSTANCE( obj2, member )

#define _GENERATE_OPERATOR( OP, ClassType, ... ) \
inline bool     operator##OP( const ClassType& obj1, const ClassType& obj2 )\
{                                                                           \
    return std::tie( FOR_EACH( _APPEND_INSTANCE_OBJ1, __VA_ARGS__ ) )       \
        OP std::tie( FOR_EACH( _APPEND_INSTANCE_OBJ2, __VA_ARGS__ ) );      \
}

/**@brief Generates operator== function for ClassType.
Pass all class members as variadic parameters.*/
#define GENERATE_EQUAL_OPERATOR( ClassType, ... ) \
    _GENERATE_OPERATOR( ==, ClassType, __VA_ARGS__ )

/**@brief Generates operator!= function for ClassType.
Pass all class members as variadic parameters.*/
#define GENERATE_NON_EQUAL_OPERATOR( ClassType, ... ) \
    _GENERATE_OPERATOR( !=, ClassType, __VA_ARGS__ )

/**@brief Generates operator== and operator!= for ClassType.*/
#define GENERATE_EQUALITY_OPERATORS( ClassType, ... ) \
    _GENERATE_OPERATOR( ==, ClassType, __VA_ARGS__ )  \
    _GENERATE_OPERATOR( !=, ClassType, __VA_ARGS__ )

/**@brief Generates whole family of operators <, <=, >, >= function for ClassType.
Pass all class members as variadic parameters.*/
#define GENERATE_ORDERING_OPERATORS( ClassType, ... ) \
    _GENERATE_OPERATOR( <, ClassType, __VA_ARGS__ )   \
    _GENERATE_OPERATOR( <=, ClassType, __VA_ARGS__ )  \
    _GENERATE_OPERATOR( >, ClassType, __VA_ARGS__ )   \
    _GENERATE_OPERATOR( >=, ClassType, __VA_ARGS__ )

/**@brief Generates all comparision operators.
Pass all class members as variadic parameters.*/
#define GENERATE_RELATIONAL_OPERATORS( ClassType, ... ) \
    GENERATE_ORDERING_OPERATORS( ClassType, ... )       \
    GENERATE_EQUALITY_OPERATORS( ClassType, ... )

}	// sw

