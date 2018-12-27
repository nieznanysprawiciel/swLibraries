/**
@file Shape.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "Shape.h"




RTTR_REGISTRATION
{
	rttr::registration::class_< sw::gui::DependencyObject >( "sw::gui::Shape" )
		.property( "Fill", &sw::gui::Shape::m_fill )
		.property( "Stroke", &sw::gui::Shape::m_stroke );
}



namespace sw {
namespace gui
{


// ================================ //
//
IDrawing*				Shape::QueryDrawing			() const
{
	return m_drawing.get();
}


}	// gui
}	// sw

