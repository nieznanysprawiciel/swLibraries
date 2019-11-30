#pragma once
/**
@file SerialAttribute.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "SerialGeneric.h"

#include "ISerializer.h"

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
protected:
public:
    explicit		SerialAttribute     ( sw::ISerializer* ser, impl::NodePointer nodeInternal )
        : impl::SerialBase( ser, nodeInternal )
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
};



}	// sw

