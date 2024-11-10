#pragma once
/**
@file TextBlock.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGUI/Core/Controls/FrameworkElement.h"

#include "swGUI/Core/Media/Brushes/Brush.h"
#include "swGUI/Core/System/Rendering/Drawings/TextDrawing.h"
#include "swGraphicAPI/Assets/TextAsset/Text.h"


namespace sw {
namespace gui
{

/**@brief Font style.
@ingroup Text*/
enum class FontStyle : u8
{
    Normal,
    Italic,
    // Oblique
};

/**@brief Font thickness.
@ingroup Text*/
enum class FontWeight : u8
{
    Light,
    Normal,
    UltraBold,
};

/**@brief Simple Text presenter.
@ingroup Text
@ingroup Controls*/
class TextBlock : public FrameworkElement
{
    RTTR_ENABLE( FrameworkElement );
    RTTR_REGISTRATION_FRIEND;

private:

	TextDrawingPtr      m_drawing;

    BrushPtr            m_background;   ///< Brush for background.
    BrushPtr            m_pen;          ///< Brush for drawing text.

protected:

    std::string         m_fontFamily;
    FontStyle           m_fontStyle;
    FontWeight          m_fontWeight;
    bool                m_invalidateFont;

    TextAlignment       m_textAlignment;
    FontSizeType        m_fontSize;
    std::wstring        m_text;

public:

    explicit TextBlock();
    virtual ~TextBlock() = default;

public:

    void                SetBackground( BrushPtr brush );
    void                SetForeground( BrushPtr pen );

    BrushPtr            GetBackground() const { return m_background; }
    BrushPtr            GetForeground() const { return m_pen; }

    void                SetFontFamily( const std::string& fontFamily );
    std::string         GetFontFamily() const { return m_fontFamily; }
    
    void                SetFontSize( uint32 size );
    uint32              GetFontSize() const;

    FontStyle           GetFontStyle() const { return m_fontStyle; }
    void                SetFontStyle( FontStyle fontStyle );

    FontWeight          GetFontWeight() const { return m_fontWeight; }
    void                SetFontWeight( FontWeight fontWeight );

    void                SetText( const std::wstring& text );
    std::wstring        GetText() const { return m_text; }


    GeometryPtr         GetGeometry() const { return m_drawing->GetGeometry(); }

protected:

    void                SetGeometry( GeometryPtr geom );
    
    void                InvalidateFont() { m_invalidateFont = true; }
    void                FontUpdated() { m_invalidateFont = false; }
    bool                FontNeedsUpdate() const { return m_invalidateFont; }

public:

    // Inherited via UIElement
    virtual bool            HitTest( const Point& point ) override;
    
    virtual IDrawing*       QueryDrawing() const;
    virtual ReturnResult    UpdateDrawingResources( sw::ResourceManagerAPI& resourceManager ) override;
};

DEFINE_OPTR_TYPE( TextBlock );

}  // namespace gui
}  // namespace sw
