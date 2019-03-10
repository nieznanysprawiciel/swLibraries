#pragma once
/**
@file nResourceManager.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/BlendingState.h"
#include "swGraphicAPI/Resources/RasterizerState.h"
#include "swGraphicAPI/Resources/DepthStencilState.h"
#include "swGraphicAPI/ResourceManager/nResourceContainer.h"

#include "swCommonLib/Common/Multithreading/ReaderWriterLock.h"

#include "AssetCreators/AssetsFactory.h"
#include "IAssetLoader.h"
#include "Cache/CacheManager.h"
#include "AsyncLoad/LoadBarrier.h"

#include <vector>
#include <map>



namespace sw
{


typedef std::vector< ResourcePtr< Resource > > AssetsVec;


/**@brief Future implementation of ResourceManager.


@ingroup AssetsManagement*/
class nResourceManager
{
	typedef std::map< TypeID, ResourceContainer< Resource > > ResourcesMap;

private:
protected:

	ResourcesMap				m_resources;

	ReaderWriterLock			m_rwLock;
	LoadBarrier					m_waitingAssets;		///< Barrier protects from loading one asset multiple times.

	CacheManager				m_cacheManager;			///< Assets cache.
	AssetsFactoryOPtr			m_assetsFactory;		///< Factory for generic and non generic assets creation.

	std::vector< IAssetLoaderOPtr >		m_loaders;		///< File loaders.

public:

	/**@brief This constructor creates default cache and AssetsFactory.*/
	explicit		nResourceManager		();
	virtual			~nResourceManager		();



	RenderTargetObject*			CreateRenderTarget			( const filesystem::Path& name, const RenderTargetDescriptor& renderTargetDescriptor );

	///@name Geting existing resource
	///@detail Gets resource if exist otherwise returns nullptr.
	///@{

	BlendingState*				GetBlendingState			( const filesystem::Path& name );
	RasterizerState*			GetRasterizerState			( const filesystem::Path& name );
	DepthStencilState*			GetDepthStencilState		( const filesystem::Path& name );

	BlendingState*				GetBlendingState			( const BlendingInfo& info );
	RasterizerState*			GetRasterizerState			( const RasterizerStateInfo& info );
	DepthStencilState*			GetDepthStencilState		( const DepthStencilInfo& info );

	RenderTargetObject*			GetRenderTarget				( const filesystem::Path& name );
	VertexShader*				GetVertexShader				( const filesystem::Path& name );
	PixelShader*				GetPixelShader				( const filesystem::Path& name );
	Texture*					GetTexture					( const filesystem::Path& name );
	BufferObject*				GetVertexBuffer				( const filesystem::Path& name );
	BufferObject*				GetConstantBuffer			( const filesystem::Path& name );
	BufferObject*				GetIndexBuffer				( const filesystem::Path& name );
	ShaderInputLayout*			GetLayout					( const filesystem::Path& name );
	///@}


	///@name Resource loading
	///@detail Load assets from specified file. Functions protect from loading assets multiple times.
	///@{
	Texture*						LoadTexture					( const filesystem::Path& fileName );
	VertexShader*					LoadVertexShader			( const filesystem::Path& fileName, const std::string& shaderEntry );
	VertexShader*					LoadVertexShader			( const filesystem::Path& fileName, const std::string& shaderEntry, ShaderInputLayout** layout, InputLayoutDescriptor* layout_desc );
	PixelShader*					LoadPixelShader				( const filesystem::Path& fileName, const std::string& shaderEntry );
	GeometryShader*					LoadGeometryShader			( const filesystem::Path& fileName, const std::string& shaderEntry );
	ControlShader*					LoadControlShader			( const filesystem::Path& fileName, const std::string& shaderEntry );
	EvaluationShader*				LoadEvaluationShader		( const filesystem::Path& fileName, const std::string& shaderEntry );

	ResourcePtr< Resource >			LoadGeneric					( const filesystem::Path& assetName, IAssetLoadInfo* desc, TypeID type );
	///@}

	///@name Resource creation
	///@detail You can create assets in code using these functions. Remember to give unique names for your assets.
	///Engine uses convention, that all generated resources have :: before name, to distinguish them from assets loaded from files.
	///@{
	ResourcePtr< BufferObject >		CreateVertexBuffer			( const filesystem::Path& name, const void* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< BufferObject >		CreateVertexBuffer			( const filesystem::Path& name, const VertexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const filesystem::Path& name, const void* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const filesystem::Path& name, const IndexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const filesystem::Path& name, const void* buffer, unsigned int size );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const filesystem::Path& name, const ConstantBufferInitData& data );

	ResourcePtr< BlendingState >	CreateBlendingState			( const filesystem::Path& name, const BlendingInfo& info );
	ResourcePtr< RasterizerState >	CreateRasterizerState		( const filesystem::Path& name, const RasterizerStateInfo& info );
	ResourcePtr< DepthStencilState >CreateDepthStencilState		( const filesystem::Path& name, const DepthStencilInfo& info );

	ResourcePtr< Resource >			CreateGenericAsset			( const filesystem::Path& name, TypeID assetType, IAssetCreateInfo&& createInfo );
	///@}

	RenderTargetObject*				AddRenderTarget				( RenderTargetObject* renderTarget, const std::wstring& name );


	///@name Listing resources
	///@{
	std::vector< ResourcePtr< BufferObject > >			ListVertexBuffers	();
	std::vector< ResourcePtr< BufferObject > >			ListIndexBuffers	();
	std::vector< ResourcePtr< BufferObject > >			ListConstantBuffers	();
	std::vector< ResourcePtr< ShaderInputLayout > >		ListShaderLayouts	();

	std::vector< ResourcePtr< Texture > >				ListTextures		();
	std::vector< ResourcePtr< VertexShader > >			ListVertexShaders	();
	std::vector< ResourcePtr< PixelShader > >			ListPixelShaders	();
	
	std::vector< ResourcePtr< RenderTargetObject > >	ListRenderTargets	();
	///@}

protected:

	ResourcePtr< Resource >						FindResource		( const filesystem::Path& assetName, TypeID assetType );
	ResourcePtr< Resource >						FindRequestedAsset	( const filesystem::Path& assetName, TypeID assetType, const AssetsVec& loadedAssets );
	IAssetLoader*								FindLoader			( const filesystem::Path& assetName, TypeID assetType );

	ResourcePtr< Resource >						LoadingImpl			( const filesystem::Path& assetName, IAssetLoadInfo* desc, TypeID assetType );
};

}	// sw

