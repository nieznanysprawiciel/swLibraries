#pragma once
/**
@file RMLoaderAPI.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"



namespace sw
{


class nResourceManager;



/**@brief ResourceManager API for @ref Loaders internal usage.

Loaders should use only synchronous functions. This API gives acces only
to those functions that won't cause deadlocks.

@todo Consider adding path of loaded asset to constructor. This way we could block
loading, that could cause deadlocks. (For example: Someone calls LoadGeneric on asset
that resides in file that is currenly loaded by loader).

@ingroup Loaders*/
class RMLoaderAPI
{
private:

	nResourceManager*		m_resourceManager;

protected:
public:

	explicit		RMLoaderAPI			( nResourceManager* manager );
					~RMLoaderAPI		() = default;

public:

	/**@brief Gets asset that is already loaded or returns nullptr if it isn't.
	
	Probably there are only rare cases when you want use this function. The main purpose could be checking if assets
	were already loaded by ResourceManager. If Loader can't get asset this way, creates new asset himself.
	I discourage to use GetGeneric for that. Even if asset doesn't exist in ResourceManager, it can be cached
	and ready to load. You should use GetCachedGeneric function in such case.

	The second case is, when Loader wants to load asset referenced by file that he loads. In this case you should
	use LoadGeneric function.*/
	ResourcePointer					GetGeneric					( const filesystem::Path& name, TypeID type );

	/**@brief Gets asset from ResourceManager or tries to create it from cache.

	Function will return nullptr if it won't find asset and is unable to create it from cache.
	You should always use this function before creating asset in Loader. There're some reasons causing, that
	asset already exist and despite this, Loader was called for the second time:
	- Someone requested asset from file, but didn't set Loader flag to load whole content of file. In this case
	some assets exist in @ref ResourceManager and some not, so second load request must load remaining content.
	- Assets were loaded in the past but they were removed as unnecessary and remained in cache.
	- Editor called LoadFileGeneric. This function always tries to load file even if assets existed and Loaders
	must be prepared for it.
	
	Don't use LoadGeneric to load assets from file that you are loading. Load Generic should be used to load
	assets referenced by file, but placed in other files.*/
	ResourcePointer					GetCachedGeneric			( const filesystem::Path& name, TypeID type );

	/**@copydoc nResourceManager::LoadGeneric*/
	sw::Nullable< ResourcePointer >	LoadGeneric					( const filesystem::Path& assetName, IAssetLoadInfo* desc, TypeID type );
};


}	// sw



