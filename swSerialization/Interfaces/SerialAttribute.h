#pragma once
/**
@file SerialAttribute.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "SerialGeneric.h"

#include "ISerializer.h"

#include "swCommonLib/Common/Converters/Convert.h"

#include <string_view>
#include <optional>


namespace sw
{

/**@brief Represents attribute serialization primitive.
It is one of primitive types: string, number, bool.
@ingroup Serialization*/
class SerialAttribute : public impl::SerialBase
{
private:

    SerialType          m_type;

protected:
public:
    explicit		SerialAttribute     ( sw::ISerializer* ser, impl::NodePointer nodeInternal, SerialType type )
        : impl::SerialBase( ser, nodeInternal )
        , m_type( type )
    {}
                    ~SerialAttribute	() = default;
public:

    ///@name Attribute query functions
    /// Functions return converted attribute or empty optional if conversion fails.
    /// Note that not only type matters, but variables range is checked either.
    /// Functions guarantee, that if conversion didn't fail, no information is lost.
    ///@{
    std::optional< std::string_view >           ConvertToString         () const;

    std::optional< double >                     ConvertToDouble         () const;
    std::optional< uint64 >                     ConvertToUInt64         () const;
    std::optional< int64 >                      ConvertToInt64          () const;
    std::optional< uint32 >                     ConvertToUInt32         () const;
    std::optional< int32 >                      ConvertToInt32          () const;
    std::optional< uint16 >                     ConvertToUInt16         () const;
    std::optional< int16 >                      ConvertToInt16          () const;
    std::optional< uint8 >                      ConvertToUInt8          () const;
    std::optional< int8 >                       ConvertToInt8           () const;

    std::optional< bool >                       ConvertToBool           () const;
    std::optional< char >                       ConvertToChar           () const;

    /**@brief Converts to templated type.
    Function can convert to types listed above. It is usefull in templated code.*/
    template< typename TargetType >
    std::optional< TargetType >                 ConvertTo               () const;
    ///@}

private:

    template< typename TargetType >
    std::optional< TargetType >                 Convert                 ( std::string_view src ) const;

    template< typename SourceType, typename TargetType >
    std::optional< TargetType >                 Convert                 ( const SourceType& src ) const;
};


// ================================ //
//
template< typename TargetType >
inline std::optional< TargetType >              SerialAttribute::ConvertTo      () const
{
    switch( m_type )
    {
    case sw::String:
        return Convert< TargetType >( m_serializer->GetString( *this ) );
    case sw::Bool:
        return Convert< bool, TargetType >( m_serializer->GetBool( *this ) );
    case sw::UInt64:
        return Convert< uint64, TargetType >( m_serializer->GetUInt64( *this ) );
    case sw::Int64:
        return Convert< int64, TargetType >( m_serializer->GetInt64( *this ) );
    case sw::Double:
        return Convert< double, TargetType >( m_serializer->GetDouble( *this ) );
    default:
        return {};
    }

    return {};
}

// ================================ //
//
template< typename SourceType, typename TargetType >
inline std::optional< TargetType >              SerialAttribute::Convert        ( const SourceType& src ) const
{
    auto result = Convert::FromTo< SourceType, TargetType >( src );
    if( !result.IsValid() )
        return {};

    return result.Get();
}

// ================================ //
//
template< typename TargetType >
inline std::optional< TargetType >              SerialAttribute::Convert        ( std::string_view src ) const
{
    auto result = Convert::FromString< TargetType >( src );
    if( !result.IsValid() )
        return {};

    return result.Get();
}

}	// sw

