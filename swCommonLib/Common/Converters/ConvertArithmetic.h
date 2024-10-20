#pragma once
/**
@file ConvertArithmetic.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include <string_view>
#include <charconv>
#include <limits>


namespace sw::impl
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
        return ConversionException();

    // Whole string should be processed. std::from_chars could parse only part of string.
    if( lastChar != str.data() + str.size() )
        return ConversionException();

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

    return ConversionException();
}



// ================================ //
//
template< typename Type >
struct GetUnsigned
{
    typedef typename std::make_unsigned< Type >::type type;
};

// ================================ //
//
template<>
struct GetUnsigned< double >
{
    typedef double type;
};

// ================================ //
//
template<>
struct GetUnsigned< float >
{
    typedef float type;
};


// ================================ //
// Based on https://stackoverflow.com/questions/18625964/checking-if-an-input-is-within-its-range-of-limits-in-c
template< typename RangeType, typename ValueType,
typename std::enable_if< 
    std::numeric_limits< RangeType >::is_signed == std::numeric_limits< ValueType >::is_signed &&
    std::numeric_limits< RangeType >::is_integer,    
    void* >::type = nullptr >
bool                                IsInRange               ( ValueType value )
{
    return value >= std::numeric_limits< RangeType >::min() && value <= std::numeric_limits< RangeType >::max();
}

// ================================ //
//
template< typename RangeType, typename ValueType,
typename std::enable_if<
    std::numeric_limits< RangeType >::is_signed &&
    !std::numeric_limits< ValueType >::is_signed &&
    std::numeric_limits< RangeType >::is_integer,
    void* >::type = nullptr >
bool                                IsInRange               ( ValueType value )
{
    typedef GetUnsigned< ValueType >::type UnsignedType;
    return value <= static_cast< UnsignedType >( std::numeric_limits< RangeType >::max() );
}

// ================================ //
//
template< typename RangeType, typename ValueType,
typename std::enable_if<
    std::numeric_limits< ValueType >::is_signed &&
    !std::numeric_limits< RangeType >::is_signed &&
    std::numeric_limits< RangeType >::is_integer,
    void* >::type = nullptr >
bool                                IsInRange               ( ValueType value )
{
    typedef GetUnsigned< ValueType >::type UnsignedType;
    return value >= 0 && static_cast< UnsignedType >( value ) <= std::numeric_limits< RangeType >::max();
}

// ================================ //
//
template< typename RangeType, typename ValueType,
typename std::enable_if<
    !std::numeric_limits< RangeType >::is_integer &&
    std::numeric_limits< ValueType >::is_signed,
    void* >::type = nullptr >
bool                                IsInRange               ( ValueType value )
{
    return ( value > 0 ? value : -value ) <= std::numeric_limits< RangeType >::max();
}

// ================================ //
//
template< typename RangeType, typename ValueType,
    typename std::enable_if<
    !std::numeric_limits< RangeType >::is_integer &&
    !std::numeric_limits< ValueType >::is_signed,
    void* >::type = nullptr >
    bool                                IsInRange               ( ValueType value )
{
    return value <= std::numeric_limits< RangeType >::max();
}


//// ================================ //
//// https://stackoverflow.com/questions/18625964/checking-if-an-input-is-within-its-range-of-limits-in-c
//template< typename RangeType, typename ValueType >
//bool                                IsInRange               ( ValueType value )
//{
//    if( !std::numeric_limits< RangeType >::is_integer )
//    {
//        return ( value > 0 ? value : -value ) <= std::numeric_limits< RangeType >::max();
//    }
//
//    if( std::numeric_limits< RangeType >::is_signed ==
//        std::numeric_limits< ValueType >::is_signed )
//    {
//        return value >= std::numeric_limits< RangeType >::min() &&
//            value <= std::numeric_limits< RangeType >::max();
//    }
//    else if( std::numeric_limits< RangeType >::is_signed )
//    {
//        return value <= std::numeric_limits< RangeType >::max();
//    }
//    else
//    {
//        return value >= 0 && value <= std::numeric_limits< RangeType >::max();
//    }
//}

// ================================ //
//
template< typename SrcType, typename DstType >
bool                                WillTruncate            ( SrcType val )
{
    if( !std::numeric_limits< SrcType >::is_integer )
    {
        // Check if rounding loses precision.
        if( ceil( val ) == val )
            return false;
        return true;
    }

    return false;
}

}	// impl




// ================================ //
//
template< typename SrcType, typename DstType >
inline sw::Result< typename std::enable_if< both_arithmetic< SrcType, DstType >::value, DstType >::type, ConversionError >
                                        Convert::FromTo     ( const SrcType& val )
{
    if( sw::impl::WillTruncate< SrcType, DstType >( val ) )
        return ConversionError::FloatTruncation;

    if( !sw::impl::IsInRange< DstType, SrcType >( val ) )
        return ConversionError::OutOfRange;

    return static_cast< DstType >( val );
}

// ================================ //
//
template< typename SrcType, typename DstType >
inline sw::Result< typename std::enable_if< is_one_boolean< SrcType, DstType >::value, DstType >::type, ConversionError >
                                        Convert::FromTo     ( const SrcType& val )
{
    return ConversionError::NotConvertible;
}


