/**
@file ResourcesFactory.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/DX11API/stdafx.h"

#include "swGraphicAPI/Resources/ResourcesFactory.h"
#include "DX11Initializer/DX11Initializer.h"

#include "DX11VertexShader.h"
#include "DX11PixelShader.h"
#include "DX11ComputeShader.h"
#include "DX11Buffer.h"
#include "DX11Texture.h"
#include "DX11RenderTarget.h"
#include "DX11InputLayoutDescriptor.h"
#include "DX11InputLayout.h"
#include "DX11SwapChain.h"
#include "DX11PipelineState.h"

#include "swCommonLib/Common/MemoryLeaks.h"


namespace sw
{


typedef DX11Texture				TextureObject;
typedef DX11VertexShader		VertexShaderObject;
typedef DX11PixelShader			PixelShaderObject;
typedef DX11Buffer				BufferObject;
typedef DX11ComputeShader		ComputeShaderObject;
typedef DX11DepthStencilState	DepthStencilStateObject;
typedef DX11RasterizerState		RasterizerStateObject;
typedef DX11BlendingState		BlendingStateObject;



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
	return DX11InputLayout::CreateLayout( name, layoutDesc );
}

// ================================ //
//
sw::Nullable< Texture* >			ResourcesFactory::CreateTextureFromMemory		( const AssetPath& fileName, const BufferRaw& texData, sw::TextureInfo&& texInfo )
{
	return TextureObject::CreateFromMemory( fileName, texData, std::move( texInfo ) );
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

// ================================ //
//
sw::Nullable< Buffer* >			    ResourcesFactory::CreateBufferFromMemory		( const AssetPath& name, const uint8* data, const BufferInfo& bufferInfo )
{
	return BufferObject::CreateFromMemory( name, data, bufferInfo );
}

/**@brief Creates RenderTarget from screen buffer.

@return Returns RenderTarget.*/
RenderTarget*					    ResourcesFactory::CreateScreenRenderTarget()
{
	return DX11RenderTarget::CreateScreenRenderTarget();
}

// ================================ //
//
SwapChain*						    ResourcesFactory::CreateScreenSwapChain			( RenderTarget* screenRT )
{
	return DX11SwapChain::CreateScreenSwapChain( screenRT );
}

// ================================ //
//
IGraphicAPIInitializer*			    ResourcesFactory::CreateAPIInitializer			()
{
	return new DX11Initializer();
}

// ================================ //
//
sw::Nullable< RenderTarget* >	    ResourcesFactory::CreateRenderTarget			( const AssetPath& name, const RenderTargetDescriptor& renderTargetDescriptor )
{
	return DX11RenderTarget::CreateRenderTarget( name, renderTargetDescriptor );
}

}	// sw
