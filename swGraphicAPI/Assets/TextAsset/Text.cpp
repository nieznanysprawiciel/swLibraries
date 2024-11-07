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

std::vector< Position2d >             TextArranger::ArrangeText( const std::wstring& text, const FontLayout& layout ) const
{
    std::vector< Position2d > letters;
    letters.reserve( text.length() );
    
    Position2d translate( this->Bounds.Left, this->Bounds.Top );
    Size charIdx = 0;

    while( charIdx < text.length() )
    {
        auto lineString = std::wstring_view( text.c_str() + charIdx );
        auto line = ArrangeLine( lineString, layout, translate );
        
        ApplyAlignement( layout, line, lineString );

        charIdx += line.size();
        letters.insert( letters.end(), line.begin(), line.end() );
        translate = Position2d( this->Bounds.Left, translate.y - this->NewLineSize );

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
        }
        else
        {
            // Unknown character: put space instead.
            letters.push_back( translate );
            translate += Position2d( this->SpaceSize + this->Interspace, 0.f );
        }

        if( this->WrapText && translate.x > this->Bounds.Right )
        {
            // Text crossed right bound. We need to break line.
            // Removing all characters since last space. Next call to ArrangeLine will handle those characters again.
            letters.erase( letters.begin() + (lastSpace + 1), letters.end() );
            break;
        }
    }

    return letters;
}

// ================================ //

void                TextArranger::ApplyAlignement( const FontLayout& layout, std::vector< Position2d >& letters, std::wstring_view text ) const
{
    if( letters.empty() || text.length() < letters.size() )
        return;

    Size charIdx = letters.size() - 1;
    Position2d last = letters[ charIdx ];
    auto& glyph = layout.Glyphs.at( text[ charIdx ] );

    float textWidth = letters.back().x - letters.front().x + glyph.AdvanceX;
    float remainingSpace = this->Bounds.Right - this->Bounds.Left - textWidth;


    switch( this->TextAlign )
    {
    case TextAlignmentType::Left:
    {
        // Nothing to do. Text is aligned to left by default.
        break;
    }

    case TextAlignmentType::Center:
    {
        float offset = remainingSpace / 2.0f;
        for( auto& letter : letters )
            letter.x += offset;
        break;
    }

    case TextAlignmentType::Right:
    {
        for( auto& letter : letters )
            letter.x += remainingSpace;
        break;
    }

    case TextAlignmentType::Justification:
    {
        // Find all spaces which will be extended.
        auto numSpaces = std::count_if( text.begin(), text.begin() + charIdx, [](wchar_t c) { return IsWhitespace(c);  });
        
        // Distribute remaining space equally between all spaces.
        // (Besides last one: we have one place less between than number of chars)
        float offset = remainingSpace / ( numSpaces - 1 );

        for( Size charIdx = 0; charIdx < text.length(); charIdx++ )
        {
            if( IsWhitespace( text[ charIdx ] ) )
            {
                for( Size i = 0; i < letters.size(); i++ )
                    if( IsWhitespace( text[ i ] ) )
                    letters[ i ].x += offset;
            }
        }
        break;
    }
    default:
        break;
    }
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

Nullable< geom::IndexedGeometry< geom::VertexShape2D, Index32 > >    TextArranger::GenerateGeometry( const std::wstring& text, const FontAssetPtr font, bool genBackground ) const
{
    auto letters = this->ArrangeText( text, font->GetLayout() );
    
    TextGeometryGenerator< geom::VertexShape2D, Index32, geom::TextAcc< geom::VertexShape2D > > generator( std::move( letters ), font, text );
    generator.GenerateBackground = genBackground;
    generator.Bounds = this->Bounds;

    return geom::Generate< geom::IndexedGeometry< geom::VertexShape2D, Index32 > >( generator );
}

// ================================ //

Nullable< geom::IndexedGeometry< geom::VertexText2D, Index32 > >      TextArranger::GenerateGeometryTextured( const std::wstring& text, const FontAssetPtr font, bool genBackground ) const
{
    auto letters = this->ArrangeText( text, font->GetLayout() );

    TextGeometryGenerator< geom::VertexText2D, Index32, geom::TexturedTextAcc< geom::VertexText2D > > generator( std::move( letters ), font, text);
    generator.GenerateBackground = genBackground;
    generator.Bounds = this->Bounds;

    geom::PlanarUV< geom::VertexText2D > planarUV;
    planarUV.MinX = this->Bounds.Left;
    planarUV.MinY = this->Bounds.Bottom;
    planarUV.MaxX = this->Bounds.Right;
    planarUV.MaxY = this->Bounds.Top;

    return geom::Generate< geom::IndexedGeometry< geom::VertexText2D, Index32 > >( generator, planarUV );
}

}	// sw
