#pragma once
/**
@file CacheManager.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "IAssetCache.h"



namespace sw
{

/**@brief */
class CacheManager
{
private:

	IAssetCacheOPtr				m_cacheList;		///< Hierarchy of cache objects.

protected:
public:
	explicit		CacheManager		();
					~CacheManager		() = default;

	/**@brief Loads asset from cache if it exists. Oterwise returns nullptr.
	@todo Probably we should pass pointer to resource manager to allow asset creation.*/
	ResourcePtr< ResourceObject >		LoadFromCache		( const filesystem::Path& assetName, TypeID assetType );

private:

	/**@brief Creates default cache levels.*/
	void			InitDefaultCacheHierarchy	();
};



}	// sw

