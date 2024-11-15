#pragma once
/**
@file TextGeometry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGUI/Core/Media/Geometry/Geometry.h"
#include "swGraphicAPI/Assets/TextAsset/Text.h"


namespace sw {
namespace gui
{

/**@brief Generates Text.
@ingroup Geometries*/
class TextGeometry : public Geometry
{
private:
protected:

    FontAssetPtr        m_font;
    std::wstring        m_text;  // Text to display.

    float               m_width;
    float               m_height;

    TextAlignment       m_textAlignment;

    Size                m_counter;  //< Counter for unique buffer name.

public:

    explicit TextGeometry( FontAssetPtr font );
    virtual ~TextGeometry() = default;

public:

    void                    SetText( const std::wstring& text );
    const std::wstring&     GetText() const  { return m_text; }

    void                    SetFont( FontAssetPtr font );
    FontAssetPtr            GetFont() const { return m_font; }

    void                    SetWidth( float width );
    void                    SetHeight( float height );

    void                    SetAlignment( TextAlignment alignment );

public:

    // Inherited via Geometry
    virtual bool             HitTest( const Point& point ) const override;
    virtual bool             HitTest( const Rect& rectangle ) const override;

    virtual Nullable< GeometryData > Generate() override;
    virtual BufferRange              BufferData() override;
    virtual fs::Path                 ShaderFunctionFile() override;
    virtual std::string              GeometryName() override;
    virtual AssetPath                ConstantsName() override;

private:
    static Size             NextCounter();
};

DEFINE_PTR_TYPE( TextGeometry )

}  // namespace gui
}  // namespace sw
