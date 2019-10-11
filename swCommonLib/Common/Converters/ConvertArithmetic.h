#pragma once
/**
@file ConvertArithmetic.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include <stdlib.h>


namespace impl
{

// ================================ //
//
template< typename ElementType >
inline bool         IsCorrectSign                           ( const std::string& str )
{
    if( str.size() > 1 )
        return str[ 0 ] != '-';
    return true;
}

// ================================ //
//
template<> inline bool  IsCorrectSign< int64 >              ( const std::string& str )  { return true; }
template<> inline bool  IsCorrectSign< int32 >              ( const std::string& str )  { return true; }
template<> inline bool  IsCorrectSign< int16 >              ( const std::string& str )  { return true; }
template<> inline bool  IsCorrectSign< int8 >               ( const std::string& str )  { return true; }
template<> inline bool  IsCorrectSign< float >              ( const std::string& str )  { return true; }
template<> inline bool  IsCorrectSign< double >             ( const std::string& str )  { return true; }



/**@brief Converts string to numeric types. Uses strol function from std.*/
template< typename ElementType >
inline ElementType  ConvertArithmeticImpl   			    ( const char* valueBegin, char** checkEndPtr )
{
    assert( false );
    return false;
}


// ================================ //
//
template<>
inline uint32		ConvertArithmeticImpl< uint32 >         ( const char* valueBegin, char** checkEndPtr )
{
    return strtoul( valueBegin, checkEndPtr, 10 );
}

// ================================ //
//
template<>
inline int32		ConvertArithmeticImpl< int32 >          ( const char* valueBegin, char** checkEndPtr )
{
    return strtol( valueBegin, checkEndPtr, 10 );
}

// ================================ //
//
template<>
inline uint64		ConvertArithmeticImpl< uint64 >         ( const char* valueBegin, char** checkEndPtr )
{
    return strtoull( valueBegin, checkEndPtr, 10 );
}

// ================================ //
//
template<>
inline int64		ConvertArithmeticImpl< int64 >          ( const char* valueBegin, char** checkEndPtr )
{
    return strtoll( valueBegin, checkEndPtr, 10 );
}


// ================================ //
//
template<>
inline bool			ConvertArithmeticImpl< bool >           ( const char* valueBegin, char** checkEndPtr )
{
    const char* trueString = "true";
    const char* falseString = "false";

    *checkEndPtr = const_cast< char* >( valueBegin );
    const char* referenceString;
    bool returnValue;

    if( **checkEndPtr == 't' )
    {
        returnValue = true;
        referenceString = trueString;
    }
    else if( **checkEndPtr == 'f' )
    {
        returnValue = false;
        referenceString = falseString;
    }
    else
        return false;

    int i = 0;
    do
    {
        ++i;
        *checkEndPtr += 1;
    } while( **checkEndPtr == *( referenceString + i ) && **checkEndPtr != '\0' );

    return returnValue;
}

// ================================ //
//
template<>
inline double		ConvertArithmeticImpl< double >         ( const char* valueBegin, char** checkEndPtr )
{
    return strtod( valueBegin, checkEndPtr );
}

// ================================ //
//
template<>
inline float		ConvertArithmeticImpl< float >          ( const char* valueBegin, char** checkEndPtr )
{
    return (float)ConvertArithmeticImpl< double >( valueBegin, checkEndPtr );
}

// ================================ //
//
template< typename ElementType >
inline sw::Nullable< ElementType >      ConvertArithmetic   ( const std::string& str )
{
    // strto** functions can't handle negative numbers.
    if( !IsCorrectSign< ElementType >( str ) )
        return ::impl::ConversionException();

    const char* attribValue = str.c_str();
    char* checkEndPtr = nullptr;	        // After conversion we will get here pointer to byte after last parsed element.

    errno = 0;	                            // strto** functions can return ERANGE if value will be out of range.

    auto value = ConvertArithmeticImpl< ElementType >( attribValue, &checkEndPtr );
    auto errnoVal = errno;

    if( checkEndPtr == attribValue ||       // If we are on the begining, no conversion was performed.
        *checkEndPtr != '\0' ||             // If we didn't reached terminator character, this means error.
        errno == ERANGE )
        return ::impl::ConversionException();

    // Max value for type indicates coversion error. But not for bool.
    if( value == std::numeric_limits< ElementType >::max() &&
        !std::is_same< ElementType, bool >::value )
        return ::impl::ConversionException();

    return value;
}

}	// impl




