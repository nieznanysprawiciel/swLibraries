#pragma once
/**
@file Ellipse.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Ellipse.h"

#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"

#define _USE_MATH_DEFINES
#include <math.h>



namespace sw {
namespace geom
{

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline				Ellipse< VertexType, IndexType, PositionAcc >::Ellipse		()
	:	Tesselation( 10 )
	,	Width( 1.0f )
	,	Height( 1.0f )
{}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline void			Ellipse< VertexType, IndexType, PositionAcc >::GenerateVertex		( VertexType& vertex, Size vertexIdx )
{
	float angleDelta = float( 2 * M_PI / Tesselation );
	float angle = angleDelta * vertexIdx;

	auto& pos = PositionAcc::Get( vertex );
	pos.x = Width * sinf( angle );
	pos.y = Height * cosf( angle );
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
template< class IndexBuffer >
inline void			Ellipse< VertexType, IndexType, PositionAcc >::GenerateIndexBuffer	( IndexBuffer& idxBuffer, Size startIdx )
{
	IndexType numVerts = (IndexType)GetNumberVerticies();
	IndexType rightIdx = 1;
	IndexType leftIdx = numVerts - 1;	// Last vertex.

	// Add top triangle without pair.
	AddTriangleCW( idxBuffer, startIdx, 0, rightIdx, leftIdx );

	// Add pairs of triangles from left to right side of circle.
	while( leftIdx - rightIdx > 3 )
	{
		AddTriangleCW( idxBuffer, startIdx, leftIdx, rightIdx, leftIdx - 1 );
		AddTriangleCW( idxBuffer, startIdx, leftIdx - 1, rightIdx, rightIdx + 1 );

		rightIdx++;
		leftIdx--;
	}

	// If there's one vertex left, we need to add one triangle else. Note that if
	// we have even number of verticies, two last verticies were already used to create two traingles
	// in previous while loop.
	if( leftIdx - rightIdx == 2 )
		AddTriangleCW( idxBuffer, startIdx, leftIdx, rightIdx, leftIdx - 1 );
}


// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size			Ellipse< VertexType, IndexType, PositionAcc >::GetNumberVerticies	() const
{
	return Tesselation;
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size			Ellipse< VertexType, IndexType, PositionAcc >::GetNumberIndicies		() const
{
	return 3 * ( Tesselation - 2 );
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline ReturnResult Ellipse< VertexType, IndexType, PositionAcc >::ValidateParams		() const
{
	ErrorsCollector collector;

	if( Tesselation <= 2 )
		collector.Add( "[Circle] Invalid parameter [Tesselation=" + Convert::ToString( Tesselation ) + "] should be greater then 2." );

	if( Width <= 0.0f )
		collector.Add( "[Circle] Invalid parameter [Width=" + Convert::ToString( Width ) + "] should be greater then 0." );

	if( Height <= 0.0f )
		collector.Add( "[Circle] Invalid parameter [Width=" + Convert::ToString( Height ) + "] should be greater then 0." );

	return collector;
}



}	// geom
}	// sw


