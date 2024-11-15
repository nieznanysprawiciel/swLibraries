#pragma once
/**
@file ResourceManager.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/PipelineStates/BlendingState.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"

#include "swGraphicAPI/ResourceManager/ResourceContainer.h"
#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"
#include "swGraphicAPI/ResourceManager/PathTranslators/PathsManager.h"

#include "swCommonLib/Common/Multithreading/ReaderWriterLock.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "AssetCreators/AssetsFactory.h"
#include "Loaders/IAssetLoader.h"
#include "Cache/CacheManager.h"
#include "AsyncLoad/LoadBarrier.h"

#include <vector>
#include <map>



namespace sw
{


/**@defgroup AssetsManagement Assets Management
@brief Class for loading assets and managing their lifetime.
@ingroup GraphicAPI

@copydoc ResourceManagerRequirements

@page ResourceManagerRequirements Resource Manager Requirements

@section RMRequirements ResourceManager requirements

-# ResourceManager supports generic assets types defined by future users. It should also expose special functions
for built in low level types without need to use this generic API, but these types should be also avaible through generic API.
-# User can write his own implementations of loaders for different file types.
Requirements:
    - Loaders implement generic interface, but user can also add parameters for specific loader.
      For example FBX SDK loader could load Meshes and merge them all in one asset or it could
      create several assets for all parts.
    - ResourceManager finds best matching loader and uses it to load asset.
    - Loaders support loading of whole content of file.
    - Loaders allow to prefetch data and store it in cache, without loading asset.
    - Separated asset creation and file loading.
        - User uses the same API to generate assets as Loader uses to load file.
        - Assets are created using descritpors describing their content.
        - User can provide their own implementation of @ref sw::IAssetCreator "Asset Creator".
        - Library provides set of basic creators for native GPU Resources.
-# Asynchronous assets loading. Assets can be loaded in separate thread. User provides callback function which will be called
when asset is ready.
    - There's separate API for synchronous and asynchronous loading.
    - Request can come from multiple threads. In case of synchronous load, when multiple threads want to load the same asset,
      all threads are blocked until asset is loaded. ResourceManager takes care of dealing with these conflicts and prevents from loading
      same asset multiple times.
    - Internal implementation uses only one thread for loading. This should be enough for high performance, since disk access is bottleneck.
-# Paths translation. Some assets' directory can depend on graphic API which is being used (for example shaders glsl or hlsl).
User can register Paths Aliases in ResourceManager and access assets paths using these aliases. ResourceManager translates aliases to
real paths.
Requirements:
    - Paths Aliases are user defined so can be used for different purposes too.
    - Functionality of finding best matching alias. This functionality is usefull, when editor has browse file dialog and sends absolut
      path to ResourceManager.
-# ResourceManager supports packed file which internally consist of many smaller files.
    - ResourceManager paths consist of system path and internal path.
        - Asset file can contain multiple assets.
        - File can have internal filesystem and internal path represent this internal structure.
        - ResourceManager supports generated content. Paths should constist only from internal path then.
-# Assets caching. Assets can be cached in RAM memory in raw form to speed up creating. Second cache level can exist on SSD drive.
Requirements:
    - Cache automatically manages resources.
        - Assets are moved automatically based on chosen cache strategy.
        - It supports maximal memory occupancy limit.
        - Support for prefetching mechanism. Assets can be loaded from cache depending on prefetching strategy.
        - Cache should be aware of assets dependencies. Dependend assets can't be moved to lower cache level before
          parent asset is moved.
    - Support for multilevel cache hierarchy. User can implement his own cache levels.
    - Predefined cache levels: RAM cache and disk cache.
    - API for user defined caching strategy.
    - API for user defined prefetching strategy.
-# Descriptive error handling.
    - Most of API returns @ref sw::Nullable "Nullable", which can hold error message (@ref sw::Exception).
    - ResourceManager doesn't throws exceptions.
    - Two levels of errors: errors and warnings.
-# Support for level of detailes.
-# Support for asset streaming.
-# Support for hot reload of shaders and other assets where possible.
*/

typedef std::vector< IAssetLoaderPtr > LoadersVec;


/**@brief Manages resources creation, loading and releasing.

@ingroup AssetsManagement*/
class ResourceManager
{
	typedef std::map< TypeID, ResourceContainer< Resource > > ResourcesMap;

private:
protected:

	ResourcesMap				m_resources;

	ReaderWriterLock			m_rwLock;				///< Reader/Writer lock for protecting m_resources dictionary.
	LoadBarrier					m_waitingAssets;		///< Barrier protects from loading one asset multiple times.

	PathsManagerUPtr			m_pathsManager;			///< Translates path aliases into system paths.

	CacheManager				m_cacheManager;			///< Assets cache.
	AssetsFactoryOPtr			m_assetsFactory;		///< Factory for generic and non generic assets creation.

