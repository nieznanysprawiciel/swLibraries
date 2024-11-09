#pragma once
/**
@file IDrawing.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Object.h"

#include "swGraphicAPI/Rendering/IRenderer.h"
#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"
#include "swGUI/Core/System/Rendering/Shading/ShaderProvider.h"


/**@defgroup Drawing Drawing
@brief Rendering tree representation.
@ingroup RenderingSystem*/



namespace sw {
namespace gui
{


/**@brief Base class for rendering entities. Drawing object gives Visual it's appearance.
@ingroup Drawing*/
class IDrawing : public Object
{
	RTTR_ENABLE( Object );
	RTTR_REGISTRATION_FRIEND;

	friend class RenderingSystem;
private:
public:

	explicit		IDrawing		() = default;
	virtual			~IDrawing		() = 0 {}

private:

	/**@brief Changing parameters of Drawing objects may require reloading some of subresources.
	
	@ref IDrawing::RebuildResources	will be called by @ref RenderingSystem before rendering IDrawing
	on screen. RenderingSystem defers Resources update until it is necessary. That means that changing
	parameters of IDrawing object should only mark some Resources as invalid and reload them only 
	when IDrawing::RebuildResources	is called.
	This way if swGUI user updates model mulitple times in one animation frame, RenderingSystem won't
	suffer performance penalty.*/
	virtual void			RebuildResources	( sw::ResourceManagerAPI resourceManager, ShaderProvider* sp ) = 0;

	/**@brief Allows to implement custom rendering logic for different types of visual objects.
	For example rendering Text has some aspects that are different from standard geometry.
	
	IDrawing::Render function is called by @ref RenderingSystem each time part of screen must be redrawn.*/
	virtual void			Render				( IRenderer* renderer ) = 0;

};

DEFINE_PTR_TYPE( IDrawing )


}	// gui
}	// sw
