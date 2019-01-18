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
	:	m_width( 100 )
	,	m_height( 100 )
	,	m_strokeThickness( 1 )
{
	auto rectGeom = std::make_shared< EllipseGeometry >();
	rectGeom->SetWidth( m_width );
	rectGeom->SetHeight( m_height );
	rectGeom->SetThickness( m_strokeThickness );

	SetGeometry( rectGeom );
}

// ================================ //
//
void			Ellipse::SetWidth		( float width )
{
	m_width = width;
	
	auto geom = std::static_pointer_cast< EllipseGeometry >( GetGeometry() );
	geom->SetWidth( m_width );
}

// ================================ //
//
void			Ellipse::SetHeight	( float height )
{
	m_height = height;
	
	auto geom = std::static_pointer_cast< EllipseGeometry >( GetGeometry() );
	geom->SetHeight( m_height );
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


