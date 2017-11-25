/**
@file ResourcesFactory.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "swGraphicAPI/Resources/ResourcesFactory.h"
#include "MockInitializer/MockInitializer.h"

#include "MockVertexShader.h"
#include "MockPixelShader.h"
#include "MockComputeShader.h"
#include "MockBuffer.h"
#include "MockTexture.h"
#include "MockRenderTarget.h"
#include "MockInputLayoutDescriptor.h"
#include "MockInputLayout.h"
#include "MockSwapChain.h"
#include "MockPipelineState.h"





typedef sw::MockTexture				Texture;
typedef sw::MockVertexShader		VertexShaderObject;
typedef sw::MockPixelShader			PixelShaderObject;
typedef sw::MockBuffer				Buffer;
typedef sw::MockComputeShader		ComputeShaderObject;
typedef sw::MockDepthStencilState	DepthStencilStateObject;
typedef sw::MockRasterizerState		RasterizerStateObject;
typedef sw::MockBlendingState		BlendingStateObject;

/**@brief Tworzy teksturê z podanego deskryptora.*/
TextureObject*			ResourcesFactory::CreateTextureFromMemory	( const MemoryChunk& texData, TextureInfo&& texInfo )
{
	return Texture::CreateFromMemory( texData, std::move( texInfo ) );
}


/**@brief Tworzy obiekt vertex shadera.

@param[in] fileName Nazwa pliku z kodem shadera.
@param[in] shaderName Nazwa funkcji, od której ma siê rozpocz¹æ wykonanie programu shadera.
@param[in] shaderModel Shader model.
@return Zwraca obiekt vertex shadera lub nullptr w przypadku niepowodzenia.*/
VertexShader*		ResourcesFactory::CreateVertexShaderFromFile( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	auto shader = VertexShaderObject::CreateFromFile( fileName, shaderName, shaderModel );
	if( shader )
	{
		shader->SetFileName( fileName );
		shader->SetShaderName( shaderName );
	}
	return shader;
}

/**@brief Tworzy obiekt vertex shadera oraz layout wierzcho³ka.

@param[in] fileName Nazwa pliku z kodem shadera.
@param[in] shaderName Nazwa funkcji, od której ma siê rozpocz¹æ wykonanie programu shadera.
@param[out] layout Zwraca obiekt layoutu.
@param[in] layoutDesc Deskryptor opisuj¹cy layout.
@param[in] shaderModel Shader model.
@return Zwraca obiekt vertex shadera lub nullptr w przypadku niepowodzenia.*/
VertexShader*		ResourcesFactory::CreateVertexShaderFromFile	( const std::wstring& fileName,
																		const std::string& shaderName,
																		ShaderInputLayout** layout,
																		InputLayoutDescriptor* layoutDesc,
																		const char* shaderModel/* = "vs_4_0"*/ )
{
	auto shader = VertexShaderObject::CreateFromFile( fileName, shaderName, layout, layoutDesc, shaderModel );
	if( shader )
	{
		shader->SetFileName( fileName );
		shader->SetShaderName( shaderName );
	}
	return shader;
}

/**@brief Creates BlendingState.*/
BlendingState*		ResourcesFactory::CreateBlendingState		( const BlendingInfo& info )
{
	return BlendingStateObject::Create( info );
}

/**@brief Creates RasterizerState*/
RasterizerState*	ResourcesFactory::CreateRasterizerState		( const RasterizerStateInfo& info )
{
	return RasterizerStateObject::Create( info );
}

/**@brief Creates DepthStencilState.*/
DepthStencilState*	ResourcesFactory::CreateDepthStencilState	( const DepthStencilInfo& info )
{
	return DepthStencilStateObject::Create( info );
}


/**@brief Tworzy obekt pixel shadera.
@param[in] fileName Nazwa pliku z kodem shadera.
@param[in] shaderName Nazwa funkcji, od której ma siê rozpocz¹æ wykonanie programu shadera.
@param[in] shaderModel Shader model.
@return Zwraca obiekt vertex shadera lub nullptr w przypadku niepowodzenia.*/
PixelShader*		ResourcesFactory::CreatePixelShaderFromFile( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	auto shader = PixelShaderObject::CreateFromFile( fileName, shaderName, shaderModel );
	if( shader )
	{
		shader->SetFileName( fileName );
		shader->SetShaderName( shaderName );
	}
	return shader;
}

/**@brief Tworzy obekt compute shadera.
@param[in] fileName Nazwa pliku z kodem shadera.
@param[in] shaderName Nazwa funkcji, od której ma siê rozpocz¹æ wykonanie programu shadera.
@param[in] shaderModel Shader model.
@return Zwraca obiekt vertex shadera lub nullptr w przypadku niepowodzenia.*/
ComputeShader*		ResourcesFactory::CreateComputeShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	return ComputeShaderObject::CreateFromFile( fileName, shaderName, shaderModel );
}


/**@brief Tworzy bufor na podstawie sanych w pamiêci.

@param[in] name Buffer name or file path.
@param[in] data Pointer to initialization data. Memory can be released after call.
@param[in] bufferInfo Buffer descriptor.
@return Zwraca wskaŸnik na obiekt bufora lub nullptr w przypadku niepowodzenia.*/
BufferObject*			ResourcesFactory::CreateBufferFromMemory		( const std::wstring& name, const uint8* data, const BufferInfo& bufferInfo )
{
	return Buffer::CreateFromMemory( name, data, bufferInfo );
}

/**Tworzy object RenderTargetObject z bufora tylnego ekranu.

@return Zwraca object RenderTargetObject.*/
RenderTargetObject*		ResourcesFactory::CreateScreenRenderTarget()
{
	return sw::MockRenderTarget::CreateScreenRenderTarget();
}

SwapChain*				ResourcesFactory::CreateScreenSwapChain( RenderTargetObject* screenRT )
{
	return sw::MockSwapChain::CreateScreenSwapChain( screenRT );
}

IGraphicAPIInitializer* ResourcesFactory::CreateAPIInitializer()
{
	return new sw::MockInitializer();
}

/**Tworzy obiekt deskryptora layoutu.*/
InputLayoutDescriptor* ResourcesFactory::CreateInputLayoutDescriptor( const std::wstring& layoutName )
{
	return new sw::MockInputLayoutDescriptor( layoutName );
}

RenderTargetObject* ResourcesFactory::CreateRenderTarget( const std::wstring& name, const RenderTargetDescriptor& renderTargetDescriptor )
{
	return sw::MockRenderTarget::CreateRenderTarget( name, renderTargetDescriptor );
}

