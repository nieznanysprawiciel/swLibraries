#pragma once
/**
@file Nullable.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Engine.
*/

#include <exception>
#include <string>
#include <memory>
#include <assert.h>



namespace sw
{




/**@brief Alexandrescu Expected type for error handling.
@ingroup Helpers*/
template< typename ContentType >
class Nullable
{
public:

	typedef std::shared_ptr< std::exception > ErrorType;

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

    bool                    IsValid             ();
    std::string             GetErrorReason      ();
    ErrorType				GetError            ();

    bool						operator==          ( const ContentType & that );
    bool						operator!=          ( const ContentType & that );
	Nullable< ContentType >&	operator=			( const Nullable< ContentType > & that );

    const ContentType &				Get			() const;
    operator const ContentType &				() const;

	ContentType &					Get			();
    operator ContentType &						();

public:

    static Nullable			FromError           ( const ErrorType& error );
    static Nullable			FromError           ( const std::string& reason );
    static Nullable			FromError           ();
};


/**@brief Alexandrescu Expected type for error handling.
@ingroup Helpers*/
template<>
class Nullable< void >
{
public:

	typedef std::shared_ptr< std::exception > ErrorType;

private:

	ErrorType			Error;
	bool				m_isValid;

public:

	explicit                Nullable			();
			                Nullable			( bool result );
                            Nullable			( const ErrorType& error );
							Nullable			( const std::string& error );


    bool                    IsValid             ();
    std::string             GetErrorReason      ();
    ErrorType				GetError            ();

};


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
	: m_isValid( false ), Error( std::make_exception_ptr( std::make_shared< std::runtime_error >( error ) ) )
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
    return Error->what(); 
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
inline const ContentType &		Nullable< ContentType >::Get          () const
{ 
    if( !m_isValid ) 
        assert( false );  // FIXME: error handling(?)
    return Content; 
}

// ================================ //
//
template< typename ContentType >
inline ContentType &			Nullable< ContentType >::Get          () 
{ 
	if( !m_isValid )
		throw Error;
    return Content; 
}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::operator const ContentType &		() const
{ 
    return Get(); 
}

// ================================ //
//
template< typename ContentType >
inline Nullable< ContentType >::operator ContentType &				()
{ 
    return Get(); 
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
inline Nullable< void >::Nullable			( const std::string& error )
	: m_isValid( false ), Error( std::make_shared< std::runtime_error >( error ) )
{}

// ================================ //
//
inline Nullable< void >::Nullable			( bool result )
	: m_isValid( result ), Error( nullptr )
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
    return Error->what(); 
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
