#pragma once
/**
@file CacheManager.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "IAssetCache.h"

#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"



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
	@todo Probably we should pass pointer to resource manager to allow asset creation.
	@todo Maybe we could use string as key instead of AssetPath.*/
	ResourcePtr< Resource >		LoadFromCache		( const AssetPath& assetName, TypeID assetType );

private:

	/**@brief Creates default cache levels.*/
	void			InitDefaultCacheHierarchy	();
};



}	// sw

