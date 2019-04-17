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
bool				MemoryCache::AddCacheEntry		( const AssetPath& filePath, TypeID resourceType, MemoryChunk rawData )
{
	return false;
}

// ================================ //
//
bool				MemoryCache::RemoveEntry		( const AssetPath& filePath, TypeID resourceType )
{
	return false;
}

// ================================ //
//
MemoryChunk&		MemoryCache::GetEntry			( const AssetPath& filePath, TypeID resourceType )
{
	// TODO: insert return statement here
	return MemoryChunk();
}

}	// sw