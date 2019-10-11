#pragma once
/**
@file ForEach.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



namespace sw
{

// ============================================================================== //
// Implements FOR_EACH macros for use in combination with other macros.
// https://stackoverflow.com/questions/1872220/is-it-possible-to-iterate-over-arguments-in-variadic-macros


#define EXPAND( ... ) __VA_ARGS__

#define _FOR_EACH_1(WHAT, X) WHAT(X) 
#define _FOR_EACH_2(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_1(WHAT, __VA_ARGS__) )
#define _FOR_EACH_3(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_2(WHAT, __VA_ARGS__) )
#define _FOR_EACH_4(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_3(WHAT, __VA_ARGS__) )
#define _FOR_EACH_5(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_4(WHAT, __VA_ARGS__) )
#define _FOR_EACH_6(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_5(WHAT, __VA_ARGS__) )
#define _FOR_EACH_7(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_6(WHAT, __VA_ARGS__) )
#define _FOR_EACH_8(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_7(WHAT, __VA_ARGS__) )
#define _FOR_EACH_9(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_8(WHAT, __VA_ARGS__) )
#define _FOR_EACH_10(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_9(WHAT, __VA_ARGS__) )
#define _FOR_EACH_11(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_10(WHAT, __VA_ARGS__) )
#define _FOR_EACH_12(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_11(WHAT, __VA_ARGS__) )
#define _FOR_EACH_13(WHAT, X, ...) WHAT(X), EXPAND( _FOR_EACH_12(WHAT, __VA_ARGS__) )
//... repeat as needed

#define _CHOOSE_FOR_EACH(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,NAME,...) NAME 
#define FOR_EACH( action, ... ) \
    EXPAND( _CHOOSE_FOR_EACH( __VA_ARGS__,   \
             _FOR_EACH_13,  \
             _FOR_EACH_12,  \
             _FOR_EACH_11,  \
             _FOR_EACH_10,  \
             _FOR_EACH_9,   \
             _FOR_EACH_8,   \
             _FOR_EACH_7,   \
             _FOR_EACH_6,   \
             _FOR_EACH_5,   \
             _FOR_EACH_4,   \
             _FOR_EACH_3,   \
             _FOR_EACH_2,   \
             _FOR_EACH_1, )(action,__VA_ARGS__) )



}	// sw

