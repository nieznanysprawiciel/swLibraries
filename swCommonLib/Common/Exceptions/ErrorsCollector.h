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

	inline				operator ReturnResult	();
	inline ReturnResult Get						();

	inline bool			IsList					() const { return m_multipleRaised; }

	inline ExceptionsListPtr	GetExceptionsList	() const;
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

// ================================ //
//
inline void			ErrorsCollector::Add			( ExceptionsListPtr list )
{
	auto& exceptionsVec = list->GetNestedExceptions();

	// Note: Sometimes we could use list from parameter and take ownership of it (for example if we don't have created list yet).
	// We could consider this, but it is dangerous. Someone could modify this list from outside.
	for( auto& newException : exceptionsVec )
		Add( newException );
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


}	// sw


