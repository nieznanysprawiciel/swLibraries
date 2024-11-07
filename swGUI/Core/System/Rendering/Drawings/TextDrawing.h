#pragma once
/**
@file TextDrawing.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Drawing.h"

#include "swGUI/Core/Media/Brushes/Brush.h"
#include "swGUI/Core/Media/Geometry/Geometry.h"


namespace sw {
namespace gui
{

/**@brief Draws text and it's background.

@ingroup Drawing*/
class TextDrawing : public Drawing
{
	RTTR_ENABLE( Drawing );
	RTTR_REGISTRATION_FRIEND
private:

	BrushPtr		m_brush;		///< Brush used to fill background.
	BrushPtr		m_pen;			///< Brush used to draw text.
	GeometryPtr		m_backgroundGeometry;	///< Geometry to draw background.
	GeometryPtr		m_textGeometry;			///< Geometry to draw Text Glyphs.

public:

	explicit				TextDrawing				( BrushPtr brush, BrushPtr pen, GeometryPtr bakcground, GeometryPtr text );


	virtual void			Render					( IRenderer* renderer ) override;
	virtual void			RebuildResources		( ResourceManagerAPI rm, ShaderProvider* sp );

public:

	const BrushPtr&			GetBrush					() const { return m_brush; }
	const BrushPtr&			GetPen						() const { return m_pen; }
	const GeometryPtr&		GetGeometry					() const { return m_textGeometry; }
};

DEFINE_PTR_TYPE( TextDrawing )


}	// gui
}	// sw


