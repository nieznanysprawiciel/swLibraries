/**
@file GeometryFrawing.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "GeometryDrawing.h"

#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"
#include "swGUI/Core/System/Rendering/Shading/ShaderProvider.h"


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
void				GeometryDrawing::RebuildResources		( ResourceManagerAPI rm, ShaderProvider* sp )
{
	auto result = DefaultRebuildResources( rm, sp, m_brush.get(), m_pen.get(), m_geometry.get() );
    if( !result.IsValid() )
        LOG_ERROR( fmt::format( "Error during rebuilding resources for geometry drawing.", result.GetError() ) );
}


}	// gui
}	// sw

