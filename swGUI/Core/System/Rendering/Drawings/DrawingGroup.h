#pragma once
/**
@file CompositeDrawing.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "IDrawing.h"


namespace sw {
namespace gui
{


/**@brief Composites group of Drawings.

DrawingGroup can draw multiple Drawing objects.
In future we could support other advanced functionalities from WPF like
transformations, effects rendered to separate textures, clipping and so on.

@ingroup Drawing*/
class DrawingGroup : public IDrawing
{
	RTTR_ENABLE( IDrawing );
	RTTR_REGISTRATION_FRIEND
private:
public:


};


}	// gui
}	// sw
