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

public:

	void			SetFill				( BrushPtr brush );
	void			SetStroke			( BrushPtr pen );

	BrushPtr		GetFill				() const { return m_fill; }
	BrushPtr		GetStroke			() const { return m_stroke; }
	
	GeometryPtr		GetGeometry			() const { return m_drawing->GetGeometry(); }

protected:

	void			SetGeometry			( GeometryPtr geom );

public:

	// Inherited via UIElement
	virtual bool		HitTest					( const Point& point )		override;
	virtual Size		GetNumChildren			()							const override;
	virtual Visual*		GetVisualChild			( Size idx )				const override;
	virtual Size2D		Measure					( Size2D availableSize )	override;
	virtual void		Arrange					( Rect& finalRect )			override;
	virtual bool		AddChild				( UIElementOPtr&& child )	override;
};

DEFINE_OPTR_TYPE( Shape )


}	// gui
}	// sw

