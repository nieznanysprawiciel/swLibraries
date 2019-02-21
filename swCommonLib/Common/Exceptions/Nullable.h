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




namespace sw
{


/**@brief Enumeration for nullable for creating valid and invalid object.
@ingroup Helpers*/
enum class Result : uint8
{
	Error,
	Success
};



/**@brief Alexandrescu Expected type for error handling.
@ingroup Exceptions*/
template< typename ContentType >
class Nullable
{
public:

	typedef ExceptionPtr ErrorType;

protected:
    union
    {
        ContentType			Content;
        ErrorType			Error;
    };

    bool					m_isValid;

public:

    explicit                Nullable			();
                            Nullable			( ContentType&& content );
							Nullable			( const ContentType& content );
                            Nullable			( const ErrorType& error );
							Nullable			( const std::string& error );
                            Nullable			( const Nullable< ContentType > & that );
                            ~Nullable			();

	template< typename ExceptionType >
							Nullable			( std::shared_ptr< ExceptionType > error );

    bool                    IsValid             ();
    std::string             GetErrorReason      ();
    ErrorType				GetError            ();

    bool						operator==          ( const ContentType & that );
    bool						operator!=          ( const ContentType & that );
	Nullable< ContentType >&	operator=			( const Nullable< ContentType > & that );

    const ContentType &				Get			() const&;
    operator const ContentType &				() const&;

	ContentType &					Get			() &;
    operator ContentType &						() &;

	ContentType &&					Get			() &&;
    operator ContentType &&						() &&;

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
			                Nullable			( Result result );
                            Nullable			( const ErrorType& error );
							Nullable			( const std::string& error );

	template< typename ExceptionType >
							Nullable			( std::shared_ptr< ExceptionType > error );

    bool                    IsValid             ();
    std::string             GetErrorReason      ();
    ErrorType				GetError            ();

};


typedef Nullable< void > ReturnResult;


// ========================================================================= //
// Implementation
// ========================================================================= //

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::Nullable        () 
    : m_isValid( false )
    , Error( nullptr ) 
{}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::Nullable			( ContentType&& content ) 
    : m_isValid( true ), Content( std::move( content ) ) 
{}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::Nullable			( const ContentType& content )
	: m_isValid( true ), Content( content ) 
{}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::Nullable			( const ErrorType & error ) 
    : m_isValid( false ), Error( error )
{}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::Nullable			( const std::string& error )
	: m_isValid( false ), Error( std::static_pointer_cast< Exception >( std::make_shared< RuntimeException >( error ) ) )
{}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::Nullable			( const Nullable< ContentType > & that ) 
    : m_isValid( that.m_isValid )
{ 
    if( m_isValid ) 
        new( &Content ) ContentType( that.Content ); 
    else 
        new( &Error ) ErrorType( that.Error ); 
}

// ================================ //
//
template< typename ContentType >
template< typename ExceptionType >
inline Nullable< ContentType >::Nullable			( std::shared_ptr< ExceptionType > error )
	: m_isValid( false ), Error( std::static_pointer_cast< Exception >( error ) )
{
	static_assert( std::is_base_of< typename ErrorType::element_type, ExceptionType >::value, "ExceptionType should be derived from ErrorType" );
}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::~Nullable       () 
{
    if( m_isValid ) 
        Content.~ContentType(); 
    else 
        Error.~ErrorType(); 
}

// ================================ //
//
template< typename ContentType >
inline bool						Nullable< ContentType >::IsValid() 
{
    return m_isValid;
}

// ================================ //
//
template< typename ContentType >
inline std::string				Nullable< ContentType >::GetErrorReason  () 
{ 
	if( Error )
		return Error->ErrorMessage();
	return "Unknown error";
}

// ================================ //
//
template< typename ContentType >
inline typename Nullable< ContentType >::ErrorType		Nullable< ContentType >::GetError ()
{
    if( m_isValid )
        assert( false ); // FIXME: error handling(?)
    return Error;
}

// ================================ //
//
template< typename ContentType >
inline bool						Nullable< ContentType >::operator==      ( const ContentType & that ) 
{ 
    return m_isValid && Content == that; 
}

// ================================ //
//
template< typename ContentType >
inline bool						Nullable< ContentType >::operator!=      ( const ContentType & that ) 
{ 
    return !( *this == that ); 
}

// ================================ //
//
template< typename ContentType >
Nullable< ContentType >&		Nullable< ContentType >::operator=		( const Nullable< ContentType > & that )
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
template< typename ContentType >
inline const ContentType &		Nullable< ContentType >::Get          () const&
{ 
    if( !m_isValid ) 
        assert( false );  // FIXME: error handling(?)
    return Content; 
}

// ================================ //
//
template< typename ContentType >
inline ContentType &			Nullable< ContentType >::Get          () &
{ 
	if( !m_isValid )
		throw Error;
    return Content; 
}

// ================================ //
//
template< typename ContentType >
inline ContentType &&			Nullable< ContentType >::Get          () &&
{ 
	if( !m_isValid )
		throw Error;
    return std::move( Content );
}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::operator const ContentType &		() const &
{ 
    return Get(); 
}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::operator ContentType &				() &
{ 
    return Get(); 
}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::operator ContentType &&				() &&
{ 
    return std::move( Get() );
}

//====================================================================================//
//			Creating Nullable from error	
//====================================================================================//

template< typename ContentType >
inline Nullable< ContentType >     Nullable< ContentType >::FromError       ( const ErrorType& error ) 
{ 
    Nullable< ContentType > ret; 
    ret.Error = error; 
    return ret; 
}

template< typename ContentType >
inline Nullable< ContentType >     Nullable< ContentType >::FromError       ( const std::string& reason ) 
{ 
    return FromError( std::make_shared< std::runtime_error >( reason ) ); 
}

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
inline Nullable< void >::Nullable			( const std::string& error )
	: m_isValid( false ), Error( std::static_pointer_cast< Exception >( std::make_shared< RuntimeException >( error ) ) )
{}

// ================================ //
//
inline Nullable< void >::Nullable			( Result result )
	: m_isValid( result == Result::Success ), Error( nullptr )
{}


// ================================ //
//
inline bool						Nullable< void >::IsValid() 
{
    return m_isValid;
}

// ================================ //
//
inline std::string				Nullable< void >::GetErrorReason  () 
{
	if( Error )
		return Error->ErrorMessage();
	return "Unknown error";
}

// ================================ //
//
inline typename Nullable< void >::ErrorType		Nullable< void >::GetError ()
{
    if( m_isValid )
        assert( false ); // FIXME: error handling(?)
    return Error;
}

}	// sw
