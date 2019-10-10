#include "ExceptionsList.h"
/**
@file ExceptionsList.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



namespace sw
{




// ================================ //
//
std::string				ExceptionsList::ErrorMessage		() const
{
	std::string message = "";

	for( auto& exception : m_nestedExceptions )
		message += exception->ErrorMessage() + "\n";

	return message;
}

// ================================ //
//
void					ExceptionsList::MergeExceptions		( ExceptionsListPtr list )
{
	const auto& listExceptions = list->GetNestedExceptions();
	m_nestedExceptions.insert( m_nestedExceptions.end(), listExceptions.begin(), listExceptions.end() );
}

// ================================ //
//
void					ExceptionsList::AddException		( ExceptionPtr except )
{
	m_nestedExceptions.push_back( except );
}

}	// sw


