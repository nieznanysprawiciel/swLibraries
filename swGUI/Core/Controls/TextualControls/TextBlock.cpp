/**
@file Shape.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "TextBlock.h"

#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"
#include "swGraphicAPI/Assets/TextAsset/Loader/FontPicker.h"

#include "swGUI/Core/System/Rendering/Shading/ShaderProvider.h"
#include "swGUI/Core/System/Rendering/Drawings/TextDrawing.h"



RTTR_REGISTRATION
{
    rttr::registration::class_< sw::gui::TextBlock >( "sw::gui::TextBlock" )
        .property( "Background", &sw::gui::TextBlock::GetBackground, &sw::gui::TextBlock::SetBackground )
        .property( "Foreground", &sw::gui::TextBlock::GetForeground, &sw::gui::TextBlock::SetForeground )
        .property( "FontFamily", &sw::gui::TextBlock::GetFontFamily, &sw::gui::TextBlock::SetFontFamily )
        .property( "FontStyle", &sw::gui::TextBlock::GetFontStyle, &sw::gui::TextBlock::SetFontStyle )
        .property( "FontWeight", &sw::gui::TextBlock::GetFontWeight, &sw::gui::TextBlock::SetFontWeight )
        .property( "FontSize", &sw::gui::TextBlock::GetFontSize, &sw::gui::TextBlock::SetFontSize )
        .property( "TextAlignment", &sw::gui::TextBlock::GetTextAlignment, &sw::gui::TextBlock::SetTextAlignment )
        .property( "Text", &sw::gui::TextBlock::GetText, &sw::gui::TextBlock::SetText );
}

namespace sw {
namespace gui
{

static DependencyProperty sBackground = DependencyProperty::Register( "Background", TypeID::get< TextBlock >() );
static DependencyProperty sForeground = DependencyProperty::Register( "Foreground", TypeID::get< TextBlock >() );
static DependencyProperty sFontFamily = DependencyProperty::Register( "FontFamily", TypeID::get< TextBlock >() );
static DependencyProperty sFontStyle = DependencyProperty::Register( "FontStyle", TypeID::get< TextBlock >() );
static DependencyProperty sFontWeight = DependencyProperty::Register( "FontWeight", TypeID::get< TextBlock >() );
static DependencyProperty sFontSize = DependencyProperty::Register( "FontSize", TypeID::get< TextBlock >() );
static DependencyProperty sTextAlignment = DependencyProperty::Register( "TextAlignment", TypeID::get< TextBlock >() );
static DependencyProperty sText = DependencyProperty::Register( "Text", TypeID::get< TextBlock >() );

// ================================ //

TextBlock::TextBlock()
    : m_invalidateFont( true )
    , m_fontSize( 16 )
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
        FontPicker picker;
        picker.RegisterSearchPath( "$(Application-Dir)" );
        picker.RegisterSearchPath( "$(SystemFonts)" );

        auto chosen = picker.ChooseFontFile( api.GetPathsManager(), m_fontFamily, m_fontWeight, m_fontStyle, false );
        ReturnIfInvalid( chosen );  // Maybe other default font could be used instead of returning error.

        FontLoaderData init( m_fontSize );
        //auto font = api.Load< FontAsset >( "$(Application-Dir)/arial.ttf", &init );
        auto font = api.Load< FontAsset >( chosen.Get().Path.GetOriginalPath(), &init );
        ReturnIfInvalid( font );

        auto geometry = std::make_shared< TextGeometry >( font.Get() );
        geometry->SetText( m_text );
        geometry->SetWidth( GetSize().x );
        geometry->SetHeight( GetSize().y );
        geometry->SetAlignment( m_textAlignment );

        SetGeometry( geometry );
        FontUpdated();
    }

    return Success::True;
}

// ================================ //
//

void            TextBlock::SetBackground( BrushPtr brush )
{
    if( DependencyObject::SetValue( sBackground, brush, &TextBlock::m_background ) )
    {
        // Create new Drawing only if it previously existed. Drawing doesn't exist if Geometry is not set.
        if( m_drawing && m_background != m_drawing->GetBrush() )
        {
            m_drawing = std::make_shared< TextDrawing >( m_background, m_drawing->GetPen(), m_drawing->GetGeometry() );
        }
    }
}

// ================================ //
//

void            TextBlock::SetForeground( BrushPtr pen )
{
    if( DependencyObject::SetValue( sForeground, pen, &TextBlock::m_pen ) )
    {
        // Create new Drawing only if i previously existed. Drawing doesn't exist if Geometry is not set.
        if( m_drawing && m_pen != m_drawing->GetPen() )
        {
            m_drawing = std::make_shared< TextDrawing >( m_drawing->GetBrush(), m_pen, m_drawing->GetGeometry() );
        }
    }
}

// ================================ //

void            TextBlock::SetFontFamily( const std::string& fontFamily )
{
    if( DependencyObject::SetValue( sFontFamily, fontFamily, &TextBlock::m_fontFamily ) )
        InvalidateFont();
}

// ================================ //

void            TextBlock::SetFontSize( FontSizeType size )
{
    if( DependencyObject::SetValue( sFontSize, size, &TextBlock::m_fontSize ) )
        InvalidateFont();
}

// ================================ //

void            TextBlock::SetFontStyle( FontStyle fontStyle )
{
    if( DependencyObject::SetValue( sFontStyle, fontStyle, &TextBlock::m_fontStyle ) )
        InvalidateFont();
}

// ================================ //
//

void            TextBlock::SetFontWeight( FontWeight fontWeight )
{
    if( DependencyObject::SetValue( sFontWeight, fontWeight, &TextBlock::m_fontWeight ) )
        InvalidateFont();
}

// ================================ //

void            TextBlock::SetText( const std::wstring& text )
{
    if( DependencyObject::SetValue( sText, text, &TextBlock::m_text ) )
        if( m_drawing )
            m_drawing->GetTextGeometry()->SetText( text );
}

// ================================ //

void            TextBlock::SetTextAlignment( TextAlignment alignment )
{
    if( DependencyObject::SetValue( sTextAlignment, alignment, &TextBlock::m_textAlignment ) )
        if( m_drawing )
            m_drawing->GetTextGeometry()->SetAlignment( alignment );

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
