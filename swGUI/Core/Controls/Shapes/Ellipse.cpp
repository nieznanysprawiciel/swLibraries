/**
@file Ellipse.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "Ellipse.h"
#include "swGUI/Core/Media/Geometry/EllipseGeometry.h"


namespace sw {
namespace gui
{


// ================================ //
//
Ellipse::Ellipse()
	:	m_strokeThickness( 1 )
{
    Shape::SetWidth( 100 );
    Shape::SetHeight( 100 );

	auto rectGeom = std::make_shared< EllipseGeometry >();
	rectGeom->SetWidth( GetSize().x );
	rectGeom->SetHeight( GetSize().y );
	rectGeom->SetThickness( m_strokeThickness );

	SetGeometry( rectGeom );
}

// ================================ //
//
void			Ellipse::SetWidth		( float width )
{
    Shape::SetWidth( width );
	
	auto geom = std::static_pointer_cast< EllipseGeometry >( GetGeometry() );
	geom->SetWidth( GetSize().x );
}

// ================================ //
//
void			Ellipse::SetHeight	( float height )
{
    Shape::SetHeight( height );
	
	auto geom = std::static_pointer_cast< EllipseGeometry >( GetGeometry() );
	geom->SetHeight( GetSize().y );
}

// ================================ //
//
void			Ellipse::SetThickness	( float thickness )
{
	m_strokeThickness = thickness;
	
	auto geom = std::static_pointer_cast< EllipseGeometry >( GetGeometry() );
	geom->SetThickness( m_strokeThickness );
}



}	// gui
}	// sw


