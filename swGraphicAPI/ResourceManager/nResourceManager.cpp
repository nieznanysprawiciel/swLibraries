/**
@file nResourceManager.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"


#include "nResourceManager.h"
#include "swGraphicAPI/ResourceManager/nResourceContainer.h"
#include "swGraphicAPI/ResourceManager/Exceptions/ResourceManagerException.h"

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
ResourcePointer							nResourceManager::GetGeneric				( const filesystem::Path& name, TypeID type )
{
	// Lock as Reader.
	ReaderUniqueLock< ReaderWriterLock > lock( m_rwLock );

	return FindResource( name, type );
}

// ================================ //
//
sw::Nullable< ResourcePointer >			nResourceManager::LoadGeneric				( const filesystem::Path& name, IAssetLoadInfo* desc, TypeID type )
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
			auto result = m_waitingAssets.WaitUntilLoaded( assetWait );

			// Loading could fail. If this is the case, we return error stored in WaitingAsset.
			// Note that we must store error in WaitingAsset to avoid reloading the same file again.
			// All threads that waited for asset, have no other way to get to know loading result.
			if( result.IsValid() )
			{
				// Asset loader could load requested file but there's no guarantee that requested asset was loaded too.
				// For example name contains path to material inside mesh file. Loader loads entire mesh, but material wasn't necessary.
				// If asset was loaded, next call to LoadGeneric will take it from m_resources map. If it wasn't - next call will try to load
				// specific asset (not entire file). If it returns nullptr, it means that asset can't be loaded.
				//
				// @todo Consider situation when first found loader isn't able to load file, but next could. Should we handle this? Maybe use some loader flags.
				return LoadGeneric( name, desc, type );
			}

			return result.GetError();
		}
		else
		{
			return LoadingImpl( name, desc, type );
		}
	}

	return resource;
}

// ================================ //
//
sw::Nullable< ResourcePointer >			nResourceManager::CreateGenericAsset		( const filesystem::Path& name, TypeID assetType, IAssetCreateInfo&& createInfo )
{
	auto asset = m_assetsFactory->CreateAsset( name, assetType, std::move( createInfo ) );
	
	// If asset is valid we need to add it to m_resources.
	if( asset.IsValid() )
	{
		// Create this pointer here to increment reference counter. Assets factory returns raw C pointers.
		// After adding asset to m_resources, it can be released any time by other threads.
		ResourcePointer assetPointer = asset.Get();

		auto result = AddGenericResource( name, assetType, assetPointer );
		
		// Note: Asset under this name could already exist and it won't be added in AddGenericResource function.
		if( result.IsValid() )
			return assetPointer;
		else
		{
			// We must manually remove asset here, because it wasn't added to resources list.
			// @todo It would be better not to create asset in first place if we can't add it to resources list.
			// There are some solutions for that:
			// - Create asset under m_rwLock as writer - but creation would last long and we don't want to stop other threads.
			// - Check if asset can be added as reader and then add as writer - this suffers from race conditions but this way we could
			//   avoid most of not necessary creations.
			// - Use LoadBarrier (separate then in loader) - I don't know if it is reasonable, because we don't want to use asset created by others.
			assetPointer->Delete( ResourceAccessKey< Resource >() );

			return result.GetError();
		}
	}
	else
	{
		return asset.GetError();
	}
}



// ================================ //
//
bool									nResourceManager::RegisterAssetCreator		( IAssetCreatorPtr creator )
{
	return m_assetsFactory->RegisterCreator( creator );
}


//====================================================================================//
//			Internal implementation	
//====================================================================================//


// ================================ //
//
ResourcePtr< Resource >					nResourceManager::FindResource				( const filesystem::Path& name, TypeID assetType )
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
ResourcePtr< Resource >					nResourceManager::FindRequestedAsset		( const filesystem::Path& assetName, TypeID assetType, const AssetsVec& loadedAssets )
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
sw::Nullable< ResourcePointer >			nResourceManager::LoadingImpl				( const filesystem::Path& assetName, IAssetLoadInfo* desc, TypeID assetType )
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

// ================================ //
//
ReturnResult							nResourceManager::AddGenericResource		( const filesystem::Path& name, TypeID assetType, ResourcePointer resource )
{
	if( !resource )
		return std::make_shared< ResourceManagerException >( "Trying to add nullptr resource.", name, assetType );

	// Check if asset already exists in m_resources. Note that even if asset exists, that doesn't
	// mean that it is the same asset. It could be generated by user (and have different content) or it could be loaded
	// and postprocessed using different parameters.

	// Lock as Writer, because we want to add resource atomically.
	WriterUniqueLock< ReaderWriterLock > lock( m_rwLock );

	ResourceContainer< Resource >& container = m_resources[ assetType ];
	bool inserted = container.SafeAdd( name, resource.Ptr() );

	if( !inserted )
		return std::make_shared< ResourceManagerException >( "Can't add asset, because it already existed.", name, assetType );

	return Result::Success;
}



}	// sw

