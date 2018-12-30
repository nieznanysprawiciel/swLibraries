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
		.property( "Fill", &sw::gui::Shape::GetFill, &sw::gui::Shape::SetFill )
		.property( "Stroke", &sw::gui::Shape::GetStroke, &sw::gui::Shape::SetStroke );
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

// ================================ //
//
void					Shape::SetFill				( BrushPtr brush )
{
	m_fill = brush;

	// Create new Drawing only if i previously existed. Drawing doesn't exist if Geometry is not set.
	if( m_drawing && m_fill != m_drawing->GetBrush() )
	{
		m_drawing = std::make_shared< GeometryDrawing >( m_fill, m_drawing->GetPen(), m_drawing->GetGeometry() );
	}
}

// ================================ //
//
void					Shape::SetStroke				( BrushPtr pen )
{
	m_stroke = pen;

	// Create new Drawing only if i previously existed. Drawing doesn't exist if Geometry is not set.
	if( m_drawing && m_stroke != m_drawing->GetPen() )
	{
		m_drawing = std::make_shared< GeometryDrawing >( m_drawing->GetBrush(), m_stroke, m_drawing->GetGeometry() );
	}
}

// ================================ //
//
void					Shape::SetGeometry			( GeometryPtr geom )
{
	// Create new drawing if m_drawing is nullptr or geometry changed.
	if( !m_drawing || geom != m_drawing->GetGeometry() )
	{
		m_drawing = std::make_shared< GeometryDrawing >( m_fill, m_stroke, geom );
	}
}

// ================================ //
//
bool					Shape::HitTest				( const Point& point )
{
	if( m_drawing )
		return m_drawing->GetGeometry()->HitTest( point );
	return false;
}

// ================================ //
//
Size					Shape::GetNumChildren		() const
{
	// Shapes should be leaf elements in the tree.
	return 0;
}

// ================================ //
//
Visual*					Shape::GetVisualChild		( Size idx ) const
{
	// No children.
	return nullptr;
}

// ================================ //
//
Size2D					Shape::Measure				( Size2D availableSize )
{
	assert( !"Implement me" );
	return Size2D();
}

// ================================ //
//
void					Shape::Arrange				( Rect& finalRect )
{
	assert( !"Implement me" );
}

// ================================ //
//
bool					Shape::AddChild				( UIElementOPtr&& child )
{
	// Shouldn't allow to add children.
	return false;
}



}	// gui
}	// sw

