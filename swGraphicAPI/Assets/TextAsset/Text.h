#pragma once
/**
@file Text.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"
#include "swGeometrics/GeometricsCore/Math/Types.h"

namespace sw
{

/**@brief Decides how text should be aligned.
@ingroup Text*/
enum class TextAlignmentType
{
    Left,
    Center,
    Right,
    Justification,
};


/**@brief Arranges text.
@ingroup Text*/
class TextArrange
{
public:
    float                   Interspace;
    float                   NewLineSize;
    float                   SpaceSize;
    TextAlignmentType       TextAlign;
    bool                    UseKerning;
    /**Wrap text according to Bounds. If set to false, single text line won't have any limit and only
    NewLine characters will break line.
    Depending on TextAlignment, Bounds will be used to determine left, right or center of the text.*/
    bool                    WrapText;
    /**Text crossing lower Bound won't be generated.*/
    bool                    CutOutOfBounds;
    Rect2d                  Bounds;

    float                   AspectRatio;

public:
    explicit TextArrange()
        : Interspace( 0.0f )
        , NewLineSize( 0.0f )
        , SpaceSize( 0.0f )
        , TextAlign( TextAlignmentType::Left )
        , UseKerning( true )
        , WrapText( false )
        , CutOutOfBounds( false )
        , AspectRatio( 1.0f )
        , Bounds( { 0.0f, 0.0f, 0.0f, 0.0f } )
    {}

public:
    std::vector< Position2d >   ArrangeText( const std::wstring& text, const FontLayout& layout ) const;
    std::vector< Position2d >   ArrangeLine( std::wstring_view text, const FontLayout& layout, Position2d startPosition ) const;
    void                        ApplyAlignement( const FontLayout& layout, std::vector< Position2d >& letters, std::wstring_view text ) const;
    
    static bool                 IsWhitespace( wchar_t character );
    static bool                 IsNewline( wchar_t character );
    static bool                 IsSpace( wchar_t character );
};



/**@brief Class for displaying Text on screen.

Layouts and formats text according to rules and parameters provided.
Generates vertex buffer for displaying text on screen.

This class can be used to display simple texts that use only one font without special formatting.
For more complicated cases where some parts of the text have different formatting, new class should be created.

@ingroup Text*/
class Text
{
private:
protected:
    FontAssetPtr        m_font;
    VertexShaderPtr		m_vertexShader;
    PixelShaderPtr		m_pixelShader;

    TextArrange         m_arrange;

    std::wstring        m_text;     // Text to display.

public:
	explicit Text() = default;
	~Text() = default;

};

}	// sw
