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
struct ErrorAdapter
{
    static std::string          ErrorMessage        ( const ErrorType& error );
    static ExceptionPtr         ExceptionPointer    ( const ErrorType& error );
};

// ================================ //
//
template< typename ErrorType >
inline std::string          ErrorAdapter< ErrorType >::ErrorMessage     ( const ErrorType& error )
{
    return Convert::ToString( error );
}

// ================================ //
/// Create RuntimeException with ErrorMessage by default.
template< typename ErrorType >
inline ExceptionPtr         ErrorAdapter< ErrorType >::ExceptionPointer ( const ErrorType& error )
{
    return std::make_shared< RuntimeException >( ErrorAdapter::ErrorMessage( error ) );
}



/**@brief Base implementation of Result class.*/
template< typename ContentType, typename ErrorType >
class ResultBase
{
protected:
    union
    {
        ContentType			Content;
        ErrorType			Error;
    };

    bool					m_isValid;

public:
    explicit                ResultBase              ();
                            ResultBase			    ( ContentType&& content );
                            ResultBase			    ( const ContentType& content );
                            ResultBase			    ( const ErrorType& error );
                            ResultBase			    ( const ResultBase< ContentType, ErrorType >& that );
                            ~ResultBase			    ();

    template< typename DerivedClass, typename std::enable_if< impl::IsBaseConversion< DerivedClass, ContentType >::value >::type * = nullptr >
                            ResultBase			    ( ResultBase< DerivedClass, ErrorType >&& other );

public:

    bool                    IsValid             () const;
    std::string             GetErrorReason      () const;
    ErrorType				GetError            () const;

    bool						            operator==      ( const ContentType& that );
    bool						            operator!=      ( const ContentType& that );
    ResultBase< ContentType, ErrorType >&   operator=       ( const ResultBase< ContentType, ErrorType >& that );

    const ContentType&          Get			    () const &;
    operator const ContentType&                 () const &;

    ContentType&                Get			    () &;
    operator ContentType&                       () &;

    ContentType&&               Get			    () &&;
    operator ContentType&&                      () && = delete;
};


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
class Result : public impl::ResultBase< ContentType, ErrorType >
{
    typedef impl::ResultBase< ContentType, ErrorType > Parent;
private:
public:

    // Use construtors from base class.
    using           Parent::ResultBase;

public:

    template< typename Type, typename std::enable_if< impl::IsBaseConversion< ContentType, Type >::value, void >::type * = nullptr >
    Result< Type, ErrorType >       Move		    ();
};


namespace impl
{

// ========================================================================= //
// Implementation
// ========================================================================= //

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ResultBase< ContentType, ErrorType >::ResultBase        ()
    : m_isValid( false )
    , Error( nullptr )
{}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ResultBase< ContentType, ErrorType >::ResultBase         ( ContentType&& content )
    : m_isValid( true ), Content( std::move( content ) )
{}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ResultBase< ContentType, ErrorType >::ResultBase			( const ContentType& content )
    : m_isValid( true ), Content( content )
{}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ResultBase< ContentType, ErrorType >::ResultBase			( const ErrorType& error )
    : m_isValid( false ), Error( error )
{}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ResultBase< ContentType, ErrorType >::ResultBase			( const ResultBase< ContentType, ErrorType >& that )
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
inline ResultBase< ContentType, ErrorType >::ResultBase			( ResultBase< DerivedClass, ErrorType >&& other )
    : m_isValid( other.IsValid() )
    , Error( ErrorType() )
{
    if( m_isValid )
        Content = std::move( other ).Get();
    else
        Error = other.GetError();
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ResultBase< ContentType, ErrorType >::~ResultBase       ()
{
    if( m_isValid )
        Content.~ContentType();
    else
        Error.~ErrorType();
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline bool						ResultBase< ContentType, ErrorType >::IsValid		    () const
{
    return m_isValid;
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline std::string				ResultBase< ContentType, ErrorType >::GetErrorReason    () const
{
    if( m_isValid )
        throw RuntimeException( "Called GetErrorReason on valid Result." );
    return impl::ErrorAdapter< ErrorType >::ErrorMessage( Error );
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline typename ErrorType		ResultBase< ContentType, ErrorType >::GetError          () const
{
    if( m_isValid )
        throw RuntimeException( "Called GetError on valid Result." );
    return Error;
}


// ================================ //
//
template< typename ContentType, typename ErrorType >
inline bool						ResultBase< ContentType, ErrorType >::operator==      ( const ContentType& that )
{
    return m_isValid && Content == that;
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline bool						ResultBase< ContentType, ErrorType >::operator!=      ( const ContentType& that )
{
    return !( *this == that );
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
ResultBase< ContentType, ErrorType >& ResultBase< ContentType, ErrorType >::operator=		( const ResultBase< ContentType, ErrorType >& that )
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
inline const ContentType& ResultBase< ContentType, ErrorType >::Get          () const&
{
    if( !m_isValid )
        throw RuntimeException( impl::ErrorAdapter< ErrorType >::ErrorMessage( Error ) );
    return Content;
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ContentType& ResultBase< ContentType, ErrorType >::Get           ()&
{
    if( !m_isValid )
    {
        // Note: we lose exception type information, but throw statement copies
        // exception and we can't copy polymorphic type, so this is best option at least for now.
        /// @todo We should rethink exceptions handling in future.
        throw RuntimeException( impl::ErrorAdapter< ErrorType >::ErrorMessage( Error ) );
    }
    return Content;
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ContentType&& ResultBase< ContentType, ErrorType >::Get          ()&&
{
    if( !m_isValid )
        throw RuntimeException( impl::ErrorAdapter< ErrorType >::ErrorMessage( Error ) );
    return std::move( Content );
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ResultBase< ContentType, ErrorType >::operator const ContentType& () const&
{
    return Get();
}

// ================================ //
//
template< typename ContentType, typename ErrorType >
inline ResultBase< ContentType, ErrorType >::operator ContentType&      ()&
{
    return Get();
}

}   // impl


// ================================ //
//
template< typename ContentType, typename ErrorType >
template< typename Type, typename std::enable_if< impl::IsBaseConversion< ContentType, Type >::value, void >::type* >
inline Result< Type, ErrorType >            Result< ContentType, ErrorType >::Move	()
{
    bool wasValid = IsValid();
    //m_isValid = false;		// We don't change validity. We don't want to call Error destructor on Result destruction.

    if( wasValid )
        return Result< Type, ErrorType >( std::move( Content ) );
    else
        return Result< Type, ErrorType >( std::move( Error ) );
}


}	// sw



