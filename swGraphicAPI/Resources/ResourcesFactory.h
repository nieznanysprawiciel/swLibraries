#pragma once
/**
@file ResourcesFactory.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/Buffers/BufferRaw.h"


#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"
#include "swGraphicAPI/Resources/PipelineStates/BlendingState.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"
#include "swGraphicAPI/Resources/SwapChain.h"
#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"

#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"





namespace sw
{


class ResourceManager;


class BufferCreator;
class LayoutCreator;
class BlendingStateCreator;
class RasterizerStateCreator;
class DepthStencilStateCreator;
class TextureCreator;

template< typename ShaderObjectType > class ShaderCreator;



/**@brief Class for creating low level graphic API dependent resources.
@ingroup GraphicAPI

This class should be implemented in graphicAPI implementation. At this moment we use link time
binding. In future this could change to virtual class.
*/
class ResourcesFactory
{
	friend class sw::BufferCreator;

	friend class sw::ShaderCreator< VertexShader >;
	friend class sw::ShaderCreator< PixelShader >;
	friend class sw::ShaderCreator< GeometryShader >;
	friend class sw::ShaderCreator< EvaluationShader >;
	friend class sw::ShaderCreator< ControlShader >;
	friend class sw::ShaderCreator< ComputeShader >;
	friend class sw::LayoutCreator;
	friend class sw::BlendingStateCreator;
	friend class sw::RasterizerStateCreator;
	friend class sw::DepthStencilStateCreator;
	friend class sw::TextureCreator;


private:

	static sw::Nullable< VertexShader* >		CreateVertexShader				( const AssetPath& name, const std::string& code, const std::string& entrypoint );
	static sw::Nullable< PixelShader* >			CreatePixelShader				( const AssetPath& name, const std::string& code, const std::string& entrypoint );
	static sw::Nullable< ComputeShader* >		CreateComputeShader				( const AssetPath& name, const std::string& code, const std::string& entrypoint );

	static sw::Nullable< ShaderInputLayout* >	CreateInputLayout				( const AssetPath& name, const InputLayoutDescriptor& layoutDesc );

	static sw::Nullable< Texture* >				CreateTextureFromMemory			( const AssetPath& name, const BufferRaw& texData, sw::TextureInfo&& texInfo );
	static sw::Nullable< Buffer* >				CreateBufferFromMemory			( const AssetPath& name, const uint8* data, const BufferInfo& bufferInfo );

	static sw::Nullable< BlendingState*	>		CreateBlendingState				( const AssetPath& name, const BlendingInfo& info );
	static sw::Nullable< RasterizerState* >		CreateRasterizerState			( const AssetPath& name, const RasterizerStateInfo& info );
	static sw::Nullable< DepthStencilState* >	CreateDepthStencilState			( const AssetPath& name, const DepthStencilInfo& info );


	static Texture*								CreateTextureFromMemory			( const MemoryChunk& texData, sw::TextureInfo&& texInfo );

	static VertexShader*					CreateVertexShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );
	static PixelShader*						CreatePixelShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "ps_4_0" );
	static GeometryShader*					CreateGeometryShaderFromFile	( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "gs_4_0" );
	static EvaluationShader*				CreateEvaluationShaderFromFile	( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "hs_4_0" );
	static ControlShader*					CreateControlShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "ds_4_0" );
	static ComputeShader*					CreateComputeShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "cs_4_0" );


	static VertexShader*			CreateVertexShaderFromFile		( const std::wstring& fileName,
																	  const std::string& shaderName,
																	  ShaderInputLayout** layout,
																	  InputLayoutDescriptor* layout_desc,
																	  const char* shaderModel = "vs_4_0" );

public:
	static IGraphicAPIInitializer*				CreateAPIInitializer			();
	static RenderTarget*						CreateScreenRenderTarget		();
	static SwapChain*							CreateScreenSwapChain			( RenderTarget* screenRT );
	static InputLayoutDescriptor*				CreateInputLayoutDescriptor		( const std::wstring& layoutName );
	static sw::Nullable< RenderTarget* >		CreateRenderTarget				( const AssetPath& name, const RenderTargetDescriptor& renderTargetDescriptor );
};


}	// sw