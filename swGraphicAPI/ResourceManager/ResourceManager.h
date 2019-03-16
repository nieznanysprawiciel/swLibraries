#pragma once
/**
@file ResourceManager.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/PipelineStates/BlendingState.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"
#include "swGraphicAPI/ResourceManager/ResourceContainer.h"


class ILoader;

/**@defgroup AssetsManagement Assets Management
@brief Class for loading assets and managing their lifetime.
@ingroup GraphicAPI

@copydoc ResourceManagerRequirements

@page ResourceManagerRequirements Resource Manager Requirements

@section RMRequirements ResourceManager requirements

1. ResourceManager supports generic assets types defined by future users. It should also expose special functions
for built in low level types without need to use this generic API, but these types should be also avaible through generic API.
2. User can write his own implementations of loaders for different file types. ResourceManager finds best matching loader and uses
it to load asset.
Loaders implement generic interface, but user can also add parameters for specific loader. For example FBX SDK loader could load
Meshes and merge them all in one asset or it could create several assets for all parts.
3. Asynchronous assets loading. Assets can be loaded in separate thread. User provides callback function which will be called
when asset is ready.
 - There's separate API for synchronous and asynchronous loading.
 - Request can come from multiple threads. In case of synchronous load, when multiple threads want to load the same asset,
 all threads are blocked until asset is loaded. ResourceManager takes care of dealing with these conflicts and prevents from loading
 same asset multiple times.
 - Internal implementation uses only one thread for loading. This should be enough for high performance, since disk access is bottleneck.
4. Paths translation. Some assets' directory can depend on graphic API which is being used (for example shaders glsl or hlsl).
User can register Paths Translators in ResourceManager to solve this problem. Paths Translators are fully user defined so can be used for
different purposes too.
Moreover ResourceManager supports packed file which internally consist of many smaller files. This goal is reached by using special naming
convention. ::sings separate file name paths from each other.
5. Assets caching. Asssets can be cached in RAM memory in raw form to speed up creating. Second cach level can exist on SSD drive.
Cache automatically manages resources. It supports maximal memory occupancy limit. It supports user defined API for prefetching data.
6. Support for logging mechanism. This mechanism is independent from logger implementation (maybe callback).
7. Support for level of detailes.
8. Support for asset streaming.
9. Support for hot reload of shaders and other assets wher possible.
*/



/**@brief Manager for low level resources.

@todo This class should implement generic high level asssets managment.

@ingroup AssetsManagement*/
class ResourceManager
{
private:
protected:
	ResourceContainer< sw::BlendingState >			m_blendingState;	///< BlendingState objects.
	ResourceContainer< sw::RasterizerState >		m_rasterizerState;	///< RasterizerState objects.
	ResourceContainer< sw::DepthStencilState >		m_depthStencilState;///< DepthStencilState objects.

	ResourceContainer< sw::VertexShader >			m_vertexShader;		///< Vertex shaders.
	ResourceContainer< sw::PixelShader >			m_pixelShader;		///< Pixel shaders.
	ResourceContainer< sw::GeometryShader >			m_geometryShader;	///< Geometry shaders.
	ResourceContainer< sw::EvaluationShader >		m_evaluationShader;	///< Tesselation evaluation shaders.
	ResourceContainer< sw::ControlShader >			m_controlShaders;	///< Tesselation control shaders.

	ResourceContainer< sw::Texture >				m_texture;			///< Textures.
	ResourceContainer< sw::Buffer >			m_vertexBuffer;		///< Vertex buffers.
	ResourceContainer< sw::Buffer >			m_indexBuffer;		///< Index buffers.
	ResourceContainer< sw::Buffer >			m_constantBuffer;	///< Shader constant buffers.
	ResourceContainer< sw::ShaderInputLayout >		m_vertexLayout;		///< Vertex layouts.
	// UWAGA! m_fileModel musi byæ na koñcu. Jego destruktor kasuje odwo³ania do obiektów powy¿ej. Podobnie RenderTargetObject odwo³uje siê do tekstur.
	// Musz¹ one w tym czasie istnieæ, a destruktory s¹ wywo³ywane w kolejnoœci odwrotnej do zadeklarowanej w klasie.
	ResourceContainer< sw::RenderTargetObject >		m_renderTarget;		///<Obiekty mog¹ce s³u¿yæ za render target.

	/*loadery dla ró¿nych formatów plików z modelami*/
	//std::vector<ILoader*>						m_loader;				///<Loadery do plików z modelami 3D

public:
	explicit						ResourceManager();
	virtual							~ResourceManager();

	// Funkcje do zarz¹dzania assetami
	sw::RenderTargetObject*			CreateRenderTarget			( const std::wstring& name, const sw::RenderTargetDescriptor& renderTargetDescriptor );

	///@name Geting existing resource
	///@detail Gets resource if exist otherwise returns nullptr.
	///@{

	inline sw::BlendingState*			GetBlendingState			( const std::wstring& name )		{ return m_blendingState.get( name ); }
	inline sw::RasterizerState*			GetRasterizerState			( const std::wstring& name )		{ return m_rasterizerState.get( name ); }
	inline sw::DepthStencilState*		GetDepthStencilState		( const std::wstring& name )		{ return m_depthStencilState.get( name ); }

	inline sw::BlendingState*			GetBlendingState			( const sw::BlendingInfo& info )		{ return m_blendingState.Find( info ); }
	inline sw::RasterizerState*			GetRasterizerState			( const sw::RasterizerStateInfo& info ) { return m_rasterizerState.Find( info ); }
	inline sw::DepthStencilState*		GetDepthStencilState		( const sw::DepthStencilInfo& info )	{ return m_depthStencilState.Find( info ); }

