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
    // TODO: Rebuild font
    


    bool result = true;

    auto brush = GetBrush().get();
    auto pen = GetPen().get();
    auto geometry = GetGeometry().get();

    // Geometry updates
    result = CreateAndSetLayoutForVertexType< VertexText2D >( rm, sp, geometry ) && result;
    result = UpdateVertexShader( sp, geometry ) && result;
    result = UpdateGeometry( rm, geometry ) && result;
    result = UpdateGeometryConstants( rm, geometry ) && result;

    // Brush updates
    result = UpdateBrushShader( sp, brush ) && result;
    result = UpdateBrushTexture( rm, brush ) && result;
    result = UpdateBrushConstants( rm, brush ) && result;

    // Pen updates
    result = UpdatePenShader( sp, pen ) && result;
    result = UpdatePenTexture( rm, pen ) && result;
    result = UpdatePenConstants( rm, pen ) && result;
}

}  // namespace gui
}	// sw
