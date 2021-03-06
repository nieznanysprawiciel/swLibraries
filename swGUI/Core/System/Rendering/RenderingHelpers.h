#pragma once
/**
@file RenderingHelpers.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Rendering/RenderCommands.h"

#include "swCommonLib/Common/Buffers/StackBuffer.h"

#include <DirectXMath.h>

class IRenderer;
struct RenderContext;



namespace sw {
namespace gui
{



/**@brief Rendering helper functions to fill rendering commands.
@todo This should be temporary. We need new renderer API and new set of commands. Then
we can think about new implementation of helpers but they should be placed in swGraphicAPI.*/
struct RenderingHelper
{
private:

	IRenderer*			m_renderer;

public:

	/**@brief Instanciate this class to call helper functions without passing renderer.*/
	explicit	RenderingHelper	( IRenderer* renderer )
		: m_renderer( renderer )
	{}

	/**@brief Default clear command.
	This command doesn't clear stencil buffer.*/
	void					ClearRenderTargetAndDepth	( RenderTarget* target, const DirectX::XMFLOAT4& color, float depth );

	/**@brief Set render target.
	Ignores buffers and sets them to nullptr.*/
	void					SetRenderTarget				( RenderTarget* target, RasterizerState* rasterizerState, BlendingState* blendingState, DepthStencilState* depthStencilState );

	/**@brief Updates buffer with data.*/
	template< typename BufferDataType >
	inline void				UpdateBuffer				( Buffer* buffer, BufferDataType& data );

	/**@brief Updates buffer using StackBuffer.*/
	template< typename BufferDataType >
	inline void				UpdateBuffer				( Buffer* buffer, StackBufferA< BufferDataType >& data );

	/**@brief Binds buffer.*/
	void					BindBuffer					( Buffer* buffer, uint8 slot, uint8 shaderFlag );

	/**@brief Draw without using buffer.*/
	void					DrawBufferLess				( uint32 numVerticies, PrimitiveTopology topology );

public:
	// ================================ //
	// Static part

	/**@brief Default clear command.
	This command doesn't clear stencil buffer.*/
	static void					ClearRenderTargetAndDepth	( IRenderer* renderer, RenderTarget* target, const DirectX::XMFLOAT4& color, float depth );

	/**@brief Set render target.
	Ignores buffers and sets them to nullptr.*/
	static void					SetRenderTarget				( IRenderer* renderer, RenderTarget* target, RasterizerState* rasterizerState, BlendingState* blendingState, DepthStencilState* depthStencilState );

	/**@brief Updates buffer with data.*/
	template< typename BufferDataType >
	static inline void			UpdateBuffer				( IRenderer* renderer, Buffer* buffer, BufferDataType& data );

	/**@brief Updates buffer using StackBuffer.*/
	template< typename BufferDataType >
	static inline void			UpdateBuffer				( IRenderer* renderer, Buffer* buffer, StackBufferA< BufferDataType >& data );

	/**@brief Binds buffer.*/
	static void					BindBuffer					( IRenderer* renderer, Buffer* buffer, uint8 slot, uint8 shaderFlag );

	/**@brief Draw without using buffer.*/
	static void					DrawBufferLess				( IRenderer* renderer, uint32 numVerticies, PrimitiveTopology topology );

	/**@brief Set texture in command.
	@param[in] bindShader Flags @ref ShaderType can be combined with operator|.*/
	static void					SetTexture					( SetShaderStateCommand& command, Texture* texture, uint8 bindingPoint, uint8 bindShader );

	/**@brief Set all textures to nullptr.*/
	static void					ClearTextureState			( SetShaderStateCommand& command );
};




// ================================ //
//
template< typename BufferDataType >
inline void			RenderingHelper::UpdateBuffer			( Buffer* buffer, BufferDataType& data )
{
	UpdateBuffer( m_renderer, buffer, data );
}

// ================================ //
//
template< typename BufferDataType >
inline void			RenderingHelper::UpdateBuffer			( Buffer* buffer, StackBufferA< BufferDataType >& data )
{
	UpdateBuffer< BufferDataType >( m_renderer, buffer, data );
}

// ================================ //
//
template< typename BufferDataType >
inline void			RenderingHelper::UpdateBuffer			( IRenderer* renderer, Buffer* buffer, BufferDataType& data )
{
	UpdateBufferCommand updateCommand;
	updateCommand.Buffer = buffer;
	updateCommand.FillData = (uint8*)&data;
	updateCommand.Size = sizeof( BufferDataType );

	renderer->UpdateBuffer( updateCommand );
}

// ================================ //
//
template< typename BufferDataType >
inline void			RenderingHelper::UpdateBuffer			( IRenderer* renderer, Buffer* buffer, StackBufferA< BufferDataType >& data )
{
	UpdateBufferCommand updateCommand;
	updateCommand.Buffer = buffer;
	updateCommand.FillData = data.GetData();
	updateCommand.Size = (uint32)data.GetSize();

	renderer->UpdateBuffer( updateCommand );
}


}	// gui
}	// sw


