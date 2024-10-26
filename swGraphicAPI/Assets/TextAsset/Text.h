#pragma once
/**
@file Text.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"
#include "swGeometrics/GeometricsCore/Types/Math/Types.h"

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
    // Allign text to specific character. For example floating point numbers
    // `1.0023` and `25611.5` could be aligned to `.` like this:
    //     1.0023
    // 25611.5
    Character,
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
    wchar_t                 AlignCharacter;
    bool                    UseKerning;
    /**Wrap text according to Bounds. If set to false, text won't have any limit.
    Depending on TextAlignment, Bounds will be used to determine left, right or center of the text.*/
    bool                    WrapText;
    Rect2d                  Bounds;

    float                   AspectRatio;

public:

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

    std::string         m_text;     // Text to display.

public:
	explicit Text() = default;
	~Text() = default;

};

}	// sw
