/**
@file MemoryCache.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"
#include "MemoryCache.h"



namespace sw
{

// ================================ //
//
bool				MemoryCache::AddCacheEntry		( const filesystem::Path& filePath, TypeID resourceType, MemoryChunk rawData )
{
	return false;
}

// ================================ //
//
bool				MemoryCache::RemoveEntry		( const filesystem::Path& filePath, TypeID resourceType )
{
	return false;
}

// ================================ //
//
MemoryChunk&		MemoryCache::GetEntry			( const filesystem::Path& filePath, TypeID resourceType )
{
	// TODO: insert return statement here
	return MemoryChunk();
}

}	// sw