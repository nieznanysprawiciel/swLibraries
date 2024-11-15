/**
@file FileNotFoundException.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "FileNotFoundException.h"


namespace sw
{

// ================================ //
//
FileNotFoundException::FileNotFoundException					( fs::Path filePath )
	:	m_path( std::move( filePath ) )
{}

// ================================ //
//
std::string				FileNotFoundException::ErrorMessage		() const
{
	return "File [" + m_path.String() + "] not found.";
}

}	// sw

