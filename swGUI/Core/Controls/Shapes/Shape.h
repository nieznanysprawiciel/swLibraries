#pragma once
/**
@file Shape.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/Controls/UIElement.h"

#include "swGUI/Core/Media/Brushes/Brush.h"
#include "swGUI/Core/System/Rendering/Drawings/GeometryDrawing.h"


/**@defgroup Shapes Geometric Shapes

@brief Controls for rendering simple geometric 2D shapes.

@ingroup Controls*/


namespace sw {
namespace gui
{


/**@brief Base class for geometric shape controls.
@ingroup Shapes
@ingroup Controls*/
class Shape : public UIElement
{
	RTTR_ENABLE( UIElement );
	RTTR_REGISTRATION_FRIEND;
private:

	GeometryDrawingPtr		m_drawing;

protected:

	BrushPtr		m_fill;
	BrushPtr		m_stroke;		///< Border brush.

public:

	explicit		Shape		() = default;
	virtual			~Shape		() = default;


	virtual IDrawing*				QueryDrawing		() const;

};




}	// gui
}	// sw

