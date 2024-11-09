#pragma once
/**
@file TextDrawing.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "GeometryDrawing.h"

#include "swGUI/Core/Media/Brushes/Brush.h"
#include "swGUI/Core/Media/Geometry/TextGeometry.h"


namespace sw {
namespace gui
{

/**@brief Draws text and it's background.

@ingroup Drawing*/
class TextDrawing : public GeometryDrawing
{
    RTTR_ENABLE( GeometryDrawing );
	RTTR_REGISTRATION_FRIEND
private:

public:

	explicit				TextDrawing				( BrushPtr brush, BrushPtr pen, GeometryPtr text );


	virtual void			Render					( IRenderer* renderer ) override;
	virtual void			RebuildResources		( ResourceManagerAPI rm, ShaderProvider* sp );

public:

	const TextGeometryPtr&	GetTextGeometry() const { return std::static_pointer_cast< TextGeometry >( GetGeometry() ); }
    
};

DEFINE_PTR_TYPE( TextDrawing )


}	// gui
}	// sw