	inline sw::RenderTargetObject*		GetRenderTarget				( const std::wstring& name ) { return m_renderTarget.get( name ); }	///<Zwraca RenderTarget o podanej nazwie, je¿eli jest wczytany.
	inline sw::VertexShader*			GetVertexShader				( const std::wstring& name ) { return m_vertexShader.get( name ); } ///<Zwraca vertex shader o podanej nazwie, je¿eli jest wczytany.
	inline sw::PixelShader*				GetPixelShader				( const std::wstring& name ) { return m_pixelShader.get( name ); }	///<Zwraca pixel shader o podanej nazwie, je¿eli jest wczytany.
	inline sw::Texture*					GetTexture					( const std::wstring& name ) { return m_texture.get( name ); }		///<Zwraca teksturê o podanej nazwie, je¿eli jest wczytany.
	inline sw::Buffer*			GetVertexBuffer				( const std::wstring& name ) { return m_vertexBuffer.get( name ); }	///<Zwraca bufor wierzcho³ków o podanej nazwie, je¿eli jest wczytany.
	inline sw::Buffer*			GetConstantBuffer			( const std::wstring& name ) { return m_constantBuffer.get( name ); }	///<Zwraca bufor sta³ych o podanej nazwie, je¿eli jest wczytany.
	inline sw::Buffer*			GetIndexBuffer				( const std::wstring& name ) { return m_indexBuffer.get( name ); }	///<Zwraca bufor indeksów o podanej nazwie, je¿eli jest wczytany.
	inline sw::ShaderInputLayout*		GetLayout					( const std::wstring& name ) { return m_vertexLayout.get( name ); }	///<Zwraca layout o podanej nazwie.	
	///@}


	///@name Resource loading
	///@detail Load assets from specified file. Functions protect from loading assets multiple times.
	///@{
	sw::Texture*						LoadTexture					( const std::wstring& fileName );
	sw::VertexShader*					LoadVertexShader			( const std::wstring& fileName, const std::string& shaderEntry );
	sw::VertexShader*					LoadVertexShader			( const std::wstring& fileName, const std::string& shaderEntry, sw::ShaderInputLayout** layout, sw::InputLayoutDescriptor* layout_desc );
	sw::PixelShader*					LoadPixelShader				( const std::wstring& fileName, const std::string& shaderEntry );
	sw::GeometryShader*					LoadGeometryShader			( const std::wstring& fileName, const std::string& shaderEntry );
	sw::ControlShader*					LoadControlShader			( const std::wstring& fileName, const std::string& shaderEntry );
	sw::EvaluationShader*				LoadEvaluationShader		( const std::wstring& fileName, const std::string& shaderEntry );
	///@}

	///@name Resource creation
	///@detail You can create assets in code using these functions. Remember to give unique names for your assets.
	///Engine uses convention, that all generated resources have :: before name, to distinguish them from assets loaded from files.
	///@{
	sw::ResourcePtr< sw::Buffer >		CreateVertexBuffer			( const std::wstring& name, const void* buffer, unsigned int element_size, unsigned int vert_count );
	sw::ResourcePtr< sw::Buffer >		CreateVertexBuffer			( const std::wstring& name, const sw::VertexBufferInitData& data );
	sw::ResourcePtr< sw::Buffer >		CreateIndexBuffer			( const std::wstring& name, const void* buffer, unsigned int element_size, unsigned int vert_count );
	sw::ResourcePtr< sw::Buffer >		CreateIndexBuffer			( const std::wstring& name, const sw::IndexBufferInitData& data );
	sw::ResourcePtr< sw::Buffer >		CreateConstantsBuffer		( const std::wstring& name, const void* buffer, unsigned int size );
	sw::ResourcePtr< sw::Buffer >		CreateConstantsBuffer		( const std::wstring& name, const sw::ConstantBufferInitData& data );

	sw::ResourcePtr< sw::BlendingState >	CreateBlendingState			( const std::wstring& name, const sw::BlendingInfo& info );
	sw::ResourcePtr< sw::RasterizerState >	CreateRasterizerState		( const std::wstring& name, const sw::RasterizerStateInfo& info );
	sw::ResourcePtr< sw::DepthStencilState >CreateDepthStencilState		( const std::wstring& name, const sw::DepthStencilInfo& info );

	///@}

	sw::RenderTargetObject*				AddRenderTarget				( sw::RenderTargetObject* renderTarget, const std::wstring& name );


	///@name Listing resources
	///@{
	std::vector< sw::ResourcePtr< sw::Buffer > >			ListVertexBuffers	();
	std::vector< sw::ResourcePtr< sw::Buffer > >			ListIndexBuffers	();
	std::vector< sw::ResourcePtr< sw::Buffer > >			ListConstantBuffers	();
	std::vector< sw::ResourcePtr< sw::ShaderInputLayout > >		ListShaderLayouts	();

	std::vector< sw::ResourcePtr< sw::Texture > >				ListTextures		();
	std::vector< sw::ResourcePtr< sw::VertexShader > >			ListVertexShaders	();
	std::vector< sw::ResourcePtr< sw::PixelShader > >			ListPixelShaders	();
	
	std::vector< sw::ResourcePtr< sw::RenderTargetObject > >	ListRenderTargets	();
	///@}

private:
	//ILoader*						FindLoader					( const std::wstring& path );
	
	virtual MemoryChunk				LoadTextureImpl				( const filesystem::Path& filePath, sw::TextureInfo& texInfo );
};

