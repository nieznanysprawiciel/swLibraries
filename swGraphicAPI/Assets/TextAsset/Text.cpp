/**
@file Text.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/Assets/TextAsset/stdafx.h"

#include "swGeometrics/GeometricsCore/Generators/Generator.h"
#include "swGeometrics/BasicShapes/CoordsUV/PlanarUV.h"

#include "Text.h"


namespace sw
{



// ================================ //

TextArranger                TextArranger::CreateFrom( const FontAssetPtr font )
{
    TextArranger arranger;
    arranger.SpaceSize = font->GetLayout().SpaceWidth();
    return arranger;
}

// ================================ //

std::vector< Position2d >   TextArranger::ArrangeText( const std::wstring& text, const FontLayout& layout ) const
{
    std::vector< Position2d > letters;
    letters.reserve( text.length() );
    
    // Offset position from top using max hight of the letter relative to baseline (bearingY).
    Position2d translate( this->Bounds.Left, this->Bounds.Top - layout.GetMaxBearingY() );
    Size charIdx = 0;

    while( charIdx < text.length() )
    {
        auto lineString = std::wstring_view( text.c_str() + charIdx );
        auto line = ArrangeLine( lineString, layout, translate );
        
        ApplyAlignement( layout, line, lineString );

        charIdx += line.size();
        letters.insert( letters.end(), line.begin(), line.end() );
        translate = Position2d( this->Bounds.Left, translate.y - this->Interline * layout.NewLineSize() );

        if( this->CutOutOfBounds && translate.y < this->Bounds.Bottom )
            break;
    }

    return letters;
}

// ================================ //

std::vector< Position2d >               TextArranger::ArrangeLine( std::wstring_view text, const FontLayout& layout, Position2d translate ) const
{
    std::vector< Position2d > letters;
    letters.reserve( EstimateLineLength( text ) );

    Size lastSpace = 0;

    for( Size charIdx = 0; charIdx < text.length(); charIdx++ )
    {
        if( IsSpace( text[ charIdx ] ) )
        {
            lastSpace = charIdx;

            translate += Position2d( this->SpaceSize + this->Interspace, 0.f );
            letters.push_back( translate );
            continue;
        }

        if( IsNewline( text[ charIdx ] ) )
        {
            letters.push_back( translate );
            return letters;
        }

        if( auto glyphIter = layout.Glyphs.find( text[ charIdx ] ); glyphIter != layout.Glyphs.end() )
        {
            auto& glyph = glyphIter->second;

            if ( this->UseKerning && charIdx > 0 && !IsWhitespace( text[ charIdx - 1 ] ) )
            {
                auto kerShift = layout.Kerning.at( std::make_pair( text[ charIdx - 1 ], text[ charIdx ] ) );
                translate += Position2d( kerShift, 0.0 );
            }

            letters.push_back( translate );
            translate += Position2d( this->Interspace + glyph.AdvanceX, 0.f );

            // Conditionally wrapping text for known characters. For unknown characters we assume, that the next
            // character will be correct and wrapping will happen than.
            // We need to know glyph vertex right edge, so this logic can't be moved after.
            if( this->WrapText && TopRightVertex( glyph, translate ).x + layout.Padding > this->Bounds.Right )
            {
                // Text crossed right bound. We need to break line.
                // Removing all characters since last space. Next call to ArrangeLine will handle those characters
                // again.
                letters.erase( letters.begin() + ( lastSpace + 1 ), letters.end() );
                break;
            }
        }
        else
        {
            // Unknown character: put space instead.
            letters.push_back( translate );
            translate += Position2d( this->SpaceSize + this->Interspace, 0.f );
        }
    }

    return letters;
}

// ================================ //

void                TextArranger::ApplyAlignement( const FontLayout& layout, std::vector< Position2d >& letters, std::wstring_view text ) const
{
    if( letters.empty() || text.length() < letters.size() )
        return;

    Size lastCharIdx = letters.size() - 1;
    float textWidth = TextWidth( letters, text.data(), layout );
    float remainingSpace = this->Bounds.Right - this->Bounds.Left - textWidth;


    switch( this->TextAlign )
    {
    case TextAlignment::Left:
    {
        // Nothing to do. Text is aligned to left by default.
        break;
    }

    case TextAlignment::Center:
    {
        float offset = remainingSpace / 2.0f;
        for( auto& letter : letters )
            letter.x += offset;
        break;
    }

    case TextAlignment::Right:
    {
        for( auto& letter : letters )
            letter.x += remainingSpace;
        break;
    }

    case TextAlignment::Justify:
    {
        // Find all spaces which will be extended.
        auto numSpaces = std::count_if( text.begin(), text.begin() + lastCharIdx, [](wchar_t c) { return IsWhitespace(c); });
        auto trailingSpaces = CountTrailingWhitespaces( std::wstring_view( text.data(), lastCharIdx ) );
        
        // Distribute remaining space equally between all spaces.
        // (Besides last one: we have one place less between than number of chars)
        float offsetPerSpace = remainingSpace / ( numSpaces - trailingSpaces );
        float curOffset = 0.0f;

        for( Size i = 0; i < letters.size(); i++ )
        {
            if( IsWhitespace( text[ i ] ) )
                curOffset += offsetPerSpace;
            
            letters[ i ].x += curOffset;
        }
        break;
    }
    default:
        break;
    }
}

// ================================ //

float               TextArranger::TextWidth( const std::vector< Position2d >& letters, const std::wstring& text, const FontLayout& layout ) const
{
    Size lastCharIdx = letters.size() - 1;
    Size trailingSpaces = CountTrailingWhitespaces( std::wstring_view( text.c_str(), letters.size() ) );
    i64 lastNonSpace = (i64)lastCharIdx - (i64)trailingSpaces;

    if( lastNonSpace < 0 )
        return 0.0f;  // No characters in text (only spaces or newlines)

    // We need to find right edge of the last non whitespace character in line.
    auto lastRightEdge = TopRightVertex( layout.Glyphs.at( text[ lastNonSpace ] ), letters[ lastNonSpace ] ).x + layout.Padding;
    // We don't take TopLeftVertex, because it's translated by bearingX, which causes natural padding.
    auto firstLeftEdge = letters[ 0 ].x;

    return lastRightEdge - firstLeftEdge;
}

// ================================ //

bool                TextArranger::IsWhitespace        ( wchar_t character )
{
    if( character == L' ' || character == L'\n' || character == L'\r' )
        return true;
    return false;
}

// ================================ //

bool                TextArranger::IsNewline             ( wchar_t character )
{
    if( character == L'\n' || character == L'\r' )
        return true;
    return false;
}

// ================================ //

bool                TextArranger::IsSpace               ( wchar_t character )
{
    if( character == L' ' )
        return true;
    return false;
}

// ================================ //

Size                TextArranger::EstimateLineLength( std::wstring_view text ) { 
    auto endline = text.find_first_of( L"\n\r" );
    return endline != std::string::npos ? endline : text.length();
}

// ================================ //

Rect2d              TextArranger::ComputeTextBounds( const std::vector< Position2d >& letters ) { 
    if( letters.empty() )
        // PlanarUV requires non-zero size.
        return Rect2d{ 0.f, 0.000001f, 0.f, 0.000001f };
    
    auto [ minX, maxX ] =
        std::minmax_element( letters.begin(), letters.end(), []( auto& pos1, auto& pos2 ) { return pos1.x < pos2.x; } );
    auto [ minY, maxY ] =
        std::minmax_element( letters.begin(), letters.end(), []( auto& pos1, auto& pos2 ) { return pos1.y < pos2.y; } );

    auto bb = Rect2d{ minX->x, maxX->x, minY->y, maxY->y };
    
    // PlanarUV requires non-zero size.
    bb.Right = bb.Right - bb.Left == 0.0f ? 0.000001f : bb.Right;
    bb.Bottom = bb.Top - bb.Bottom == 0.0f ? 0.000001f : bb.Bottom;

    return bb;
}

// ================================ //

Size                TextArranger::CountTrailingWhitespaces( const std::wstring_view& text )
{
    for( auto iter = text.rbegin(); iter != text.rend(); iter++ )
    {
        if( !IsWhitespace( *iter ) )
            return std::distance( text.rbegin(), iter );
    }

    return 0;
}

// ================================ //

Position2d          TextArranger::TopLeftVertex( const Glyph& glyph, Position2d position )
{
    Position2d bearing = Position2d( (float)glyph.BearingX, (float)glyph.BearingY );
    return position + bearing;
}

// ================================ //

Position2d          TextArranger::TopRightVertex( const Glyph& glyph, Position2d position )
{
    Position2d bearing = Position2d( (float)glyph.BearingX, (float)glyph.BearingY );
    Position2d quadTopRight = Position2d( (float)glyph.Width, 0.f );
    return quadTopRight + position + bearing;
}

// ================================ //

Position2d          TextArranger::BottomLeftVertex( const Glyph& glyph, Position2d position )
{
    Position2d bearing = Position2d( (float)glyph.BearingX, (float)glyph.BearingY );
    Position2d quadBottomLeft = Position2d( 0.f, -(float)glyph.Height );
    return quadBottomLeft + position + bearing;
}

// ================================ //

Position2d          TextArranger::BottomRightVertex( const Glyph& glyph, Position2d position )
{
    Position2d bearing = Position2d( (float)glyph.BearingX, (float)glyph.BearingY );
    Position2d quadBottomRight = Position2d( (float)glyph.Width, -(float)glyph.Height );
    return quadBottomRight + position + bearing;
}

// ================================ //

Nullable< geom::IndexedGeometryBuffer< geom::VertexShape2D, Index32 > >
TextArranger::GenerateGeometry( const std::wstring& text, const FontAssetPtr font, bool genBackground ) const
{
    auto letters = this->ArrangeText( text, font->GetLayout() );
    auto textBB = ComputeTextBounds( letters );
    
    TextGeometryGenerator< geom::VertexShape2D, Index32, geom::TextAcc< geom::VertexShape2D > > generator( std::move( letters ), font, text );
    generator.GenerateBackground = genBackground;
    generator.Bounds = this->WrapText ? this->Bounds : textBB;

    return geom::Generate< geom::IndexedGeometryBuffer< geom::VertexShape2D, Index32 > >( generator );
}

// ================================ //

Nullable< geom::IndexedGeometryBuffer< geom::VertexText2D, Index32 > >
TextArranger::GenerateGeometryTextured( const std::wstring& text, const FontAssetPtr font, bool genBackground ) const
{
    auto letters = this->ArrangeText( text, font->GetLayout() );
    auto textBB = ComputeTextBounds( letters );

    TextGeometryGenerator< geom::VertexText2D, Index32, geom::TexturedTextAcc< geom::VertexText2D > > generator( std::move( letters ), font, text);
    generator.GenerateBackground = genBackground;
    generator.Bounds = this->WrapText ? this->Bounds : textBB;

    geom::PlanarUV< geom::VertexText2D > planarUV;
    planarUV.MinX = generator.Bounds.Left;
    planarUV.MaxY = generator.Bounds.Top;
    planarUV.MaxX = generator.Bounds.Right;
    planarUV.MinY = generator.Bounds.Bottom;

    return geom::Generate< geom::IndexedGeometryBuffer< geom::VertexText2D, Index32 > >( generator, planarUV );
}

}	// sw
