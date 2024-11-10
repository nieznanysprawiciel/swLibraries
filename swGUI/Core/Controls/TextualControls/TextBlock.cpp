/**
@file Shape.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "TextBlock.h"

#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"
#include "swGUI/Core/System/Rendering/Shading/ShaderProvider.h"
#include "swGUI/Core/System/Rendering/Drawings/TextDrawing.h"



RTTR_REGISTRATION
{
    rttr::registration::class_< sw::gui::TextBlock >( "sw::gui::TextBlock" )
        .property( "Background", &sw::gui::TextBlock::GetBackground, &sw::gui::TextBlock::SetBackground )
        .property( "Foreground", &sw::gui::TextBlock::GetForeground, &sw::gui::TextBlock::SetForeground );
}

namespace sw {
namespace gui
{

// ================================ //

TextBlock::TextBlock()
    : m_invalidateFont( true )
    , m_fontSize( 12 )
    , m_fontStyle( FontStyle::Normal )
    , m_fontWeight( FontWeight::Normal )
    , m_textAlignment( TextAlignment::Left )
    , m_fontFamily( "Arial" )
{}

// ================================ //
//

IDrawing*       TextBlock::QueryDrawing() const
{
    return m_drawing.get();
}

// ================================ //

ReturnResult    TextBlock::UpdateDrawingResources( ResourceManagerAPI& api )
{
    if( FontNeedsUpdate() )
    {
        // TODO: take FontWeight and FontStyle into account
        FontLoaderData init( 16 );
        auto font = api.Load< FontAsset >( "$(Application-Dir)/arial.ttf", &init );
        ReturnIfInvalid( font );

        auto geometry = std::make_shared< TextGeometry >( font.Get() );
        geometry->SetText( m_text );

        SetGeometry( geometry );
        FontUpdated();
    }

    return Success::True;
}

// ================================ //
//

void            TextBlock::SetBackground( BrushPtr brush )
{
    m_background = brush;

    // Create new Drawing only if it previously existed. Drawing doesn't exist if Geometry is not set.
    if( m_drawing && m_background != m_drawing->GetBrush() )
    {
        m_drawing = std::make_shared< TextDrawing >( m_background, m_drawing->GetPen(), m_drawing->GetGeometry() );
    }
}

// ================================ //
//

void            TextBlock::SetForeground( BrushPtr pen )
{
    m_pen = pen;

    // Create new Drawing only if i previously existed. Drawing doesn't exist if Geometry is not set.
    if( m_drawing && m_pen != m_drawing->GetPen() )
    {
        m_drawing = std::make_shared< TextDrawing >( m_drawing->GetBrush(), m_pen, m_drawing->GetGeometry() );
    }
}

// ================================ //
//

void            TextBlock::SetText( const std::wstring& text )
{
    m_text = text;
    if( m_drawing )
        m_drawing->GetTextGeometry()->SetText( text );
}

// ================================ //

void            TextBlock::SetGeometry( GeometryPtr geom )
{
    // Create new drawing if m_drawing is nullptr or geometry changed.
    if( !m_drawing || geom != m_drawing->GetGeometry() )
    {
        m_drawing = std::make_shared< TextDrawing >( m_background, m_pen, geom );
    }
}

// ================================ //
//
bool            TextBlock::HitTest( const Point& point )
{
    if( m_drawing )
        return m_drawing->GetGeometry()->HitTest( point );
    return false;
}

}  // namespace gui
}   // namespace sw
