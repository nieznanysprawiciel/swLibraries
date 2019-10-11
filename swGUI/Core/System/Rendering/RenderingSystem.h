#pragma once
/**
@file RenderingSystem.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"
#include "swGraphicAPI/Rendering/IRenderer.h"

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"

#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"
#include "swGraphicAPI/Resources/PipelineStates/BlendingState.h"

#include "swGUI/Core/System/Rendering/Shading/ShaderProvider.h"
#include "swGraphicAPI/ResourceManager/PathTranslators/PathsManager.h"

#include "swGUI/Core/Controls/Visual.h"
#include "swGUI/Core/System/Rendering/Drawings/IDrawing.h"
#include "RenderingParams.h"



/**@defgroup RenderingSystem Rendering System
@ingroup GUICore*/



namespace sw {

DEFINE_OPTR_TYPE( IRenderer );


namespace gui
{

class HostWindow;


/**@brief GUI rendering system.

@ingroup RenderingSystem*/
class RenderingSystem
{
	FRIEND_CLASS_TESTER( RenderingSystem );
private:

	IRendererOPtr		m_renderer;
	ResourceManagerAPI	m_resourceManager;
	ShaderProvider		m_shaderProvider;

private:

	// Rendering state objects
	RasterizerStatePtr          m_rasterizerState;
	DepthStencilStatePtr        m_depthState;

	BlendingStatePtr            m_transparentBlendState;
	BlendingStatePtr            m_opaqueBlendState;

	BufferPtr                   m_renderingSystemBuffer;
	BufferPtr                   m_visualBuffer;

protected:
public:
	explicit		RenderingSystem		( ResourceManager* resourceManager, PathsManager* pathsManager, IRendererOPtr&& renderer );
					~RenderingSystem	() = default;

	/**@brief Returns renderer.
	You probably don't need it. Use only if you write graphic application which renders something by itself.
	You are not owner of this object.*/
	IRenderer*			GetRenderer			() const			{ return m_renderer.get(); }

	/**@brief Returns internal ShaderProvider object.*/
	ShaderProvider*		GetShaderProvider	()					{ return &m_shaderProvider; }

public:

	///@name Rendering
	///@{
	void			RenderTree			( HostWindow* host );

	void			Render				( const Visual* visual );
	void			Render				( IDrawing* drawing );


	///@}

    ReturnResult    InitializeRenderingSystem	();

private:

    ReturnResult    InitializeGraphicState		( ResourceManagerAPI rm );


	void			SetRenderTarget				( IRenderer* renderer, HostWindow* visual );
	void			SetSystemConstants			( IRenderer* renderer, const RenderingParams& params );

	void			DrawVisual					( IRenderer* renderer, Visual* visual, const RenderingParams& params );
	void			RenderTree					( IRenderer* renderer, Visual* visual, const RenderingParams& parentParams );
};

DEFINE_OPTR_TYPE( RenderingSystem );


}	// gui
}	// sw

