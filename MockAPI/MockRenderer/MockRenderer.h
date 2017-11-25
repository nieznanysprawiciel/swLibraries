#pragma once
/**
@file MockRenderer.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/




#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/BlendingState.h"
#include "swGraphicAPI/Resources/RasterizerState.h"
#include "swGraphicAPI/Resources/DepthStencilState.h"
#include "swGraphicAPI/Rendering/IRenderer.h"

class MockRenderer;
typedef MockRenderer Renderer;




// @todo There're constants in ConstantsBuffersFormats.h file. This is duplicate, but there's no way to do this :(.
#define CAMERA_BUFFER_BINDING_POINT 0
#define LIGHTS_BUFFER_BINDING_POINT 1
#define TRANSFORM_BUFFER_BINDING_POINT 1
#define BONES_BUFFER_BINDING_POINT 2
#define MATERIAL_BUFFER_BINDING_POINT 2



namespace sw
{


/**@brief Mock renderer for debugging and testing.
@ingroup MockAPI*/
class MockRenderer : public IRenderer
{
private:

	bool						m_valid;					///< Je¿eli klasa nie zosta³a zainicjowana poprawnie, to bêdzie tu wartoœæ false.
	RendererUsage				m_usageType;				///< Informacja jak bêdzie u¿ywany rederer.
public:
	MockRenderer( RendererUsage usage = USE_AS_IMMEDIATE );
	~MockRenderer();

	bool SupportsDefferedContextRendering() override { return true; }		///< Informuje czy Renderer nadaje siê do renderowania w wielu w¹tkach do opóŸnionego contextu.
	bool IsValid() override { return m_valid; }




	virtual void		Draw					( const DrawCommand& command )						override;
	virtual void		DrawInstanced			( const DrawInstancedCommand& command )				override;

	virtual void		SetRenderTarget			( const SetRenderTargetCommand& command )			override;
	virtual void		SetRenderTarget			( const SetRenderTargetExCommand& command )			override;
	virtual void		ClearRenderTarget		( const ClearRenderTargetCommand& command )			override;

	virtual void		UpdateBuffer			( const UpdateBufferCommand& command )				override;
	virtual void		BindBuffer				( const BindBufferCommand& command )				override;
	virtual void		UpdateAndBindBuffer		( const UpdateBindBuffer& command )					override;

	virtual void		SetDefaultBuffers		( const SetDefaultBuffersCommand& command )			override;

	virtual void		SetShaderState			( const SetShaderStateCommand& command )			override;
	virtual void		SetShaderState			( const SetShaderStateExCommand& command )			override;
	virtual void		SetShaderState			( const SetRenderStateCommand& command )			override;
	virtual void		SetShaderState			( const SetRenderStateExCommand& command )			override;

	virtual void		CopyTexture				( const CopyTextureCommand& command )				override;

private:

	bool                SetVertexBuffer         ( BufferObject* buffer, unsigned int offset );
	void				SetIndexBuffer			( BufferObject* buffer, unsigned int offset, bool extendedIndex );
	void				SetRenderTarget			( RenderTargetObject* const targets[ MAX_BOUND_RENDER_TARGETS ], RenderTargetObject* depthStencil );
	void				SetTextures				( TextureObject* const texturesArray[ MAX_BOUND_RENDER_TARGETS ], const uint8 shaderTypes[ MAX_BOUND_RENDER_TARGETS ] );
};

}	// sw


