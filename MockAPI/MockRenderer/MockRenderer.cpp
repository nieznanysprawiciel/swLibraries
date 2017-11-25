/**
@file MockRenderer.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "MockRenderer.h"

#include "MockResources/MockInputLayout.h"
#include "MockResources/MockBuffer.h"
#include "MockResources/MockVertexShader.h"
#include "MockResources/MockPixelShader.h"
#include "MockResources/MockTexture.h"
#include "MockResources/MockRenderTarget.h"





#define ThrowIfNull( ptr, message )				\
if( !ptr )										\
{												\
	assert( false );							\
	return;										\
}
//throw new std::runtime_error( message );


namespace sw
{



/**@brief*/
MockRenderer::MockRenderer( RendererUsage usage )
{
	m_usageType = usage;
}

// ================================ //
//
MockRenderer::~MockRenderer()
{}



//====================================================================================//
//			Drawing commands
//====================================================================================//

// ================================ //
//
void	MockRenderer::Draw				( const DrawCommand& command )
{}

// ================================ //
//
void	MockRenderer::DrawInstanced		( const DrawInstancedCommand& command )
{}

//====================================================================================//
//			Render target commands	
//====================================================================================//

// ================================ //
//
void	MockRenderer::SetRenderTarget	( const SetRenderTargetCommand& command )
{}

// ================================ //
//
void	MockRenderer::SetRenderTarget	( const SetRenderTargetExCommand& command )
{}

// ================================ //
//
void	MockRenderer::ClearRenderTarget	( const ClearRenderTargetCommand& command )
{}

// ================================ //
//
void	MockRenderer::UpdateBuffer		( const UpdateBufferCommand& command )
{}

// ================================ //
//
void	MockRenderer::BindBuffer		( const BindBufferCommand& command )
{}

// ================================ //
//
void	MockRenderer::UpdateAndBindBuffer	( const UpdateBindBuffer& command )
{}

// ================================ //
//
void	MockRenderer::SetDefaultBuffers	( const SetDefaultBuffersCommand& command )
{}

// ================================ //
//
void	MockRenderer::SetShaderState	( const SetShaderStateCommand& command )
{}

// ================================ //
//
void	MockRenderer::SetShaderState	( const SetShaderStateExCommand& command )
{}

// ================================ //
//
void	MockRenderer::SetShaderState	( const SetRenderStateCommand& command )
{}

// ================================ //
//
void	MockRenderer::SetShaderState	( const SetRenderStateExCommand& command )
{}

// ================================ //
//
void	MockRenderer::CopyTexture		( const CopyTextureCommand& command )
{}


//====================================================================================//
//			Internal Helpers	
//====================================================================================//


// ================================ //
//
bool    MockRenderer::SetVertexBuffer   ( BufferObject* buffer, unsigned int offset )
{
	if( buffer )
	{
		return false;
	}
	else
	{
		//throw new std::runtime_error( "Vertex buffer is nullptr" );
		assert( !"Vertex buffer is nullptr" );
	}
	return true;
}


// ================================ //
// Buffer can be nullptr.
void	MockRenderer::SetIndexBuffer	( BufferObject* buffer, unsigned int offset, bool extendedIndex )
{}

// ================================ //
//
void	MockRenderer::SetRenderTarget	( RenderTargetObject* const targets[ MAX_BOUND_RENDER_TARGETS ], RenderTargetObject* depthStencil )
{}

// ================================ //
//
void	MockRenderer::SetTextures		( TextureObject* const texturesArray[ MAX_BOUND_RENDER_TARGETS ], const uint8 shaderTypes[ MAX_BOUND_RENDER_TARGETS ] )
{}

}	// sw
