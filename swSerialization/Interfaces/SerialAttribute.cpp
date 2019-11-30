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
    return std::optional<std::string_view>();
}

// ================================ //
//
std::optional< double >                     SerialAttribute::ConvertToDouble        () const
{
    return std::optional<double>();
}

// ================================ //
//
std::optional< uint64 >                     SerialAttribute::ConvertToUInt64        () const
{
    return std::optional<uint64>();
}

// ================================ //
//
std::optional< int64 >                      SerialAttribute::ConvertToInt64         () const
{
    return std::optional<int64>();
}

// ================================ //
//
std::optional< uint32 >                     SerialAttribute::ConvertToUInt32        () const
{
    return std::optional<uint32>();
}

// ================================ //
//
std::optional< int32 >                      SerialAttribute::ConvertToInt32         () const
{
    return std::optional<int32>();
}

// ================================ //
//
std::optional< uint16 >                     SerialAttribute::ConvertToUInt16        () const
{
    return std::optional<uint16>();
}

// ================================ //
//
std::optional< int16 >                      SerialAttribute::ConvertToInt16         () const
{
    return std::optional<int16>();
}

// ================================ //
//
std::optional< uint8 >                      SerialAttribute::ConvertToUInt8         () const
{
    return std::optional<uint8>();
}

// ================================ //
//
std::optional< int8 >                       SerialAttribute::ConvertToInt8          () const
{
    return std::optional<int8>();
}

// ================================ //
//
std::optional< bool >                       SerialAttribute::ConvertToBool          () const
{
    return std::optional<bool>();
}

// ================================ //
//
std::optional< char >                       SerialAttribute::ConvertToChar          () const
{
    return std::optional<char>();
}

}	// sw