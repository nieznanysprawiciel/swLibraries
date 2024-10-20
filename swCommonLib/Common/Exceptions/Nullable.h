#pragma once
/**
@file Nullable.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Engine.
*/

#include "Exception.h"

#include <exception>
#include <string>
#include <memory>
#include <type_traits>
#include <assert.h>

#include "ResultImpl.h"


namespace sw
{

namespace impl
{

// ================================ //
/// Converts ErrorType to string message and ExceptionPtr.
/// Used by Result class.
/// @attention Default implementation needs Convert::ToString implemented for enum.
template<>
struct ErrorAdapter< ExceptionPtr >
{
    static std::string          ErrorMessage        ( const ExceptionPtr& error );
    static ExceptionPtr         ExceptionPointer    ( const ExceptionPtr& error );
};

// ================================ //
//
inline std::string          ErrorAdapter< ExceptionPtr >::ErrorMessage     ( const ExceptionPtr& error )
{
    return error->ErrorMessage();
}

// ================================ //
/// Create RuntimeException with ErrorMessage by default.
inline ExceptionPtr         ErrorAdapter< ExceptionPtr >::ExceptionPointer ( const ExceptionPtr& error )
{
    return error;
}

}	// impl


/**@brief Enumeration for nullable for creating valid and invalid object.
@ingroup Helpers*/
enum class Success : uint8
{
	True,
	False
};



/**@brief Alexandrescu Expected type for error handling.

@todo Rethink exceptions handling. We can't throw typed exceptions, because
we use std::shared_ptr instead of std::exception_ptr. It's not posible to copy
polymorphic type and throw exception wants to do this.

@todo We should wrap exception throwing inside macro. If exceptions are disabled
we should handle fails different way.

@ingroup Exceptions*/
template< typename ContentType >
class Nullable : public impl::ResultBase< ContentType, ExceptionPtr >
{
public:

	typedef ExceptionPtr ErrorType;
    typedef impl::ResultBase< ContentType, ExceptionPtr > Parent;

protected:
public:

    using                   Parent::ResultBase;

                            Nullable            (const std::string& error);
    template< typename ExceptionType >
                            Nullable            ( std::shared_ptr< ExceptionType >&& error );

public:

    template< typename Type, typename std::enable_if< impl::IsBaseConversion< ContentType, Type >::value, void >::type* = nullptr >
    Nullable< Type >        Move		        ();

public:

    static Nullable			FromError           ( const ErrorType& error );
    static Nullable			FromError           ( const std::string& reason );
    static Nullable			FromError           ();

};


/**@brief Alexandrescu Expected type for error handling.
@ingroup Exceptions*/
template<>
class Nullable< void >
{
public:

	typedef ExceptionPtr ErrorType;

private:

	ErrorType			Error;
	bool				m_isValid;

public:

	explicit                Nullable			();
			                Nullable			( Success result );
                            Nullable			( const ErrorType& error );
							Nullable			( const std::string& error );

	template< typename ExceptionType >
							Nullable			( std::shared_ptr< ExceptionType > error );

    Nullable< void >& operator=			( const Nullable< void >& that );

    bool                    IsValid             () const;
    std::string             GetErrorReason      () const;
    ErrorType				GetError            () const;

