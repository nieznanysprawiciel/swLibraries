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





typedef sw::MockTexture				TextureObject;
typedef sw::MockVertexShader		VertexShaderObject;
typedef sw::MockPixelShader			PixelShaderObject;
typedef sw::MockBuffer				BufferObject;
typedef sw::MockComputeShader		ComputeShaderObject;
typedef sw::MockDepthStencilState	DepthStencilStateObject;
typedef sw::MockRasterizerState		RasterizerStateObject;
typedef sw::MockBlendingState		BlendingStateObject;




namespace sw
{


// ================================ //
//
sw::Nullable< VertexShader* >		ResourcesFactory::CreateVertexShader			( const AssetPath& fileName, const std::string& code, const std::string& entrypoint )
{
	return VertexShaderObject::CreateFromCode( fileName, code, entrypoint );
}

// ================================ //
//
sw::Nullable< PixelShader* >		ResourcesFactory::CreatePixelShader				( const AssetPath& fileName, const std::string& code, const std::string& entrypoint )
{
	return PixelShaderObject::CreateFromCode( fileName, code, entrypoint );
}

// ================================ //
//
sw::Nullable< ComputeShader* >		ResourcesFactory::CreateComputeShader			( const AssetPath& fileName, const std::string& code, const std::string& entrypoint )
{
	return ComputeShaderObject::CreateFromCode( fileName, code, entrypoint );
}

// ================================ //
//
sw::Nullable< ShaderInputLayout* >	ResourcesFactory::CreateInputLayout				( const AssetPath& name, const InputLayoutDescriptor& layoutDesc )
{
	return sw::MockInputLayout::CreateLayout( name, layoutDesc );
}

// ================================ //
//
sw::Nullable< Texture* >			ResourcesFactory::CreateTextureFromMemory		( const AssetPath& name, const BufferRaw& texData, sw::TextureInfo&& texInfo )
{
	return TextureObject::CreateFromMemory( name, texData, std::move( texInfo ) );
}

/**@brief Creates BlendingState.*/
sw::Nullable< BlendingState* >		ResourcesFactory::CreateBlendingState		( const AssetPath& name, const BlendingInfo& info )
{
	return BlendingStateObject::Create( name, info );
}

/**@brief Creates RasterizerState*/
sw::Nullable< RasterizerState* >	ResourcesFactory::CreateRasterizerState		( const AssetPath& name, const RasterizerStateInfo& info )
{
	return RasterizerStateObject::Create( name, info );
}

/**@brief Creates DepthStencilState.*/
sw::Nullable< DepthStencilState* >	ResourcesFactory::CreateDepthStencilState	( const AssetPath& name, const DepthStencilInfo& info )
{
	return DepthStencilStateObject::Create( name, info );
}

/**@brief Tworzy bufor na podstawie sanych w pamiêci.

@param[in] name Buffer name or file path.
@param[in] data Pointer to initialization data. Memory can be released after call.
@param[in] bufferInfo Buffer descriptor.
@return Zwraca wskaŸnik na obiekt bufora lub nullptr w przypadku niepowodzenia.*/
sw::Nullable< Buffer* >					ResourcesFactory::CreateBufferFromMemory		( const AssetPath& name, const uint8* data, const BufferInfo& bufferInfo )
{
	return BufferObject::CreateFromMemory( name, data, bufferInfo );
}

/**Tworzy object RenderTarget z bufora tylnego ekranu.

@return Zwraca object RenderTarget.*/
RenderTarget*						    ResourcesFactory::CreateScreenRenderTarget		()
{
	return sw::MockRenderTarget::CreateScreenRenderTarget();
}

// ================================ //
//
SwapChain*								ResourcesFactory::CreateScreenSwapChain			( RenderTarget* screenRT )
{
	return sw::MockSwapChain::CreateScreenSwapChain( screenRT );
}

// ================================ //
//
IGraphicAPIInitializer*					ResourcesFactory::CreateAPIInitializer			()
{
	return new sw::MockInitializer();
}

// ================================ //
//
sw::Nullable< RenderTarget* >			ResourcesFactory::CreateRenderTarget			( const AssetPath& name, const RenderTargetDescriptor& renderTargetDescriptor )
{
	return sw::MockRenderTarget::CreateRenderTarget( name, renderTargetDescriptor );
}


}	// sw


