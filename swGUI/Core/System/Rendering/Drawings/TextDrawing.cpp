/**
@file TextDrawing.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "TextDrawing.h"

#include "swGUI/Core/Media/Geometry/Layouts/VertexShape2D.h"


namespace sw {
namespace gui
{

// ================================ //

TextDrawing::TextDrawing( BrushPtr brush, BrushPtr pen, GeometryPtr text ) : GeometryDrawing( brush, pen, text ) {}

// ================================ //

void            TextDrawing::Render( IRenderer* renderer )
{
    // TODO: Check if it is correct for text
    GeometryDrawing::Render( renderer );
}

// ================================ //

void            TextDrawing::RebuildResources( ResourceManagerAPI rm, ShaderProvider* sp )
{
    auto brush = GetBrush().get();
    auto pen = GetPen().get();
    auto geometry = GetGeometry().get();

    // Geometry updates
    CreateAndSetLayoutForVertexType< VertexText2D >( rm, sp, geometry );
    UpdateVertexShader( sp, geometry, sp->GetOpacityVSTemplate() );
    UpdateGeometry( rm, geometry );
    UpdateGeometryConstants( rm, geometry );

    // Brush updates
    UpdateBrushShader( sp, brush, sp->GetOpacityPSTemplate() );
    UpdateBrushTexture( rm, brush );
    UpdateBrushConstants( rm, brush );
    UpdateBrushOpacityMask( rm, nullptr );

    // Pen updates
    UpdatePenShader( sp, pen, sp->GetOpacityPSTemplate() );
    UpdatePenTexture( rm, pen );
    UpdatePenConstants( rm, pen );
    UpdatePenOpacityMask( rm, GetTextGeometry()->GetFont()->GetFontAtlas() );
}

}  // namespace gui
}	// sw
