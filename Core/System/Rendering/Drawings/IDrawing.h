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


/**@brief Base class for rendering entities.
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

	virtual void			RebuildResources	( ResourceManagerAPI resourceManager, ShaderProvider* sp ) = 0;
	virtual void			Render				( IRenderer* renderer ) = 0;

};

DEFINE_PTR_TYPE( IDrawing )


}	// gui
}	// sw
