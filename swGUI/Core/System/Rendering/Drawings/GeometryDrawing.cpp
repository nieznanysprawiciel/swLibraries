/**
@file GeometryFrawing.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "GeometryDrawing.h"




namespace sw {
namespace gui
{

// ================================ //
//
GeometryDrawing::GeometryDrawing							( BrushPtr brush, BrushPtr pen, GeometryPtr geom )
	:	m_brush( brush )
	,	m_pen( pen )
	,	m_geometry( geom )
{}

// ================================ //
//
void				GeometryDrawing::Render					( IRenderer* renderer )
{
	UpdateGeometryCBContent( renderer, m_geometry.get() );
	
	UpdateBrushCBContent( renderer, m_brush.get() );
	RenderFill( renderer );

	UpdatePenCBContent( renderer, m_pen.get() );
	RenderBorder( renderer );
}

// ================================ //
//
void				GeometryDrawing::RebuildResources		( ResourceManager* rm, ShaderProvider* sp )
{
	DefaultRebuildResources( rm, sp, m_brush.get(), m_pen.get(), m_geometry.get() );
}


}	// gui
}	// sw

