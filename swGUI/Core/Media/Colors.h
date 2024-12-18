#pragma once
/**
@file Colors.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swGUI/Core/System/CommonTypes/CommonTypes.h"


namespace sw {
namespace gui
{


/**@brief Predefined colors according to:
https://learn.microsoft.com/en-us/dotnet/api/system.windows.media.colors?view=windowsdesktop-8.0*/
enum class Colors : u32
{
    AliceBlue = 0xFFF0F8FF,
    AntiqueWhite = 0xFFFAEBD7,
    Aqua = 0xFF00FFFF,
    Aquamarine = 0xFF7FFFD4,
    Azure = 0xFFF0FFFF,
    Beige = 0xFFF5F5DC,
    Bisque = 0xFFFFE4C4,
    Black = 0xFF000000,
    BlanchedAlmond = 0xFFFFEBCD,
    Blue = 0xFF0000FF,
    BlueViolet = 0xFF8A2BE2,
    Brown = 0xFFA52A2A,
    BurlyWood = 0xFFDEB887,
    CadetBlue = 0xFF5F9EA0,
    Chartreuse = 0xFF7FFF00,
    Chocolate = 0xFFD2691E,
    Coral = 0xFFFF7F50,
    CornflowerBlue = 0xFF6495ED,
    Cornsilk = 0xFFFFF8DC,
    Crimson = 0xFFDC143C,
    Cyan = 0xFF00FFFF,
    DarkBlue = 0xFF00008B,
    DarkCyan = 0xFF008B8B,
    DarkGoldenrod = 0xFFB8860B,
    DarkGray = 0xFFA9A9A9,
    DarkGreen = 0xFF006400,
    DarkKhaki = 0xFFBDB76B,
    DarkMagenta = 0xFF8B008B,
    DarkOliveGreen = 0xFF556B2F,
    DarkOrange = 0xFFFF8C00,
    DarkOrchid = 0xFF9932CC,
    DarkRed = 0xFF8B0000,
    DarkSalmon = 0xFFE9967A,
    DarkSeaGreen = 0xFF8FBC8F,
    DarkSlateBlue = 0xFF483D8B,
    DarkSlateGray = 0xFF2F4F4F,
    DarkTurquoise = 0xFF00CED1,
    DarkViolet = 0xFF9400D3,
    DeepPink = 0xFFFF1493,
    DeepSkyBlue = 0xFF00BFFF,
    DimGray = 0xFF696969,
    DodgerBlue = 0xFF1E90FF,
    Firebrick = 0xFFB22222,
    FloralWhite = 0xFFFFFAF0,
    ForestGreen = 0xFF228B22,
    Fuchsia = 0xFFFF00FF,
    Gainsboro = 0xFFDCDCDC,
    GhostWhite = 0xFFF8F8FF,
    Gold = 0xFFFFD700,
    Goldenrod = 0xFFDAA520,
    Gray = 0xFF808080,
    Green = 0xFF008000,
    GreenYellow = 0xFFADFF2F,
    Honeydew = 0xFFF0FFF0,
    HotPink = 0xFFFF69B4,
    IndianRed = 0xFFCD5C5C,
    Indigo = 0xFF4B0082,
    Ivory = 0xFFFFFFF0,
    Khaki = 0xFFF0E68C,
    Lavender = 0xFFE6E6FA,
    LavenderBlush = 0xFFFFF0F5,
    LawnGreen = 0xFF7CFC00,
    LemonChiffon = 0xFFFFFACD,
    LightBlue = 0xFFADD8E6,
    LightCoral = 0xFFF08080,
    LightCyan = 0xFFE0FFFF,
    LightGoldenrodYellow = 0xFFFAFAD2,
    LightGray = 0xFFD3D3D3,
    LightGreen = 0xFF90EE90,
    LightPink = 0xFFFFB6C1,
    LightSalmon = 0xFFFFA07A,
    LightSeaGreen = 0xFF20B2AA,
    LightSkyBlue = 0xFF87CEFA,
    LightSlateGray = 0xFF778899,
    LightSteelBlue = 0xFFB0C4DE,
    LightYellow = 0xFFFFFFE0,
    Lime = 0xFF00FF00,
    LimeGreen = 0xFF32CD32,
    Linen = 0xFFFAF0E6,
    Magenta = 0xFFFF00FF,
    Maroon = 0xFF800000,
    MediumAquamarine = 0xFF66CDAA,
    MediumBlue = 0xFF0000CD,
    MediumOrchid = 0xFFBA55D3,
    MediumPurple = 0xFF9370DB,
    MediumSeaGreen = 0xFF3CB371,
    MediumSlateBlue = 0xFF7B68EE,
    MediumSpringGreen = 0xFF00FA9A,
    MediumTurquoise = 0xFF48D1CC,
    MediumVioletRed = 0xFFC71585,
    MidnightBlue = 0xFF191970,
    MintCream = 0xFFF5FFFA,
    MistyRose = 0xFFFFE4E1,
    Moccasin = 0xFFFFE4B5,
    NavajoWhite = 0xFFFFDEAD,
    Navy = 0xFF000080,
    OldLace = 0xFFFDF5E6,
    Olive = 0xFF808000,
    OliveDrab = 0xFF6B8E23,
    Orange = 0xFFFFA500,
    OrangeRed = 0xFFFF4500,
    Orchid = 0xFFDA70D6,
    PaleGoldenrod = 0xFFEEE8AA,
    PaleGreen = 0xFF98FB98,
    PaleTurquoise = 0xFFAFEEEE,
    PaleVioletRed = 0xFFDB7093,
    PapayaWhip = 0xFFFFEFD5,
    PeachPuff = 0xFFFFDAB9,
    Peru = 0xFFCD853F,
    Pink = 0xFFFFC0CB,
    Plum = 0xFFDDA0DD,
    PowderBlue = 0xFFB0E0E6,
    Purple = 0xFF800080,
    Red = 0xFFFF0000,
    RosyBrown = 0xFFBC8F8F,
    RoyalBlue = 0xFF4169E1,
    SaddleBrown = 0xFF8B4513,
    Salmon = 0xFFFA8072,
    SandyBrown = 0xFFF4A460,
    SeaGreen = 0xFF2E8B57,
    SeaShell = 0xFFFFF5EE,
    Sienna = 0xFFA0522D,
    Silver = 0xFFC0C0C0,
    SkyBlue = 0xFF87CEEB,
    SlateBlue = 0xFF6A5ACD,
    SlateGray = 0xFF708090,
    Snow = 0xFFFFFAFA,
    SpringGreen = 0xFF00FF7F,
    SteelBlue = 0xFF4682B4,
    Tan = 0xFFD2B48C,
    Teal = 0xFF008080,
    Thistle = 0xFFD8BFD8,
    Tomato = 0xFFFF6347,
    Transparent = 0x00FFFFFF,
    Turquoise = 0xFF40E0D0,
    Violet = 0xFFEE82EE,
    Wheat = 0xFFF5DEB3,
    White = 0xFFFFFFFF,
    WhiteSmoke = 0xFFF5F5F5,
    Yellow = 0xFFFFFF00,
    YellowGreen = 0xFF9ACD32
};




