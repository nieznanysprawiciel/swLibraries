#pragma once
/**
@file EllipseWithBorder.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "EllipseWithBorder.h"




namespace sw {
namespace geom
{

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline						EllipseWithBorder< VertexType, IndexType, PositionAcc >::EllipseWithBorder				()
	:	StrokeThickness( 0 )
{}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline void					EllipseWithBorder< VertexType, IndexType, PositionAcc >::GenerateVertex					( VertexType& vertex, Size vertexIdx )
{
	if( vertexIdx < Parent::GetNumberVerticies() )
		Parent::GenerateVertex( vertex, vertexIdx, Width, Height );
	else
		Parent::GenerateVertex( vertex, vertexIdx, Width - 2 * StrokeThickness, Height - 2 * StrokeThickness );
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
template< class IndexBuffer >
inline void					EllipseWithBorder< VertexType, IndexType, PositionAcc >::GenerateIndexBuffer			( IndexBuffer& idxBuffer, Size startIdx )
{
	Parent::GenerateIndexBuffer( idxBuffer, startIdx );

	startIdx += Parent::GetNumberIndicies();
	IndexType borderOffset = (IndexType)Parent::GetNumberVerticies();

	IndexType idx = 0;
	for( ; idx < Parent::GetNumberVerticies() - 1; ++idx )
	{
		AddTriangleCW( idxBuffer, startIdx, idx + borderOffset, idx, idx + borderOffset + 1 );
		AddTriangleCW( idxBuffer, startIdx, idx + borderOffset + 1, idx, idx + 1 );
	}

	// Last triangles reference last and first vertex.
	AddTriangleCW( idxBuffer, startIdx, idx + borderOffset, idx, borderOffset );
	AddTriangleCW( idxBuffer, startIdx, borderOffset, idx, 0 );
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size					EllipseWithBorder< VertexType, IndexType, PositionAcc >::GetNumberVerticies				() const
{
	return 2 * Parent::GetNumberVerticies();
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size					EllipseWithBorder< VertexType, IndexType, PositionAcc >::GetNumberIndicies				() const
{
	return Parent::GetNumberIndicies() + GetNumberBorderIndicies();
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size					EllipseWithBorder< VertexType, IndexType, PositionAcc >::GetNumberFillIndicies			() const
{
	return Parent::GetNumberIndicies();
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size					EllipseWithBorder< VertexType, IndexType, PositionAcc	>::GetNumberBorderIndicies		() const
{
	return 6 * Parent::GetNumberVerticies();
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline ReturnResult			EllipseWithBorder< VertexType, IndexType, PositionAcc >::ValidateParams					() const
{
	ErrorsCollector collector;
	collector.Add( Parent::ValidateParams() );

	if( Width <= 2 * StrokeThickness )
		collector.Add( "[EllipseWithBorder] Invalid parameter [StrokeThickness=" + Convert::ToString( StrokeThickness ) + "]. Width <= 2 * StrokeThickness" );

	if( Height <= 2 * StrokeThickness )
		collector.Add( "[EllipseWithBorder] Invalid parameter [StrokeThickness=" + Convert::ToString( StrokeThickness ) + "]. Height <= 2 * StrokeThickness" );

	return collector;
}


}	// geom
}	// sw


