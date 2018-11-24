#pragma once
/**
@file Circle.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Circle.h"

#include "swCommonLib/Common/Converters.h"

#define _USE_MATH_DEFINES
#include <math.h>


namespace sw {
namespace geom
{

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline				Circle< VertexType, IndexType, PositionAcc >::Circle		()
	:	Tesselation( 10 )
	,	Radius( 1.0f )
{}


// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline void			Circle< VertexType, IndexType, PositionAcc >::GenerateVertex		( VertexType& vertex, Size vertexIdx )
{
	float angleDelta = float( 2 * M_PI / Tesselation );
	float angle = angleDelta * vertexIdx;

	auto& pos = PositionAcc::Get( vertex );
	pos.x = Radius * sinf( angle );
	pos.y = Radius * cosf( angle );
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
template< class IndexBuffer >
inline void			Circle< VertexType, IndexType, PositionAcc >::GenerateIndexBuffer	( IndexBuffer& idxBuffer, Size startIdx )
{
	IndexType numVerts = (IndexType)GetNumberVerticies();
	IndexType rightIdx = 1;
	IndexType leftIdx = numVerts - 1;	// Last vertex.

	// Add top triangle without pair.
	AddTriangle( idxBuffer, (IndexType)startIdx, 0, rightIdx, leftIdx );
	startIdx += 3;

	// Add pairs of triangles from left to right side of circle.
	while( leftIdx - rightIdx > 3 )
	{
		AddTriangle( idxBuffer, (IndexType)startIdx, leftIdx, rightIdx, leftIdx - 1 );
		AddTriangle( idxBuffer, (IndexType)startIdx + 3, leftIdx - 1, rightIdx, rightIdx + 1 );

		rightIdx++;
		leftIdx--;
		startIdx += 6;
	}

	// If there's one vertex left, we need to add one triangle else. Note that if
	// we have even number of verticies, two last verticies were already used to create two traingles
	// in previous while loop.
	if( leftIdx - rightIdx == 2 )
		AddTriangle( idxBuffer, (IndexType)startIdx, leftIdx, rightIdx, leftIdx - 1 );
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
template< class IndexBuffer >
inline void			Circle< VertexType, IndexType, PositionAcc >::AddTriangle			( IndexBuffer& idxBuffer, IndexType startIdx, IndexType vertIdx1, IndexType vertIdx2, IndexType vertIdx3 )
{
	idxBuffer[ startIdx ] = vertIdx1;
	idxBuffer[ startIdx + 1 ] = vertIdx2;
	idxBuffer[ startIdx + 2 ] = vertIdx3;
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size			Circle< VertexType, IndexType, PositionAcc >::GetNumberVerticies	() const
{
	return Tesselation;
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size			Circle< VertexType, IndexType, PositionAcc >::GetNumberIndicies		() const
{
	return 3 * ( Tesselation - 2 );
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline ReturnResult Circle< VertexType, IndexType, PositionAcc >::ValidateParams		() const
{
	if( Tesselation <= 2 )
		return "Invalid parameter [Tesselation=" + Convert::ToString( Tesselation ) + "] should be greater then 2.";

	return Result::Success;
}




}	// geom
}	// sw