    /**@brief If ReturnResult is valid, function forwards onSuccess parameter.
    Otherwise it returns Exception.*/
    template< typename RetType >
    Nullable< RetType >     Ok                  ( RetType&& onSuccess ) const;
};

Nullable< void >            operator&&		    ( const Nullable< void >& that, const Nullable< void >& second );


typedef Nullable< void > ReturnResult;


#define ReturnIfInvalid( nullable )		if( !nullable.IsValid() ) return nullable.GetError();


// ========================================================================= //
// Implementation
// ========================================================================= //

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::Nullable			( const std::string& error )
	: impl::ResultBase< ContentType, ErrorType >( std::static_pointer_cast< Exception >( std::make_shared< RuntimeException >( error ) ) )
{}

// ================================ //
//
template< typename ContentType >
template< typename ExceptionType >
inline Nullable< ContentType >::Nullable            ( std::shared_ptr< ExceptionType >&& error )
    : impl::ResultBase< ContentType, ErrorType >( std::static_pointer_cast< Exception >( std::forward< std::shared_ptr< ExceptionType > >( error ) ) )
{
    static_assert( std::is_base_of< typename ErrorType::element_type, ExceptionType >::value, "ExceptionType should be derived from ErrorType" );
}

// ================================ //
//
template< typename ContentType >
template< typename Type, typename std::enable_if< impl::IsBaseConversion< ContentType, Type >::value, void >::type* >
inline Nullable< Type >            Nullable< ContentType >::Move    ()
{
    bool wasValid = IsValid();
    //m_isValid = false;        // We don't change validity. We don't want to call Error destructor on Nullable destruction.

    if( wasValid )
        return Nullable< Type >( std::move( Content ) );
    else
        return Nullable< Type >( Error );        // Error is shared_ptr, we don't have to move.
}

//====================================================================================//
//			Creating Nullable from error	
//====================================================================================//

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >     Nullable< ContentType >::FromError       ( const ErrorType& error ) 
{ 
    Nullable< ContentType > ret; 
    ret.Error = error; 
    return ret; 
}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >     Nullable< ContentType >::FromError       ( const std::string& reason ) 
{ 
    return FromError( std::make_shared< std::runtime_error >( reason ) ); 
}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >     Nullable< ContentType >::FromError       () 
{ 
    return Nullable< ContentType >(); 
}


//====================================================================================//
//			Specialization for void	
//====================================================================================//


// ================================ //
//
inline Nullable< void >::Nullable			() 
    : m_isValid( false )
    , Error( nullptr ) 
{}

// ================================ //
//
inline Nullable< void >::Nullable			( const ErrorType & error ) 
    : m_isValid( false ), Error( error )
{}

// ================================ //
//
template< typename ExceptionType >
inline Nullable< void >::Nullable			( std::shared_ptr< ExceptionType > error )
	: m_isValid( false ), Error( std::static_pointer_cast< Exception >( error ) )
{
	static_assert( std::is_base_of< typename ErrorType::element_type, ExceptionType >::value, "ExceptionType should be derived from ErrorType" );
}

// ================================ //
//
template< typename RetType >
inline Nullable< RetType >      Nullable< void >::Ok                ( RetType&& onSuccess ) const
{
    if( IsValid() )
        return Nullable< RetType >( std::move( onSuccess ) );
    return Error;
}

// ================================ //
//
inline Nullable< void >::Nullable			( const std::string& error )
	: m_isValid( false ), Error( std::static_pointer_cast< Exception >( std::make_shared< RuntimeException >( error ) ) )
{}

// ================================ //
//
inline Nullable< void >::Nullable			( Success result )
	: m_isValid( result == Success::True ), Error( nullptr )
{}

// ================================ //
//
inline Nullable< void >&        Nullable< void >::operator=         ( const Nullable< void >& that )
{
    m_isValid = that.IsValid();
    Error = that.Error;

    return *this;
}

// ================================ //
//
inline Nullable< void >         operator&&                          ( const Nullable< void >& obj1, const Nullable< void >& obj2 )
{
    if( obj1.IsValid() && obj2.IsValid() )
        return Success::True;

    /// @todo Maybe we should handle situation, when both are errors.
    if( !obj1.IsValid() )
        return obj1.GetError();

    if( !obj2.IsValid() )
        return obj2.GetError();

    return Success::True;
}

// ================================ //
//
inline bool						Nullable< void >::IsValid           () const
{
    return m_isValid;
}

// ================================ //
//
inline std::string				Nullable< void >::GetErrorReason    () const
{
	if( Error )
		return Error->ErrorMessage();
	return "Unknown error";
}

// ================================ //
//
inline typename Nullable< void >::ErrorType		Nullable< void >::GetError () const
{
    if( m_isValid )
        assert( false ); // FIXME: error handling(?)
    return Error;
}

}	// sw
