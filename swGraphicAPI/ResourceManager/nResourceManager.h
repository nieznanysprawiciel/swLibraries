#pragma once
/**
@file nResourceManager.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/PipelineStates/BlendingState.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"

#include "swGraphicAPI/ResourceManager/nResourceContainer.h"
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


typedef std::vector< IAssetLoaderPtr > LoadersVec;


/**@brief Future implementation of ResourceManager.


@ingroup AssetsManagement*/
class nResourceManager
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
	explicit		nResourceManager		();
	virtual			~nResourceManager		();



	RenderTarget*				CreateRenderTarget			( const AssetPath& name, const RenderTargetDescriptor& renderTargetDescriptor );

	///@name Geting existing resource
	///@detail Gets resource if exist otherwise returns nullptr.
	///@{

	ResourcePointer				GetGeneric					( const AssetPath& name, TypeID type );

	template< typename AssetType >
	ResourcePtr< AssetType >	Get							( const AssetPath& name );

	BlendingState*				GetBlendingState			( const AssetPath& name );
	RasterizerState*			GetRasterizerState			( const AssetPath& name );
	DepthStencilState*			GetDepthStencilState		( const AssetPath& name );

	BlendingState*				GetBlendingState			( const BlendingInfo& info );
	RasterizerState*			GetRasterizerState			( const RasterizerStateInfo& info );
	DepthStencilState*			GetDepthStencilState		( const DepthStencilInfo& info );

	RenderTarget*				GetRenderTarget				( const AssetPath& name );
	VertexShader*				GetVertexShader				( const AssetPath& name );
	PixelShader*				GetPixelShader				( const AssetPath& name );
	Texture*					GetTexture					( const AssetPath& name );
	Buffer*						GetVertexBuffer				( const AssetPath& name );
	Buffer*						GetConstantBuffer			( const AssetPath& name );
	Buffer*						GetIndexBuffer				( const AssetPath& name );
	ShaderInputLayout*			GetLayout					( const AssetPath& name );
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
	ResourcePtr< Buffer >			CreateVertexBuffer			( const AssetPath& name, const void* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< Buffer >			CreateVertexBuffer			( const AssetPath& name, const VertexBufferInitData& data );
	ResourcePtr< Buffer >			CreateIndexBuffer			( const AssetPath& name, const void* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< Buffer >			CreateIndexBuffer			( const AssetPath& name, const IndexBufferInitData& data );
	ResourcePtr< Buffer >			CreateConstantsBuffer		( const AssetPath& name, const void* buffer, unsigned int size );
	ResourcePtr< Buffer >			CreateConstantsBuffer		( const AssetPath& name, const ConstantBufferInitData& data );

	ResourcePtr< BlendingState >	CreateBlendingState			( const AssetPath& name, const BlendingInfo& info );
	ResourcePtr< RasterizerState >	CreateRasterizerState		( const AssetPath& name, const RasterizerStateInfo& info );
	ResourcePtr< DepthStencilState >CreateDepthStencilState		( const AssetPath& name, const DepthStencilInfo& info );

	sw::Nullable< ResourcePointer >	CreateGenericAsset			( const AssetPath& name, TypeID assetType, IAssetCreateInfo&& createInfo );
	///@}

	RenderTarget*					AddRenderTarget				( RenderTarget* renderTarget, const std::wstring& name );

	///@name Reasource freeing api
	///@{
	void							FreeUnusedAssets			();

	///@}


	///@name Listing resources
	///@{
	std::vector< ResourcePointer >						ListAssets			( TypeID assetType ) const;

	template< typename AssetType >
	std::vector< ResourcePtr< AssetType > >				ListAssetsTyped		( TypeID assetType ) const;

	std::vector< ResourcePtr< Buffer > >				ListVertexBuffers	();
	std::vector< ResourcePtr< Buffer > >				ListIndexBuffers	();
	std::vector< ResourcePtr< Buffer > >				ListConstantBuffers	();
	std::vector< ResourcePtr< ShaderInputLayout > >		ListShaderLayouts	();

	std::vector< ResourcePtr< Texture > >				ListTextures		();
	std::vector< ResourcePtr< VertexShader > >			ListVertexShaders	();
	std::vector< ResourcePtr< PixelShader > >			ListPixelShaders	();
	
	std::vector< ResourcePtr< RenderTarget > >			ListRenderTargets	();
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

	filesystem::Path							Translate			( const filesystem::Path& path );
	AssetPath									Translate			( const AssetPath& name );
};


//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
template< typename AssetType >
inline ResourcePtr< AssetType >						nResourceManager::Get					( const AssetPath& assetName )
{
	auto result = GetGeneric( assetName, TypeID::get< AssetType >() );
	return ResourcePtr< AssetType >( static_cast< AssetType* >( result.Ptr() ) );
}

// ================================ //
//
template< typename AssetType >
inline std::vector< ResourcePtr< AssetType > >		nResourceManager::ListAssetsTyped		( TypeID assetType ) const
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

