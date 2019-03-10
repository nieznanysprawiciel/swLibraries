/**
@file nResourceManager.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"


#include "nResourceManager.h"
#include "swGraphicAPI/ResourceManager/nResourceContainer.h"

#include "swCommonLib/Common/Multithreading/UniqueLock.h"


namespace sw
{

// ================================ //
//
nResourceManager::nResourceManager()
{
	m_assetsFactory = AssetsFactoryOPtr( new AssetsFactory() );
}

// ================================ //
//
nResourceManager::~nResourceManager()
{}

// ================================ //
//
ResourcePtr< Resource >			nResourceManager::LoadGeneric				( const filesystem::Path& name, IAssetLoadInfo* desc, TypeID type )
{
	// Lock as Reader.
	ReaderUniqueLock< ReaderWriterLock > lock( m_rwLock );

	auto resource = FindResource( name, type );
	if( !resource )
	{
		/// @todo This path should be preprocessed to contain only path without everything after ::.
		auto result = m_waitingAssets.RequestAsset( name );

		// Unlock as Reader.
		lock.Unlock();
		
		WaitingAsset* assetWait = result.first;
		bool needWait = result.second;

		if( needWait )
		{
			m_waitingAssets.WaitUntilLoaded( assetWait );

			// Asset loader could load requested file but there's no guarantee that requested asset was loaded too.
			// For example name contains path to material inside mesh file. Loader loads entire mesh, but material wasn't necessary.
			// If asset was loaded, next call to LoadGeneric will take it from m_resources map. If it wasn't - next call will try to load
			// specific asset (not entire file). If it returns nullptr, it means that asset can't be loaded.
			//
			// @todo Consider situation when first found loader isn't able to load file, but next could. Should we handle this? Maybe use some loader flags.
			resource = LoadGeneric( name, desc, type );
		}
		else
		{
			resource = LoadingImpl( name, desc, type );
		}
	}

	return resource;
}

// ================================ //
//
ResourcePtr< Resource >			nResourceManager::CreateGenericAsset		( const filesystem::Path& name, TypeID assetType, IAssetCreateInfo&& createInfo )
{


	return ResourcePtr<Resource>();
}


//====================================================================================//
//			Internal implementation	
//====================================================================================//


// ================================ //
//
ResourcePtr< Resource >			nResourceManager::FindResource				( const filesystem::Path& name, TypeID assetType )
{
	auto containerIter = m_resources.find( assetType );
	if( containerIter != m_resources.end() )
	{
		ResourceContainer< Resource >& container = containerIter->second;
		return container.Get( name );
	}

	return ResourcePtr< Resource >();
}

// ================================ //
//
IAssetLoader*							nResourceManager::FindLoader				( const filesystem::Path& assetName, TypeID assetType )
{
	for( auto& loader : m_loaders )
	{
		if( loader->CanLoad( assetName, assetType ) )
			return loader.get();
	}

	return nullptr;
}


// ================================ //
//
ResourcePtr< Resource >			nResourceManager::FindRequestedAsset		( const filesystem::Path& assetName, TypeID assetType, const AssetsVec& loadedAssets )
{
	std::string assetNameStr = assetName.String();

	for( auto loadedAsset : loadedAssets )
	{
		if( loadedAsset->GetResourceName() == assetNameStr &&
			loadedAsset->GetType().is_derived_from( assetType ) )
			return loadedAsset;
	}

	// There's no asset that has the same name. We could return first asset in raw maybe...
	if( loadedAssets.size() > 0 )
		return loadedAssets[ 0 ];

	return nullptr;
}

// ================================ //
//
ResourcePtr< Resource >			nResourceManager::LoadingImpl				( const filesystem::Path& assetName, IAssetLoadInfo* desc, TypeID assetType )
{
	auto resource = m_cacheManager.LoadFromCache( assetName, assetType );
	if( !resource )
	{
		// @todo Maybe we should extract file name from asset name.
		auto loader = FindLoader( assetName, assetType );
		AssetsVec loadedAssets = loader->Load( assetName, assetType, desc, RMAsyncLoaderAPI( this ) );

		resource = FindRequestedAsset( assetName, assetType, loadedAssets );
	}

	return resource;
}

}	// sw

