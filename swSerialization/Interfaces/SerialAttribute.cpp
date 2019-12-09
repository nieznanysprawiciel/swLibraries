/**
@file SerialAttribute.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "SerialAttribute.h"


namespace sw
{

// ================================ //
//
std::optional< std::string_view >           SerialAttribute::ConvertToString        () const
{
    return ConvertTo< std::string_view >();
}

// ================================ //
//
std::optional< double >                     SerialAttribute::ConvertToDouble        () const
{
    return ConvertTo< double >();
}

// ================================ //
//
std::optional< uint64 >                     SerialAttribute::ConvertToUInt64        () const
{
    return ConvertTo< uint64 >();
}

// ================================ //
//
std::optional< int64 >                      SerialAttribute::ConvertToInt64         () const
{
    return ConvertTo< int64 >();
}

// ================================ //
//
std::optional< uint32 >                     SerialAttribute::ConvertToUInt32        () const
{
    return ConvertTo< uint32 >();
}

// ================================ //
//
std::optional< int32 >                      SerialAttribute::ConvertToInt32         () const
{
    return ConvertTo< int32 >();
}

// ================================ //
//
std::optional< uint16 >                     SerialAttribute::ConvertToUInt16        () const
{
    return ConvertTo< uint16 >();
}

// ================================ //
//
std::optional< int16 >                      SerialAttribute::ConvertToInt16         () const
{
    return ConvertTo< int16 >();
}

// ================================ //
//
std::optional< uint8 >                      SerialAttribute::ConvertToUInt8         () const
{
    return ConvertTo< uint8 >();
}

// ================================ //
//
std::optional< int8 >                       SerialAttribute::ConvertToInt8          () const
{
    return ConvertTo< int8 >();
}

// ================================ //
//
std::optional< bool >                       SerialAttribute::ConvertToBool          () const
{
    return ConvertTo< bool >();
}

// ================================ //
//
std::optional< char >                       SerialAttribute::ConvertToChar          () const
{
    return ConvertTo< char >();
}

}	// sw