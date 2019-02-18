#pragma once
/**
@file IAssetCache.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/System/Path.h"


/**@defgroup AssetCache Asset Cache
@ingroup AssetsManagement

@copydoc CachingAssets
*/

/**@page CachingAssets Caching Assets

*/



namespace sw
{

/**@brief Interface for assets cache.
@ingroup AssetCache*/
class IAssetCache
{
private:
protected:
public:
	explicit		IAssetCache		() = default;
	virtual			~IAssetCache	() = 0;


	virtual bool			AddCacheEntry		( const filesystem::Path& filePath, TypeID resourceType, MemoryChunk rawData  )		= 0;
	virtual bool			RemoveEntry			( const filesystem::Path& filePath, TypeID resourceType )							= 0;

	/**@brief Gets raw cache entry.
	@todo Solve problem with multithreading. This entry can be released during use.*/
	virtual MemoryChunk&	GetEntry			( const filesystem::Path& filePath, TypeID resourceType )							= 0;

};

DEFINE_OPTR_TYPE( IAssetCache );

}	// sw
