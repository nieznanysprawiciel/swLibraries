#pragma once
/**
@file RenderingSystem.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"
#include "swGraphicAPI/Rendering/IRenderer.h"
#include "swGraphicAPI/ResourceManager/ResourceManager.h"

#include "swGUI/Core/System/Rendering/Shading/ShaderProvider.h"
#include "swGUI/Core/System/Config/PathsManager.h"

#include "swGUI/Core/Controls/Visual.h"
#include "swGUI/Core/System/Rendering/Drawings/IDrawing.h"



/**@defgroup RenderingSystem Rendering System
@ingroup GUICore*/


DEFINE_OPTR_TYPE( IRenderer );

namespace sw {
namespace gui
{


/**@brief GUI rendering system.

@ingroup RenderingSystem*/
class RenderingSystem
{
private:

	IRendererOPtr		m_renderer;
	ResourceManager*	m_resourceManager;
	ShaderProvider		m_shaderProvider;

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

	void			Render				( const Visual* visual );
	void			Render				( IDrawing* drawing );


	///@}

};

DEFINE_OPTR_TYPE( RenderingSystem );


}	// gui
}	// sw

