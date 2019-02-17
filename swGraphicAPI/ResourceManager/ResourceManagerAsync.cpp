/**
@file ResourceManagerAsync.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"
#include "ResourceManagerAsync.h"


namespace sw
{

// ================================ //
//
ResourceManagerAsync::ResourceManagerAsync( nResourceManager* resourceManager )
	:	m_resourceManager( resourceManager )
	,	m_asyncThread( resourceManager )
{}

}	// sw