/**@brief Color representation using 32-bit integer.

@todo Currently name `Color` is already used as float4 color.
Maybe the names should be replaced.*/
class ColorExt
{
protected:
    static const u32 RedMask = 0x00FF0000;
    static const u32 GreenMask = 0x0000FF00;
    static const u32 BlueMask = 0x000000FF;
    static const u32 AlphaMask = 0xFF000000;

    static const u8 RedMaskShift = 16;
    static const u8 GreenMaskShift = 8;
    static const u8 BlueMaskShift = 0;
    static const u8 AlphaMaskShift = 24;

private:
    u32 m_color;

public:
    ColorExt( u32 color ) : m_color( color ) {}
    ColorExt( Colors color ) : m_color( (u32)color ) {}

    Color   Into() const;

public:

    u8      Red() const { return u8( ( m_color & ColorExt::RedMask ) >> ColorExt::RedMaskShift ); }
    u8      Green() const { return u8( ( m_color & ColorExt::GreenMask ) >> ColorExt::GreenMaskShift ); }
    u8      Blue() const { return u8( ( m_color & ColorExt::BlueMask ) >> ColorExt::BlueMaskShift ); }
    u8      Alpha() const { return u8( ( m_color & ColorExt::AlphaMask ) >> ColorExt::AlphaMaskShift ); }

    float   scRed() const { return (float)Red() / 256.f; }
    float   scGreen() const { return (float)Green() / 256.f; }
    float   scBlue() const { return (float)Blue() / 256.f; }
    float   scAlpha() const { return (float)Alpha() / 256.f; }

};

// ================================ //

inline Color    ColorExt::Into() const
{
    return Color( scRed(), scGreen(), scBlue(), scAlpha() );
}


}  // namespace gui
}  // namespace sw
