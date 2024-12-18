/**
@file MockRenderTarget.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "MockRenderTarget.h"
#include "MockTexture.h"


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::MockRenderTarget >( "sw::MockRenderTarget" );
}


namespace sw
{


/**@brief */
MockRenderTarget::~MockRenderTarget()
{}



// ================================ //
//
MockRenderTarget::MockRenderTarget( const AssetPath& name, 
									Texture* colorBuffer,
									Texture* depthBuffer,
									Texture* stencilBuffer )
	: RenderTarget( name, colorBuffer, depthBuffer, stencilBuffer )
	, m_height( 0 )
	, m_width( 0 )
{}

// ================================ //
//
MockRenderTarget*		MockRenderTarget::CreateScreenRenderTarget()
{
	MockRenderTarget* newRenderTarget = new MockRenderTarget( AssetPath( "", SCREEN_RENDER_TARGET ), nullptr, nullptr, nullptr );

	//auto viewPort = DX11APIObjects::get_viewport_desc();
	//newRenderTarget->SetHeight( static_cast<uint16>( viewPort.Height ) );
	//newRenderTarget->SetWidth( static_cast<uint16>( viewPort.Width ) );

	return newRenderTarget;
}

// ================================ //
//
sw::Nullable< MockRenderTarget* >		MockRenderTarget::CreateRenderTarget( const AssetPath& name, const RenderTargetDescriptor& renderTargetDescriptor )
{
	if( !ValidateDescriptor( renderTargetDescriptor ) )
		return "[MockRenderTarget] Can't create render target. Invalid descriptor.";

	TextureInfo colorBufferInfo = renderTargetDescriptor.CreateTextureInfo();
	TextureInfo depthBufferInfo = renderTargetDescriptor.CreateTextureInfo();
	TextureInfo stencilBufferInfo = renderTargetDescriptor.CreateTextureInfo();


	colorBufferInfo.FilePath = name.GetInternalPath() / fs::Path( RENDER_TARGET_COLOR_BUFFER_NAME );
	colorBufferInfo.Format = renderTargetDescriptor.ColorBuffFormat;
	depthBufferInfo.FilePath = name.GetInternalPath() / fs::Path( RENDER_TARGET_DEPTH_BUFFER_NAME );
	//depthBufferInfo.Format = renderTargetDescriptor.DepthStencilFormat;
	stencilBufferInfo.FilePath = name.GetInternalPath() / fs::Path( RENDER_TARGET_STENCIL_BUFFER_NAME );
	//stencilBufferInfo.Format = renderTargetDescriptor.DepthStencilFormat;

	Texture* colorBufferTex = new MockTexture( AssetPath( name.GetFile(), colorBufferInfo.FilePath ), std::move( colorBufferInfo ) );
	Texture* depthBufferTex = new MockTexture( AssetPath( name.GetFile(), depthBufferInfo.FilePath ), std::move( depthBufferInfo ) );
	Texture* stencilBufferTex = nullptr;
	if( renderTargetDescriptor.DepthStencilFormat == DepthStencilFormat::DEPTH_STENCIL_FORMAT_D24_UNORM_S8_UINT ||
		renderTargetDescriptor.DepthStencilFormat == DepthStencilFormat::DEPTH_STENCIL_FORMAT_D32_FLOAT_S8X24_UINT )
		stencilBufferTex = new MockTexture( AssetPath( name.GetFile(), stencilBufferInfo.FilePath ), std::move( stencilBufferInfo ) );

	MockRenderTarget* newRenderTarget = new MockRenderTarget( name, colorBufferTex, depthBufferTex, stencilBufferTex );
	newRenderTarget->SetHeight( renderTargetDescriptor.Height );
	newRenderTarget->SetWidth( renderTargetDescriptor.Width );

	return newRenderTarget;
}

// ================================ //
//
bool MockRenderTarget::ValidateDescriptor( const RenderTargetDescriptor& renderTargetDescriptor )
{
	TextureType RTType = renderTargetDescriptor.TextureType;
	if( RTType == TextureType::Texture1D ||
		RTType == TextureType::TextureArray1D ||
		RTType == TextureType::Texture3D ||
		RTType == TextureType::Buffer )
		return false;

	return true;
}
}	// sw
