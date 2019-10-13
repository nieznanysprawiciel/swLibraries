/**
@file Rectangle.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "Rectangle.h"
#include "swGUI/Core/Media/Geometry/RectangleGeometry.h"


namespace sw {
namespace gui
{


// ================================ //
//
Rectangle::Rectangle()
	:	m_strokeThickness( 1 )
{
    Shape::SetWidth( 100 );
    Shape::SetHeight( 100 );

	auto rectGeom = std::make_shared< RectangleGeometry >();
	rectGeom->SetWidth( GetSize().x );
	rectGeom->SetHeight( GetSize().y );
	rectGeom->SetThickness( m_strokeThickness );

	SetGeometry( rectGeom );
}

// ================================ //
//
void			Rectangle::SetWidth		( float width )
{
    Shape::SetWidth( width );
	
	auto geom = std::static_pointer_cast< RectangleGeometry >( GetGeometry() );
	geom->SetWidth( GetSize().x );


}

// ================================ //
//
void			Rectangle::SetHeight	( float height )
{
    Shape::SetHeight( height );
	
	auto geom = std::static_pointer_cast< RectangleGeometry >( GetGeometry() );
	geom->SetHeight( GetSize().y );
}

// ================================ //
//
void			Rectangle::SetThickness	( float thickness )
{
	m_strokeThickness = thickness;
	
	auto geom = std::static_pointer_cast< RectangleGeometry >( GetGeometry() );
	geom->SetThickness( m_strokeThickness );
}



}	// gui
}	// sw

