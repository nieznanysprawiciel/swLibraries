/**
@file LoaderException.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "LoaderException.h"

#include "swCommonLib/Common/fmt.h"



namespace sw
{

// ================================ //
//
LoaderException::LoaderException								( std::string loaderName, std::string error, LoadPath path, TypeID assetType )
	: RuntimeException( std::move( error ) )
	, m_path( std::move( path ) )
	, m_resourceType( assetType )
	, m_loaderName( std::move( loaderName ) )
{}

// ================================ //
//
LoaderExceptionPtr		LoaderException::Create					( std::string loaderName, std::string error, LoadPath path, TypeID assetType )
{
	return std::make_shared< LoaderException >( std::move( loaderName ), std::move( error ), std::move( path ), assetType );
}


// ================================ //
//
std::string				LoaderException::ErrorMessage			() const
{
	return LoaderHeader()
		+ RuntimeException::ErrorMessage()
		+ ResourceInfo();
}

// ================================ //
//
std::string				LoaderException::LoaderHeader			() const
{
	return fmt::format( "[{}] ", m_loaderName );
}

// ================================ //
//
std::string				LoaderException::ResourceInfo			() const
{
    return fmt::format( " {}, type [{}].", m_path, m_resourceType );
}




}	// sw
