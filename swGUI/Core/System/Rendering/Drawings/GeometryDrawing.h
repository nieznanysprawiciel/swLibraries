#pragma once
/**
@file GeometryDrawing.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Drawing.h"

#include "swGUI/Core/Media/Brushes/Brush.h"
#include "swGUI/Core/Media/Geometry/Geometry.h"



namespace sw {
namespace gui
{

/**@brief Draws interior Geometry and it's border with Brush and Pen.

@ingroup Drawing*/
class GeometryDrawing : public Drawing
{
	RTTR_ENABLE( Drawing );
	RTTR_REGISTRATION_FRIEND
private:

	BrushPtr		m_brush;		///< Brush used to fill geometry's interior.
	BrushPtr		m_pen;			///< Brush used to draw border.
	GeometryPtr		m_geometry;		///< Geometry to draw.

public:

	explicit				GeometryDrawing			( BrushPtr brush, BrushPtr pen, GeometryPtr geom );


	virtual void			Render					( IRenderer* renderer ) override;
	virtual void			RebuildResources		( ResourceManager* rm, ShaderProvider* sp );

};

DEFINE_PTR_TYPE( GeometryDrawing )


}	// gui
}	// sw

