#pragma once
/**
@file ResourcesFactory.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/RasterizerState.h"
#include "swGraphicAPI/Resources/BlendingState.h"
#include "swGraphicAPI/Resources/DepthStencilState.h"
#include "swGraphicAPI/Resources/SwapChain.h"
#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"

class AssetsManager;

namespace sw
{
	class BufferCreator;

	template< typename ShaderObjectType > class ShaderCreator;
}


/**@brief Klasa ze statycznymi funkcjami do tworzenia obiekt�w asset�w.
@ingroup GraphicAPI

Jest potrzebna, �eby wybra� implementacj� resourc�w zgodn� z typem renderera.
Ka�de API graficzne powinno zaimplementowa� t� klas�.
*/
class ResourcesFactory
{
	friend class ResourceManager;
	friend class AssetsManager;
	friend class sw::BufferCreator;

	friend class sw::ShaderCreator< VertexShader >;
	friend class sw::ShaderCreator< PixelShader >;
	friend class sw::ShaderCreator< GeometryShader >;
	friend class sw::ShaderCreator< EvaluationShader >;
	friend class sw::ShaderCreator< ControlShader >;
	friend class sw::ShaderCreator< ComputeShader >;

private:
	static TextureObject*			CreateTextureFromMemory			( const MemoryChunk& texData, TextureInfo&& texInfo );

	static VertexShader*			CreateVertexShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );
	static PixelShader*				CreatePixelShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "ps_4_0" );
	static GeometryShader*			CreateGeometryShaderFromFile	( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "gs_4_0" );
	static EvaluationShader*		CreateEvaluationShaderFromFile	( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "hs_4_0" );
	static ControlShader*			CreateControlShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "ds_4_0" );
	static ComputeShader*			CreateComputeShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "cs_4_0" );

	static BufferObject*			CreateBufferFromMemory			( const std::wstring& name, const uint8* data, const BufferInfo& bufferInfo );

	static VertexShader*			CreateVertexShaderFromFile		( const std::wstring& fileName,
																	const std::string& shaderName,
																	ShaderInputLayout** layout,
																	InputLayoutDescriptor* layout_desc,
																	const char* shaderModel = "vs_4_0" );

	static BlendingState*			CreateBlendingState				( const BlendingInfo& info );
	static RasterizerState*			CreateRasterizerState			( const RasterizerStateInfo& info );
	static DepthStencilState*		CreateDepthStencilState			( const DepthStencilInfo& info );

public:
	static IGraphicAPIInitializer*	CreateAPIInitializer			();
	static RenderTargetObject*		CreateScreenRenderTarget		();
	static SwapChain*				CreateScreenSwapChain			( RenderTargetObject* screenRT );
	static InputLayoutDescriptor*	CreateInputLayoutDescriptor		( const std::wstring& layoutName );
	static RenderTargetObject*		CreateRenderTarget				( const std::wstring& name, const RenderTargetDescriptor& renderTargetDescriptor );
};

