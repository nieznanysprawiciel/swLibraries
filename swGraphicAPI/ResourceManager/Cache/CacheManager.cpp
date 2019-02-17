/**
@file CacheManager.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"
#include "CacheManager.h"


#include "swGraphicAPI/ResourceManager/Cache/MemoryCache.h"


namespace sw
{

// ================================ //
//
CacheManager::CacheManager()
{
	InitDefaultCacheHierarchy();
}

// ================================ //
//
ResourcePtr< ResourceObject >		CacheManager::LoadFromCache		( const filesystem::Path& assetName, TypeID assetType )
{
	return ResourcePtr< ResourceObject >();
}


//====================================================================================//
//			Internal	
//====================================================================================//

// ================================ //
//
void		CacheManager::InitDefaultCacheHierarchy()
{
	m_cacheList = MemoryCacheOPtr( new MemoryCache() );
}

}	// sw


