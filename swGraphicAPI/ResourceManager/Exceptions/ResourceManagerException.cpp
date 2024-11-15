/**
@file ResourceManagerException.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "ResourceManagerException.h"




namespace sw
{

// ================================ //
//
ResourceManagerException::ResourceManagerException					( const std::string& error, const fs::Path& name, TypeID assetType )
	:	RuntimeException( error )
	,	m_resourceName( name )
	,	m_resourceType( assetType )
{}


// ================================ //
//
std::string				ResourceManagerException::ErrorMessage			() const
{
	return ResourceManagerHeader()
		+ RuntimeException::ErrorMessage()
		+ ResourceInfo();
}

// ================================ //
//
std::string				ResourceManagerException::ResourceManagerHeader	() const
{
	return "[ResourceManager] ";
}

// ================================ //
//
std::string				ResourceManagerException::ResourceInfo			() const
{
	return " Name [" + m_resourceName.String() + "], type [" + m_resourceType.get_name().to_string() + "].";
}


}	// sw
