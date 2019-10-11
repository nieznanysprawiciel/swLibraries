#pragma once
/**
@file MemoryCache.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "IAssetCache.h"



namespace sw
{


/**@brief RAM cache.

@ingroup AssetCache*/
class MemoryCache : public IAssetCache
{
private:
protected:
public:
	explicit		MemoryCache		() = default;
	virtual			~MemoryCache	() = default;


	/**@copydoc IAssetCache::AddCacheEntry*/
	virtual bool			AddCacheEntry		( const AssetPath& filePath, TypeID resourceType, MemoryChunk rawData )		override;
	/**@copydoc IAssetCache::RemoveEntry*/
	virtual bool			RemoveEntry			( const AssetPath& filePath, TypeID resourceType )							override;
	/**@copydoc IAssetCache::GetEntry*/
	virtual MemoryChunk&	GetEntry			( const AssetPath& filePath, TypeID resourceType )							override;

};

DEFINE_OPTR_TYPE( MemoryCache );

}	// sw

