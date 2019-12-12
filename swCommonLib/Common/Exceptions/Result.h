#pragma once
/**
@file Result.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Exception.h"


namespace sw
{




namespace impl
{

// ================================ //
//	
template< typename From, typename To >
struct IsBaseConversion
{
    // ================================ //
    // Note: Visual Studio can't handle constexpr functions in std::enable_if
    static constexpr inline bool		Value		()
    {
        using DecayedFrom = std::remove_pointer< typename From >::type;
        using DecayedTo = std::remove_pointer< typename To >::type;

        return	!std::is_same< DecayedFrom, DecayedTo >::value &&
            std::is_base_of< DecayedTo, DecayedFrom >::value;// &&
        std::is_pointer< From >::value&&
            std::is_pointer< To >::value;
    }

public:

    const static bool value = IsBaseConversion::Value();
};


// ================================ //
/// Converts ErrorType to string message and ExceptionPtr.
/// Used by Result class.
/// @attention Default implementation needs Convert::ToString implemented for enum.
template< typename ErrorType >
struct ErrorToException
{
    static std::string          ErrorMessage        ( const ErrorType& error );
    static ExceptionPtr         ExceptionPointer    ( const ErrorType& error );
};

// ================================ //
//
template< typename ErrorType >
inline std::string          ErrorToException< ErrorType >::ErrorMessage     ( const ErrorType& error )
{
    return Convert::ToString( error );
}

// ================================ //
/// Create RuntimeException with ErrorMessage by default.
template< typename ErrorType >
inline ExceptionPtr         ErrorToException< ErrorType >::ExceptionPointer ( const ErrorType& error )
{
    return std::make_shared< RuntimeException >( ErrorToException::ErrorMessage( error ) );
}

}	// impl



/**@brief Lightweight version of Nullable, which can return error code instead of ExceptionPtr.

This class doesn't need memory allocation for exception, thats why it should be used
in code requiring high performance.

@todo We should merge Result with Nullable in the future, by making single template
with specializations. Class should be named Result. Nullable doesn't tell reader
about real purpose of class.

@todo Result should be easly converted to Nullable. Ensure that all helper utilities functions
working with Nullable work with Result too.

@ingroup Exceptions*/
template< typename ContentType, typename ErrorType >
class Result
{
protected:
    union
    {
        ContentType			Content;
        ErrorType			Error;
    };

    bool					m_isValid;

public:
    explicit                Result              ();
                            Result			    ( ContentType&& content );
                            Result			    ( const ContentType& content );
                            Result			    ( const ErrorType& error );
                            Result			    ( const Result< ContentType, ErrorType >& that );
                            ~Result			    ();

    template< typename DerivedClass, typename std::enable_if< impl::IsBaseConversion< DerivedClass, ContentType >::value >::type * = nullptr >
                            Result			    ( Result< DerivedClass, ErrorType >&& other );

public:

    bool                    IsValid             () const;
    std::string             GetErrorReason      () const;
    ErrorType				GetError            () const;

    bool						            operator==      ( const ContentType& that );
    bool						            operator!=      ( const ContentType& that );
    Result< ContentType, ErrorType >&       operator=       ( const Result< ContentType, ErrorType >& that );

    const ContentType&          Get			    () const &;
    operator const ContentType&                 () const &;

    ContentType&                Get			    () &;
    operator ContentType&                       () &;

    ContentType&&               Get			    () &&;
    operator ContentType&&                      () && = delete;

public:

};



// ========================================================================= //
// Implementation
// ========================================================================= //

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline Result< ContentType, ErrorType >::Result        ()
    : m_isValid( false )
    , Error( nullptr )
{}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline Result< ContentType, ErrorType >::Result         ( ContentType&& content )
    : m_isValid( true ), Content( std::move( content ) )
{}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline Result< ContentType, ErrorType >::Result			( const ContentType& content )
    : m_isValid( true ), Content( content )
{}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline Result< ContentType, ErrorType >::Result			( const ErrorType& error )
    : m_isValid( false ), Error( error )
{}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline Result< ContentType, ErrorType >::Result			( const Result< ContentType, ErrorType >& that )
    : m_isValid( that.m_isValid )
{
    if( m_isValid )
        new( &Content ) ContentType( that.Content );
    else
        new( &Error ) ErrorType( that.Error );
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
template< typename DerivedClass, typename std::enable_if< impl::IsBaseConversion< DerivedClass, ContentType >::value >::type* >
inline Result< ContentType, ErrorType >::Result			( Result< DerivedClass, ErrorType >&& other )
    : m_isValid( other.IsValid() )
    , Error( nullptr )
{
    if( m_isValid )
        Content = std::move( other ).Get();
    else
        Error = other.GetError();
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline Result< ContentType, ErrorType >::~Result       ()
{
    if( m_isValid )
        Content.~ContentType();
    else
        Error.~ErrorType();
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline bool						Result< ContentType, ErrorType >::IsValid		    () const
{
    return m_isValid;
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline std::string				Result< ContentType, ErrorType >::GetErrorReason    () const
{
    if( m_isValid )
        throw RuntimeException( "Called GetErrorReason on valid Result." );
    return impl::ErrorToException< ErrorType >::ErrorMessage( Error );
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline typename ErrorType		Result< ContentType, ErrorType >::GetError          () const
{
    if( m_isValid )
        throw RuntimeException( "Called GetError on valid Result." );
    return Error;
}


// ================================ //
//
template< typename ContentType, typename ErrorType >
inline bool						Result< ContentType, ErrorType >::operator==      ( const ContentType& that )
{
    return m_isValid && Content == that;
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline bool						Result< ContentType, ErrorType >::operator!=      ( const ContentType& that )
{
    return !( *this == that );
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
Result< ContentType, ErrorType >&       Result< ContentType, ErrorType >::operator=		( const Result< ContentType, ErrorType >& that )
{
    if( m_isValid )
        Content.~ContentType();
    else
        Error.~ErrorType();

    m_isValid = that.m_isValid;

    if( m_isValid )
        new( &Content ) ContentType( that.Content );
    else
        new( &Error ) ErrorType( that.Error );

    return *this;
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline const ContentType&               Result< ContentType, ErrorType >::Get          () const&
{
    if( !m_isValid )
        throw RuntimeException( impl::ErrorToException< ErrorType >::ErrorMessage( Error ) );
    return Content;
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ContentType&                     Result< ContentType, ErrorType >::Get          () &
{
    if( !m_isValid )
    {
        // Note: we lose exception type information, but throw statement copies
        // exception and we can't copy polymorphic type, so this is best option at least for now.
        /// @todo We should rethink exceptions handling in future.
        throw RuntimeException( impl::ErrorToException< ErrorType >::ErrorMessage( Error ) );
    }
    return Content;
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ContentType&&                    Result< ContentType, ErrorType >::Get          () &&
{
    if( !m_isValid )
        throw RuntimeException( impl::ErrorToException< ErrorType >::ErrorMessage( Error ) );
    return std::move( Content );
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline Result< ContentType, ErrorType >::operator const ContentType&                    () const&
{
    return Get();
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline Result< ContentType, ErrorType >::operator ContentType&                          ()&
{
    return Get();
}

}	// sw



