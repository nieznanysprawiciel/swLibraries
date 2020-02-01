#pragma once
/**
@file VariantWrapper.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/RTTR.h"

#include <variant>


namespace sw
{


/**@brief Holds new rttr::variant value or previous value got from property or array.

Deserialization functions can deserialize objects in place or create and return
new instances. This wrapper can hold both values and distinguish between them
while setting properties.

@Note: reason of this class is not optimalization, but it was forced by unsolvable
problems with comparing rttr::variants. If we compare two rttr::variants holding
reference wrappers, rttr tries to compare structures not references.
So we can't know, that object is equal to previous value.*/
class VariantWrapper
{
    typedef std::reference_wrapper< rttr::variant > VariantRef;
private:

    std::variant< rttr::variant, VariantRef >   m_value;

private:

    explicit    VariantWrapper          ( rttr::variant newValue )
        : m_value( std::move( newValue ) ) {}

    explicit    VariantWrapper          ( VariantRef prevValue )
        : m_value( prevValue ) {}

public:

    bool                        IsPrevious      () const { return !std::holds_alternative< rttr::variant >( m_value ); }
    bool                        IsNew           () const { return std::holds_alternative< rttr::variant >( m_value ); }

    rttr::variant&              GetNew          () { return std::get< rttr::variant >( m_value ); }
    VariantRef                  GetPrevious     () { return std::get< VariantRef >( m_value ); }

public:

    /**@note rttr::variant must be moved. We don't want to copy types.*/
    static VariantWrapper      FromNew         ( rttr::variant&& newValue );
    static VariantWrapper      FromPrevious    ( rttr::variant& prevValue );
};


//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline VariantWrapper           VariantWrapper::FromNew          ( rttr::variant&& newValue )
{
    return VariantWrapper( std::move( newValue ) );
}

// ================================ //
//
inline VariantWrapper           VariantWrapper::FromPrevious    ( rttr::variant& prevValue )
{
    return VariantWrapper( std::reference_wrapper< rttr::variant >( prevValue ) );
}

}	// sw


