/**
@file ResourceManager.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"


#include "ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceContainer.h"
#include "swGraphicAPI/ResourceManager/Exceptions/ResourceManagerException.h"
#include "swGraphicAPI/ResourceManager/PathTranslators/LoadPath.h"

#include "swCommonLib/Common/Multithreading/UniqueLock.h"


namespace sw
{

// ================================ //
//
ResourceManager::ResourceManager()
	:	m_pathsManager( new PathsManager() )
{
	m_assetsFactory = AssetsFactoryOPtr( new AssetsFactory() );
}

// ================================ //
//
ResourceManager::~ResourceManager()
{
	// It would happen later, but we want to release Resources before creators and loaders.
	m_resources.clear();
}


// ================================ //
//
ResourcePointer							ResourceManager::GetGeneric				( const AssetPath& name, TypeID type )
{
	// Lock as Reader.
	ReaderUniqueLock< ReaderWriterLock > lock( m_rwLock );

	return FindResource( name, type );
}

//====================================================================================//
//			Loading	
//====================================================================================//


sw::Nullable< ResourcePointer >			ResourceManager::LoadGeneric				( const AssetPath& name, const IAssetLoadInfo* desc, TypeID type )
{
	auto loadPath = LoadPath( name, m_pathsManager.get() );
	return LoadGeneric( loadPath, desc, type );
}

// ================================ //
/// @note If asset loading fails and we call LoadGeneric function again, LoadGeneric will try to load it
/// for the second time. This will cause performance problem, when something is wrong with important asset
/// loaded by multiple entities, because even failed loading is heavy operation.
sw::Nullable< ResourcePointer >			ResourceManager::LoadGeneric				( const LoadPath& loadPath, const IAssetLoadInfo* desc, TypeID type )
{
	// Lock as Reader. Try to find resource and request asset atomically.
	ReaderUniqueLock< ReaderWriterLock > lock( m_rwLock );

	auto resource = FindResource( loadPath.GetOriginalPath(), type );
	if( !resource )
	{
		WaitingAsset* assetLock = nullptr;
		bool isLoadingInProgress = false;

		// We want to lock on absolute path without aliases. Otherwise two paths can point to the same asset.
		std::tie( assetLock, isLoadingInProgress ) = LockFileForLoading( loadPath );

		// Unlock as Reader. Here we either have locked asset for this thread or asset was already
		// locked and we must wait until other thread will load it completly.
		lock.Unlock();

		if( isLoadingInProgress )
		{
			auto result = m_waitingAssets.WaitUntilLoaded( assetLock );

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
				return LoadGeneric( loadPath, desc, type );
			}

			return result.GetError();
		}
		else
		{
			return LoadingImpl( loadPath, desc, type );
		}
	}

	return resource;
}

// ================================ //
//
LoadingResult							ResourceManager::LoadFileGeneric			( const AssetPath& assetName, IAssetLoadInfo* desc, TypeID type )
{
	return LoadingResult();
}

// ================================ //
//
LoadingResult							ResourceManager::LoadFileGeneric			( const AssetPath& assetName, IAssetLoadInfo* desc, TypeID type, IAssetLoader* loader )
{
	return LoadingResult();
}

//====================================================================================//
//			Assets creation	
//====================================================================================//


// ================================ //
//
sw::Nullable< ResourcePointer >			ResourceManager::CreateGenericAsset		( const AssetPath& name, TypeID assetType, IAssetCreateInfo&& createInfo )
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

//====================================================================================//
//				Releasing resources
//====================================================================================//

// ================================ //
//
void									ResourceManager::FreeUnusedAssets			()
{
	WriterUniqueLock< ReaderWriterLock > lock( m_rwLock );
	
	// Assets can depend on other Assets. The simplest way to free Resources is to iterate multiple times.
	Size removedAssets = 0;		
	
	do
	{
		removedAssets = 0;
		for( auto& container : m_resources )
		{
			removedAssets += container.second.RemoveUnused();
		}

	} while( removedAssets > 0 );
}

//====================================================================================//
//			Listing assets	
//====================================================================================//

// ================================ //
//
std::vector< ResourcePointer >			ResourceManager::ListAssets				( TypeID assetType ) const
{
	return ListAssetsTyped< Resource >( assetType );
}

//====================================================================================//
//			Loaders, creators, registration
//====================================================================================//


// ================================ //
//
bool									ResourceManager::RegisterAssetCreator		( IAssetCreatorPtr creator )
{
	return m_assetsFactory->RegisterCreator( creator );
}

// ================================ //
//
bool									ResourceManager::RegisterLoader			( IAssetLoaderPtr loader )
{
	m_loaders.push_back( loader );
	return true;
}

// ================================ //
//
LoadersVec								ResourceManager::ListLoaders				() const
{
	return m_loaders;
}


//====================================================================================//
//			Internal implementation	
//====================================================================================//


// ================================ //
//
ResourcePtr< Resource >					ResourceManager::FindResource				( const AssetPath& name, TypeID assetType )
{
	auto translatedPath = Translate( name );

	auto containerIter = m_resources.find( assetType );
	if( containerIter != m_resources.end() )
	{
		ResourceContainer< Resource >& container = containerIter->second;
		return container.Get( translatedPath );
	}

	return ResourcePtr< Resource >();
}

// ================================ //
//
IAssetLoader*							ResourceManager::FindLoader				( const AssetPath& assetName, TypeID assetType )
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
std::pair< WaitingAsset*, bool >		ResourceManager::LockFileForLoading		( const LoadPath& loadPath )
{
	// We want to lock on absolute path without aliases. Otherwise two paths can point to the same asset.
	return m_waitingAssets.RequestAsset( loadPath.GetTranslatedPath().GetFile() );
}

// ================================ //
//
ResourcePtr< Resource >					ResourceManager::FindRequestedAsset		( const LoadPath& loadPath, TypeID assetType, const AssetsVec& loadedAssets )
{
	std::string assetNameStr = loadPath.GetOriginalPath().String();

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
sw::Nullable< ResourcePointer >			ResourceManager::LoadingImpl				( const LoadPath& loadPath, const IAssetLoadInfo* desc, TypeID assetType )
{
	// @attention: Remember to remove asset lock before each return statement.
	// Otherwise assetName will be locked for loading for always. 

	auto resource = m_cacheManager.LoadFromCache( loadPath.GetTranslatedPath(), assetType );
	if( !resource )
	{
		auto loader = FindLoader( loadPath.GetOriginalPath(), assetType );
		if( loader )
		{
			auto loadingResult = loader->Load( loadPath, assetType, desc, RMLoaderAPI( this ) );

			if( !loadingResult.Assets.IsValid() )
			{
				// Remove asset lock.
				m_waitingAssets.LoadingFailed( loadPath.GetFileTranslated(), loadingResult.Assets.GetError() );
				return loadingResult.Assets.GetError();
			}

			resource = FindRequestedAsset( loadPath, assetType, loadingResult.Assets );
		}
		else
		{
			auto exception = std::make_shared< ResourceManagerException >( "Loader for asset not found. ", loadPath.Print(), assetType );

			// Remove asset lock.
			m_waitingAssets.LoadingFailed( loadPath.GetFileTranslated(), exception );
			return exception;
		}
	}

	// Remove asset lock.
	m_waitingAssets.LoadingCompleted( loadPath.GetFileTranslated() );

	return resource;
}

// ================================ //
//
ReturnResult							ResourceManager::AddGenericResource		( const AssetPath& name, TypeID assetType, ResourcePointer resource )
{
	if( !resource )
		return std::make_shared< ResourceManagerException >( "Trying to add nullptr resource.", name.String(), assetType );

	auto translatedName = Translate( name );

	// Check if asset already exists in m_resources. Note that even if asset exists, that doesn't
	// mean that it is the same asset. It could be generated by user (and have different content) or it could be loaded
	// and postprocessed using different parameters.

	// Lock as Writer, because we want to add Resource atomically.
	WriterUniqueLock< ReaderWriterLock > lock( m_rwLock );

	ResourceContainer< Resource >& container = m_resources[ assetType ];
	bool inserted = container.SafeAdd( translatedName, resource.Ptr() );

	if( !inserted )
		return std::make_shared< ResourceManagerException >( "Can't add asset, because it already existed.", name.String(), assetType );

	return Result::Success;
}

// ================================ //
//
filesystem::Path						ResourceManager::Translate					( const filesystem::Path& path )
{
	return LoadPath::Translate( path, m_pathsManager.get() );
}

// ================================ //
//
AssetPath								ResourceManager::Translate					( const AssetPath& name )
{
	return LoadPath::Translate( name, m_pathsManager.get() );
}





}	// sw

