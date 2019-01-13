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
	:	m_width( 100 )
	,	m_height( 100 )
	,	m_strokeThickness( 1 )
{
	auto rectGeom = std::make_shared< RectangleGeometry >();
	rectGeom->SetWidth( m_width );
	rectGeom->SetHeight( m_height );
	rectGeom->SetThickness( m_strokeThickness );

	SetGeometry( rectGeom );
}

// ================================ //
//
void			Rectangle::SetWidth		( float width )
{
	m_width = width;
	
	auto geom = std::static_pointer_cast< RectangleGeometry >( GetGeometry() );
	geom->SetWidth( m_width );
}

// ================================ //
//
void			Rectangle::SetHeight	( float height )
{
	m_height = height;
	
	auto geom = std::static_pointer_cast< RectangleGeometry >( GetGeometry() );
	geom->SetHeight( m_height );
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

