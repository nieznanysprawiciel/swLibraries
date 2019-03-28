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

#include "swCommonLib/Common/Multithreading/ReaderWriterLock.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"

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

	ReaderWriterLock			m_rwLock;				///< Reader/Writer lock for protecting m_resources dictionary.
	LoadBarrier					m_waitingAssets;		///< Barrier protects from loading one asset multiple times.

	CacheManager				m_cacheManager;			///< Assets cache.
	AssetsFactoryOPtr			m_assetsFactory;		///< Factory for generic and non generic assets creation.

	std::vector< IAssetLoaderOPtr >		m_loaders;		///< File loaders.

public:

	/**@brief This constructor creates default cache and AssetsFactory.*/
	explicit		nResourceManager		();
	virtual			~nResourceManager		();



	RenderTarget*				CreateRenderTarget			( const filesystem::Path& name, const RenderTargetDescriptor& renderTargetDescriptor );

	///@name Geting existing resource
	///@detail Gets resource if exist otherwise returns nullptr.
	///@{

	ResourcePointer				GetGeneric					( const filesystem::Path& name, TypeID type );

	BlendingState*				GetBlendingState			( const filesystem::Path& name );
	RasterizerState*			GetRasterizerState			( const filesystem::Path& name );
	DepthStencilState*			GetDepthStencilState		( const filesystem::Path& name );

	BlendingState*				GetBlendingState			( const BlendingInfo& info );
	RasterizerState*			GetRasterizerState			( const RasterizerStateInfo& info );
	DepthStencilState*			GetDepthStencilState		( const DepthStencilInfo& info );

	RenderTarget*				GetRenderTarget				( const filesystem::Path& name );
	VertexShader*				GetVertexShader				( const filesystem::Path& name );
	PixelShader*				GetPixelShader				( const filesystem::Path& name );
	Texture*					GetTexture					( const filesystem::Path& name );
	Buffer*						GetVertexBuffer				( const filesystem::Path& name );
	Buffer*						GetConstantBuffer			( const filesystem::Path& name );
	Buffer*						GetIndexBuffer				( const filesystem::Path& name );
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

	sw::Nullable< ResourcePointer >	LoadGeneric					( const filesystem::Path& assetName, IAssetLoadInfo* desc, TypeID type );
	///@}

	///@name Resource creation
	///@detail You can create assets in code using these functions. Remember to give unique names for your assets.
	///Engine uses convention, that all generated resources have :: before name, to distinguish them from assets loaded from files.
	///@{
	ResourcePtr< Buffer >			CreateVertexBuffer			( const filesystem::Path& name, const void* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< Buffer >			CreateVertexBuffer			( const filesystem::Path& name, const VertexBufferInitData& data );
	ResourcePtr< Buffer >			CreateIndexBuffer			( const filesystem::Path& name, const void* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< Buffer >			CreateIndexBuffer			( const filesystem::Path& name, const IndexBufferInitData& data );
	ResourcePtr< Buffer >			CreateConstantsBuffer		( const filesystem::Path& name, const void* buffer, unsigned int size );
	ResourcePtr< Buffer >			CreateConstantsBuffer		( const filesystem::Path& name, const ConstantBufferInitData& data );

	ResourcePtr< BlendingState >	CreateBlendingState			( const filesystem::Path& name, const BlendingInfo& info );
	ResourcePtr< RasterizerState >	CreateRasterizerState		( const filesystem::Path& name, const RasterizerStateInfo& info );
	ResourcePtr< DepthStencilState >CreateDepthStencilState		( const filesystem::Path& name, const DepthStencilInfo& info );

	sw::Nullable< ResourcePointer >	CreateGenericAsset			( const filesystem::Path& name, TypeID assetType, IAssetCreateInfo&& createInfo );
	///@}

	RenderTarget*					AddRenderTarget				( RenderTarget* renderTarget, const std::wstring& name );


	///@name Listing resources
	///@{
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

	///@}


protected:

	ResourcePtr< Resource >						FindResource		( const filesystem::Path& assetName, TypeID assetType );
	ResourcePtr< Resource >						FindRequestedAsset	( const filesystem::Path& assetName, TypeID assetType, const AssetsVec& loadedAssets );
	IAssetLoader*								FindLoader			( const filesystem::Path& assetName, TypeID assetType );

	sw::Nullable< ResourcePointer >				LoadingImpl			( const filesystem::Path& assetName, IAssetLoadInfo* desc, TypeID assetType );

	ReturnResult								AddGenericResource	( const filesystem::Path& name, TypeID assetType, ResourcePointer resource );
};

}	// sw

