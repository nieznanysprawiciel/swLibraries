#pragma once

#include "swCommonLib/Common/TypesDefinitions.h"

namespace sw
{

/**@brief Describes single glyph.
http://freetype.org/freetype2/docs/tutorial/step2.html#section-2
@ingroup Text*/
struct Glyph
{
    uint16          CharCode;
    uint16          GlyphIdx;   // Index of glyph in freetype font

    uint32          Width;
    uint32          Height;

    int32           AdvanceX;   // The horizontal distance to increment the pen position when the glyph is drawn as part of a string of text.
    int32           AdvanceY;   // The vertical distance used to increment the pen position when the glyph is drawn as part of a string of text.
    int32           BearingX;   // The horizontal distance from the current cursor position to the leftmost border of the glyph image's bounding box.
    int32           BearingY;   // The vertical distance from the current cursor position (on the baseline) to the topmost border of the glyph image's bounding box.
    
    uint32          TextureX;   // x pixel coord of the bitmap's bottom-left corner
    uint32          TextureY;   // y pixel coord of the bitmap's bottom-left corner

    Size            Padding;

public:
    explicit Glyph()
        : CharCode( 0 )
        , GlyphIdx( 0 )
        , Width( 0 )
        , Height( 0 )
        , AdvanceX( 0 )
        , AdvanceY( 0 )
        , BearingX( 0 )
        , BearingY( 0 )
        , TextureX( 0 )
        , TextureY( 0 )
        , Padding( 0 )
    {}
};

} // sw
