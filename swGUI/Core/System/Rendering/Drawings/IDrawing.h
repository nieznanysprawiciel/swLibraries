#pragma once
/**
@file IDrawing.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Object.h"


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
	RTTR_REGISTRATION_FRIEND
private:
public:

	explicit		IDrawing		() = default;
	virtual			~IDrawing		() = 0 {}

};



}	// gui
}	// sw
