/**
@file RenderingSystem.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "RenderingSystem.h"
#include "RenderingHelpers.h"

#include "swCommonLib/Common/Buffers/StackBuffer.h"

#include "swGUI/Core/System/HostWindow.h"



namespace sw {
namespace gui
{


// ================================ //
//
RenderingSystem::RenderingSystem			( ResourceManager* resourceManager, PathsManager* pathsManager, IRendererOPtr&& renderer )
	:	m_resourceManager( resourceManager )
	,	m_renderer( std::move( renderer ) )
	,	m_shaderProvider( ResourceManagerAPI( resourceManager ), pathsManager )
{}

// ================================ //
//
void				RenderingSystem::RenderTree			( HostWindow* host )
{
	SetRenderTarget( m_renderer.get(), host );

	RenderingParams params;
	params.ParentOffset.x = 0;
	params.ParentOffset.y = 0;

	RenderTree( m_renderer.get(), host, params );
}

// ================================ //
//
ReturnResult        RenderingSystem::InitializeRenderingSystem	()
{
	return InitializeGraphicState( m_resourceManager );
}

// ================================ //
//
ReturnResult        RenderingSystem::InitializeGraphicState		( ResourceManagerAPI rm )
{
    ErrorsCollector collector;

	RasterizerStateInfo rasterizerDesc;
	rasterizerDesc.CullMode = CullMode::None;
	rasterizerDesc.IsClockwise = true;

    m_rasterizerState = collector.OnError( rm.CreateRasterizerState( "::sw::gui::DefaultRasterizerState", rasterizerDesc ), RasterizerStatePtr() );

	DepthStencilInfo depthDesc;
	depthDesc.EnableDepthTest = false;		// Painter algorithm. We never check depth value and always write new pixel.
	depthDesc.EnableStencilTest = false;

    m_depthState = collector.OnError( rm.CreateDepthStencilState( "::sw::gui::DefaultDepthState", depthDesc ), DepthStencilStatePtr() );

	BlendingInfo blendDesc;
	blendDesc.EnableBlending = true;
	blendDesc.ColorOperation = BlendOperation::Add;
	blendDesc.AlphaOperation = BlendOperation::Add;
	blendDesc.SrcColorBlend = BlendFactor::SrcAlpha;
	blendDesc.DstColorBlend = BlendFactor::InverseSrcAlpha;
	blendDesc.DstAlphaBlend = BlendFactor::One;
	blendDesc.SrcAlphaBlend = BlendFactor::One;

    m_transparentBlendState = collector.OnError( rm.CreateBlendingState( "::sw::gui::TransparentBlendState", blendDesc ), BlendingStatePtr() );

	blendDesc.EnableBlending = false;

	m_opaqueBlendState = collector.OnError( rm.CreateBlendingState( "::sw::gui::OpaqueBlendState", blendDesc ), BlendingStatePtr() );

	m_renderingSystemBuffer = collector.OnError( rm.CreateConstantsBuffer( "::sw::gui::RenderingSystemConstants", StackBufferA< RenderingSystemParams >() ), BufferPtr() );
	m_visualBuffer = collector.OnError( rm.CreateConstantsBuffer( "::sw::gui::VisualConstants", StackBufferA< RenderingParams >() ), BufferPtr() );

    return collector.Get();
}


// ================================ //
//
void				RenderingSystem::SetRenderTarget			( IRenderer* renderer, HostWindow* host )
{
	RenderingHelper helper( renderer );

	StackBufferA< RenderingSystemParams > paramsBuffer;
	paramsBuffer.ViewportSize = Size2D( host->GetNativeWindow()->GetClientWidth(), host->GetNativeWindow()->GetClientHeight() );

	helper.UpdateBuffer( m_renderingSystemBuffer.Ptr(), paramsBuffer );
	helper.BindBuffer( m_renderingSystemBuffer.Ptr(), 0, (uint8)ShaderType::VertexShader );
    helper.BindBuffer( m_renderingSystemBuffer.Ptr(), 0, (uint8)ShaderType::PixelShader );

	helper.ClearRenderTargetAndDepth( host->GetRenderTarget().Ptr(), DirectX::XMFLOAT4( 0.0f, 0.0f, 0.0f, 0.0f ), 1.0f );
	helper.SetRenderTarget( host->GetRenderTarget().Ptr(), m_rasterizerState.Ptr(), m_transparentBlendState.Ptr(), m_depthState.Ptr() );
}

// ================================ //
//
void				RenderingSystem::SetSystemConstants			( IRenderer* renderer, const RenderingParams& params )
{
	RenderingHelper helper( renderer );

	StackBufferA< RenderingParams > paramsBuffer;
	paramsBuffer.ParentOffset = params.ParentOffset;

	helper.UpdateBuffer( m_visualBuffer.Ptr(), paramsBuffer );
	helper.BindBuffer( m_visualBuffer.Ptr(), 1, (uint8)ShaderType::VertexShader );
}

// ================================ //
//
void				RenderingSystem::DrawVisual					( IRenderer* renderer, Visual* visual, const RenderingParams& params )
{
	IDrawing* drawing = visual->QueryDrawing();
	if( drawing )
	{
		SetSystemConstants( renderer, params );

		/// @todo RebuildResources can be done in different pass. But first we must think of better system
		/// to notify that something needs changes.
		drawing->RebuildResources( m_resourceManager, &m_shaderProvider );
		drawing->Render( renderer );
	}
}

// ================================ //
//
void				RenderingSystem::RenderTree					( IRenderer* renderer, Visual* visual, const RenderingParams& parentParams )
{
	RenderingParams params;
	params.ParentOffset.x = parentParams.ParentOffset.x + visual->GetVisualOffset().x;
	params.ParentOffset.y = parentParams.ParentOffset.y + visual->GetVisualOffset().y;

	DrawVisual( renderer, visual, params );

	auto numChildren = visual->GetNumChildren();
	for( Size i = 0; i < numChildren; i++ )
	{
		auto child = visual->GetVisualChild( i );
		RenderTree( renderer, child, params );
	}
}


}	// gui
}	// sw
