/**
@file TextDrawing.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "TextDrawing.h"

#include "swGUI/Core/Media/Geometry/Layouts/VertexShape2D.h"
#include "swCommonLib/Common/Logging/Logger.h"


namespace sw {
namespace gui
{

// ================================ //

TextDrawing::TextDrawing( BrushPtr brush, BrushPtr pen, GeometryPtr text ) : GeometryDrawing( brush, pen, text ) {}


// ================================ //

void            TextDrawing::RebuildResources( ResourceManagerAPI rm, ShaderProvider* sp )
{
    ErrorsCollector results;

    auto brush = GetBrush().get();
    auto pen = GetPen().get();
    auto geometry = GetGeometry().get();

    // Geometry updates
    results.Add( CreateAndSetLayoutForVertexType< VertexText2D >( rm, sp, geometry ) );
    results.Add( UpdateVertexShader( sp, geometry, sp->GetOpacityVSTemplate() ) );
    results.Add( UpdateGeometry( rm, geometry ) );
    results.Add( UpdateGeometryConstants( rm, geometry ) );

    // Brush updates
    results.Add( UpdateBrushShader( sp, brush, sp->GetBasicPSTemplate() ) );
    results.Add( UpdateBrushTexture( rm, brush ) );
    results.Add( UpdateBrushConstants( rm, brush ) );
    results.Add( UpdateBrushOpacityMask( rm, nullptr ) );

    // Pen updates
    results.Add( UpdatePenShader( sp, pen, sp->GetOpacityPSTemplate() ) );
    results.Add( UpdatePenTexture( rm, pen ) );
    results.Add( UpdatePenConstants( rm, pen ) );
    results.Add( UpdatePenOpacityMask( rm, GetTextGeometry()->GetFont()->GetFontAtlas() ) );

    if( !results.IsValid() )
        LOG_ERROR( fmt::format( "Error during rebuilding resources for TextDrawing: {}", results.GetException() ) );
}

}  // namespace gui
}	// sw