	LoadersVec					m_loaders;				///< File loaders.

public:

	/**@brief This constructor creates default cache and AssetsFactory.*/
	explicit		ResourceManager		    ();
	virtual			~ResourceManager		();




	///@name Geting existing resource
	///@detail Gets resource if exist otherwise returns nullptr.
	///@{

	ResourcePointer				GetGeneric					( const AssetPath& name, TypeID type );

	template< typename AssetType >
	ResourcePtr< AssetType >	Get							( const AssetPath& name );

	///@}


	///@name Resource loading
	///@detail Load assets from specified file. Functions protect from loading assets multiple times.
	///@{

	sw::Nullable< ResourcePointer >	LoadGeneric					( const AssetPath& assetName, const IAssetLoadInfo* desc, TypeID type );

	/**@brief Loads asset file with it's whole content.
	
	This function is meant for Editor usage. It will load and return all assets that will be found in specified file.
	Moreover all assets from other files, that are referenced by these assets will be loaded too.
	If asset alredy existed in ResourceManager, Loader should take this existing asset and return warning.
	
	@note Note that Loader will be called each time this function is called, even if all assets were loaded. There is
	no other way to determine content of file, than to load it again. Loaders should always check if asset existed
	and shouldn't spend time on creating not necessary assets, but performance penalty exists and depends on Laoder.

	@note Note that it is posible that file contains assets that couldn't be loaded, because IAssetLoader implementation
	doesn't support that.

	@return Returns list of loaded assets or error if loader was unable to load file. Loading results
	contains all warnings that occured during loading.*/
	LoadingResult					LoadFileGeneric				( const AssetPath& assetName, IAssetLoadInfo* desc, TypeID type );
	LoadingResult					LoadFileGeneric				( const AssetPath& assetName, IAssetLoadInfo* desc, TypeID type, IAssetLoader* loader );
	///@}

	///@name Resource creation
	///@detail You can create assets in code using these functions. Remember to give unique names for your assets.
	///Engine uses convention, that all generated resources have :: before name, to distinguish them from assets loaded from files.
	///@{
	sw::Nullable< ResourcePointer >	CreateGenericAsset			( const AssetPath& name, TypeID assetType, IAssetCreateInfo&& createInfo );

	///@}


	///@name Reasource freeing api
	///@{
	void							FreeUnusedAssets			();

	///@}


	///@name Listing resources
	///@{
	std::vector< ResourcePointer >						ListAssets			( TypeID assetType ) const;

	template< typename AssetType >
	std::vector< ResourcePtr< AssetType > >				ListAssetsTyped		( TypeID assetType ) const;

	///@}

public:

	///@name Thread unsafe initialization api
	/// These api functions should be called on the beginning of the program.
	/// @todo Consider doing this API thread safe.
	///@{
	bool							RegisterAssetCreator		( IAssetCreatorPtr creator );
	bool							RegisterLoader				( IAssetLoaderPtr loader );

	LoadersVec						ListLoaders					() const;

	PathsManager*					GetPathsManager				() const						{ return m_pathsManager.get(); }
	///@}


protected:

	ResourcePtr< Resource >						FindResource		( const AssetPath& assetName, TypeID assetType );
	ResourcePtr< Resource >						FindRequestedAsset	( const LoadPath& assetName, TypeID assetType, const AssetsVec& loadedAssets );
	IAssetLoader*								FindLoader			( const AssetPath& assetName, TypeID assetType );

	std::pair< WaitingAsset*, bool >			LockFileForLoading	( const LoadPath& assetName );

	sw::Nullable< ResourcePointer >				LoadGeneric			( const LoadPath& assetName, const IAssetLoadInfo* desc, TypeID type );
	sw::Nullable< ResourcePointer >				LoadingImpl			( const LoadPath& assetName, const IAssetLoadInfo* desc, TypeID assetType );

	ReturnResult								AddGenericResource	( const AssetPath& name, TypeID assetType, ResourcePointer resource );

	fs::Path									Translate			( const fs::Path& path );
	AssetPath									Translate			( const AssetPath& name );

    void                                        RegisterBasicLoaders();
};


//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
template< typename AssetType >
inline ResourcePtr< AssetType >						ResourceManager::Get					( const AssetPath& assetName )
{
	auto result = GetGeneric( assetName, TypeID::get< AssetType >() );
	return ResourcePtr< AssetType >( static_cast< AssetType* >( result.Ptr() ) );
}

// ================================ //
//
template< typename AssetType >
inline std::vector< ResourcePtr< AssetType > >		ResourceManager::ListAssetsTyped		( TypeID assetType ) const
{
	auto containerIter = m_resources.find( assetType );
	if( containerIter != m_resources.end() )
	{
		const ResourceContainer< AssetType >& container = containerIter->second;
		return container.List< AssetType >();
	}

	return std::vector< ResourcePtr< AssetType > >();
}

}	// sw

