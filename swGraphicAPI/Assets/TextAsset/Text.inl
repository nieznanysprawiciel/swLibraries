#pragma once
/**
@file Text.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Text.h"

namespace sw
{

// ================================ //

template< typename VertexType, typename IndexType, typename TextAcc >
inline Size         TextGeometryGenerator< VertexType, IndexType, TextAcc >::GetNumberVerticies() const
{
    // Whitespaces could be remove, but it complicates code and isn't worth at this moment.
    //auto numSpaces = std::count_if( m_text.begin(), m_text.end(), []( wchar_t c ) { return TextArranger::IsWhitespace( c ); } );
    auto numSpaces = 0;
    auto numLettersVerts = 4 * ( m_text.length() - numSpaces );

    if( GenerateBackground )
    {
        auto numBackgroundVerts = 4;
        return numLettersVerts + numBackgroundVerts;
    }
    else
        return numLettersVerts;
}

// ================================ //

template< typename VertexType, typename IndexType, typename TextAcc >
inline Size         TextGeometryGenerator< VertexType, IndexType, TextAcc >::GetNumberIndicies() const
{
    // Each letter is rectangle that has 4 vertices. We need 6 indices to draw 2 triangles.
    return 3 * GetNumberVerticies() / 2;
}

// ================================ //

template < typename VertexType, typename IndexType, typename TextAcc >
inline Size         TextGeometryGenerator< VertexType, IndexType, TextAcc >::GetNumberTextIndicies() const
{
    return GetNumberIndicies() - GetNumberBorderIndicies();
}

// ================================ //

template < typename VertexType, typename IndexType, typename TextAcc >
inline Size         TextGeometryGenerator< VertexType, IndexType, TextAcc >::GetNumberBorderIndicies() const
{
    return GenerateBackground ? 6 : 0;
}

// ================================ //

template< typename VertexType, typename IndexType, typename TextAcc >
inline ReturnResult TextGeometryGenerator< VertexType, IndexType, TextAcc >::ValidateParams() const
{
    return Success::True;
}

// ================================ //

template< typename VertexType, typename IndexType, typename TextAcc >
inline void         TextGeometryGenerator< VertexType, IndexType, TextAcc >::GenerateVertex( VertexType& vertex, Size vertexIdx )
{
    if( GenerateBackground && vertexIdx < 4 )
        GenerateBackgroundVertex( vertex, vertexIdx );
    else
        GenerateTextVertex( vertex, vertexIdx );
}

// ================================ //

template< typename VertexType, typename IndexType, typename TextAcc >
inline void         TextGeometryGenerator< VertexType, IndexType, TextAcc >::GenerateBackgroundVertex( VertexType& vertex, Size vertexIdx )
{
    switch( vertexIdx )
    {
    case 0:
        TextAcc::GetPos( vertex ) = Position2d( Bounds.Left, Bounds.Top );
        TextAcc::GetUV( vertex ) = Position2d( 0.0, 0.0 );
        break;
    case 1:
        TextAcc::GetPos( vertex ) = Position2d( Bounds.Right, Bounds.Top );
        TextAcc::GetUV( vertex ) = Position2d( 1.0, 0.0 );
        break;
    case 2:
        TextAcc::GetPos( vertex ) = Position2d( Bounds.Left, Bounds.Bottom );
        TextAcc::GetUV( vertex ) = Position2d( 0.0, 1.0 );
        break;
    case 3:
        TextAcc::GetPos( vertex ) = Position2d( Bounds.Right, Bounds.Bottom );
        TextAcc::GetUV( vertex ) = Position2d( 1.0, 1.0 );
        break;
    }
}

// ================================ //

template< typename VertexType, typename IndexType, typename TextAcc >
inline void         TextGeometryGenerator< VertexType, IndexType, TextAcc >::GenerateTextVertex( VertexType& vertex, Size vertexIdx )
{
    auto idx = FindLetterIndex( vertexIdx );
    auto wch = m_text.at( idx );
    Position2d translate = m_letters[ idx ];

    if( TextArranger::IsWhitespace( wch ) )
    {
        PutWhitespaceVertex( vertex, idx, translate );
        return;
    }

    auto& glyph = m_layout.Glyphs.at( wch );
    
    PutLetterVertex( vertex, glyph, translate, idx );
    PutLetterUV( vertex, glyph, translate, idx );
}

// ================================ //

template< typename VertexType, typename IndexType, typename TextAcc >
inline Size         TextGeometryGenerator< VertexType, IndexType, TextAcc >::FindLetterIndex( Size vertexIdx ) const
{
    return ( GenerateBackground ? vertexIdx - 4 : vertexIdx ) / 4;
}

// ================================ //

template< typename VertexType, typename IndexType, typename TextAcc >
inline void TextGeometryGenerator< VertexType, IndexType, TextAcc >::PutWhitespaceVertex( VertexType& vertex,
                                                                                          Size        vertexIdx,
                                                                                          Position2d position ) const
{
    TextAcc::GetPos( vertex ) = position;
    TextAcc::GetUV( vertex ) = Position2d( 0.0f, 0.0f);
}

// ================================ //

template < typename VertexType, typename IndexType, typename TextAcc >
inline void
TextGeometryGenerator< VertexType, IndexType, TextAcc >::PutLetterVertex( VertexType& vertex, const Glyph& glyph,
                                                                          Position2d position, Size vertexIdx ) const
{
    Position2d bearing = Position2d( (float)glyph.BearingX, (float)glyph.BearingY );

    switch ( vertexIdx % 4 )
    {
        case 0:
            Position2d quadTopLeft = Position2d( 0.f, 0.f );
            TextAcc::GetPos( vertex ) = quadTopLeft + position + bearing;
            break;
        case 1:
            Position2d quadTopRight = Position2d( (float)glyph.Width, 0.f );
            TextAcc::GetPos( vertex ) = quadTopRight + position + bearing;
            break;
        case 2:
            Position2d quadBottomLeft = Position2d( 0.f, -(float)glyph.Height );
            TextAcc::GetPos( vertex ) = quadBottomLeft + position + bearing;
            break;
        case 3:
            Position2d quadBottomRight = Position2d( (float)glyph.Width, -(float)glyph.Height );
            TextAcc::GetPos( vertex ) = quadBottomRight + position + bearing;
            break;
    }
}

// ================================ //

template < typename VertexType, typename IndexType, typename TextAcc >
inline void
TextGeometryGenerator< VertexType, IndexType, TextAcc >::PutLetterUV( VertexType& vertex, const Glyph& glyph,
                                                                      Position2d position, Size vertexIdx ) const
{
    auto texLeft = (float)glyph.TextureX / m_atlasWidth;
    auto texTop = (float)glyph.TextureY / m_atlasHeight;
    auto texWidth = (float)glyph.Width / m_atlasWidth;
    auto texHeight = (float)glyph.Height / m_atlasHeight;

    switch ( vertexIdx % 4 )
    {
        case 0:
            TextAcc::GetUV( vertex ) = Position2d( texLeft, texTop );
            break;
        case 1:
            TextAcc::GetUV( vertex ) = Position2d( texLeft + texWidth, texTop );
            break;
        case 2:
            TextAcc::GetUV( vertex ) = Position2d( texLeft, texTop + texHeight );
            break;
        case 3:
            TextAcc::GetUV( vertex ) = Position2d( texLeft + texWidth, texTop + texHeight );
            break;
    }
}

// ================================ //

template< typename VertexType, typename IndexType, typename TextAcc >
template< class IndexBuffer >
inline void         TextGeometryGenerator< VertexType, IndexType, TextAcc >::GenerateIndexBuffer( IndexBuffer& idxBuffer, Size startIdx )
{
    IndexType numVerts = (IndexType)GetNumberVerticies();
    IndexType curVertex = 0;

    // We always add rectangles. Each rectangle has 4 vertices and 6 indices.
    while( curVertex < numVerts )
    {
        AddTriangleCW( idxBuffer, startIdx, curVertex, curVertex + 1, curVertex + 2 );
        AddTriangleCW( idxBuffer, startIdx, curVertex + 1, curVertex + 3, curVertex + 2 );

        curVertex += 4;
    }
}


}	// sw

