#pragma once
/**
@file ErrorsCollector.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "ExceptionsList.h"
#include "Nullable.h"


namespace sw
{


/**@brief Class for collecting exceptions.

You can create ErrorsCollector on stack, check multiple conditions and then
add raised exceptions to list. This class will produce ReturnResult on the end.
- If only one exception occured, single exception will be returned.
- If multiple exceptions occured, ExceptionsList will be created internally and all
exceptions will be added to list.
- If there were no errror, Result::Success will be returned.

This class creates ExceptionsList class only if necessary and hides cumbersome code from user. 

@ingroup Exceptions*/
class ErrorsCollector
{
private:

	ExceptionPtr			m_exception;		///< ExceptionsList if multiple exceptions occured.
	bool					m_multipleRaised;

protected:
public:
	explicit		ErrorsCollector		();
					~ErrorsCollector	() = default;

public:

	inline void			Add						( ReturnResult result );
	inline void			Add						( ExceptionPtr exception );
	inline void			Add						( ExceptionsListPtr list );
	inline void			Add						( const ErrorsCollector& collector );

    template< typename ErrorType >
    inline void			Add						( const std::shared_ptr< ErrorType >& exception );

	/**@brief Checks if returned result was success. Adds exception, if it wasnt't.
	
	Proposed usage:
	@code
	ErrorsCollector collector;

	auto result = SomeFunction();
	if( collector.Success( result ) )
	{
		// Do something with result here, because it's valid.
		result.Get();
	}
	@endcode
	*/
	template< typename ReturnType >
	inline bool			Success					( const Nullable< ReturnType >& result );

    /**@brief Checks if returned result was success. Moves value of Nullable if it was valid.
    Returns defaultVal, if it was invalid, and collects error.
    
    This function is meant to defer error handling or collect warning.
    
    Proposed usage:
    @code
    ReturnResult        SomeClass::Function()
    {
        ErrorsCollector collector;

        member_pointer1 = collector.OnError( SomeFunction1(), nullptr ) );
        member_pointer2 = collector.OnError( SomeFunction2(), nullptr ) );

        return collector.Get();
    }
    @endcode

    Note that this helps us avoid cubersome ifs that check errors like this:

    @code
    ReturnResult        SomeClass::Function()
    {
        ErrorsCollector collector;

        auto result1 = SomeFunction1();
        if( result1.IsValid() )
            member_pointer1 = result1.Get();

        auto result2 = SomeFunction1();
        if( result2.IsValid() )
            member_pointer2 = result2.Get();

        return collector.Get();
    }
    @endcode
    */
    template< typename ReturnType >
    inline ReturnType   OnError					( Nullable< ReturnType >&& result, ReturnType defaultVal );

	inline				operator ReturnResult	();
	inline ReturnResult Get						();

	inline bool			IsList					() const { return m_multipleRaised; }

	inline ExceptionsListPtr	GetExceptionsList	() const;
	inline ExceptionPtr			GetException		() const { return m_exception; }
};

//====================================================================================//
//			Implementation
//====================================================================================//

// ================================ //
//
inline ErrorsCollector::ErrorsCollector()
	:	m_multipleRaised( false )
{}

// ================================ //
//
inline void			ErrorsCollector::Add			( ReturnResult result )
{
	// Note: There's no way to check if exception isn't ExceptionsList.
	// Moreover I don't know, if it would be reasonable to flatten such a list here.
	if( !result.IsValid() )
		Add( result.GetError() );
}

// ================================ //
//
inline void			ErrorsCollector::Add			( ExceptionPtr newException )
{
	if( newException )
	{
		if( !m_exception )
		{
			m_exception = newException;
		}
		else if( m_multipleRaised )
		{
			ExceptionsListPtr list = std::static_pointer_cast< ExceptionsList >( m_exception );
			list->AddException( newException );
		}
		else
		{
			// m_exception is single exception without nesting.
			// Create list and add previous exception to it.
			ExceptionsListPtr list = std::make_shared< ExceptionsList >();
			list->AddException( m_exception );
			list->AddException( newException );

			m_exception = list;
			m_multipleRaised = true;
		}
	}
}

// ================================ //
//
inline void			ErrorsCollector::Add			( ExceptionsListPtr list )
{
	if( list )
	{
		auto& exceptionsVec = list->GetNestedExceptions();

		// Note: Sometimes we could use list from parameter and take ownership of it (for example if we don't have created list yet).
		// We could consider this, but it is dangerous. Someone could modify this list from outside.
		for( auto& newException : exceptionsVec )
			Add( newException );
	}
}

// ================================ //
//
inline void			ErrorsCollector::Add			( const ErrorsCollector& collector )
{
	if( &collector != this )
	{
		// ExceptionsList can be nullptr, but collector should survive this.
		if( collector.IsList() )
			Add( collector.GetExceptionsList() );
		else if( collector.m_exception != nullptr )
			Add( collector.m_exception );
	}
}

// ================================ //
//
inline				ErrorsCollector::operator ReturnResult()
{
	if( m_exception )
		return m_exception;

	return Result::Success;
}

// ================================ //
//
inline ReturnResult				ErrorsCollector::Get					()
{
	return ReturnResult( m_exception );
}

// ================================ //
//
inline ExceptionsListPtr		ErrorsCollector::GetExceptionsList		() const
{
	if( m_multipleRaised )
		return std::static_pointer_cast< ExceptionsList >( m_exception );

	return nullptr;
}

// ================================ //
//
template< typename ErrorType >
inline void                     ErrorsCollector::Add                    ( const std::shared_ptr< ErrorType >& exception )
{
    Add( std::static_pointer_cast< Exception >( exception ) );
}

// ================================ //
//
template< typename ReturnType >
inline bool						ErrorsCollector::Success				( const Nullable< ReturnType >& result )
{
	if( result.IsValid() )
		return true;

	Add( result.GetError() );
	return false;
}

// ================================ //
//
template< typename ReturnType >
inline ReturnType               ErrorsCollector::OnError                  ( Nullable< ReturnType >&& result, ReturnType defaultVal )
{
    if( result.IsValid() )
        return std::move( result ).Get();

    Add( result.GetError() );
    return std::move( defaultVal );
}

}	// sw


