#pragma once
/**
@file RectangleWithBorder.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "RectangleWithBorder.h"

#include "swCommonLib/Common/Exceptions/Exception.h"
#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"
#include "swCommonLib/Common/Converters.h"



namespace sw {
namespace geom
{


// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline						RectangleWithBorder< VertexType, IndexType, PositionAcc >::RectangleWithBorder()
	:	StrokeThickness( 0 )
{}


// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline void					RectangleWithBorder< VertexType, IndexType, PositionAcc >::GenerateVertex			( VertexType& vertex, Size vertexIdx )
{
	Parent::GenerateVertex( vertex, vertexIdx );

	switch( vertexIdx )
	{
		case 4:
		{
			PositionAcc::Get( vertex ).x = TopLeftX + StrokeThickness;
			PositionAcc::Get( vertex ).y = TopLeftY - StrokeThickness;
			break;
		}
		case 5:
		{
			PositionAcc::Get( vertex ).x = TopLeftX + Width - StrokeThickness;
			PositionAcc::Get( vertex ).y = TopLeftY - StrokeThickness;
			break;
		}
		case 6:
		{
			PositionAcc::Get( vertex ).x = TopLeftX + Width - StrokeThickness;
			PositionAcc::Get( vertex ).y = TopLeftY - Height + StrokeThickness;
			break;
		}
		case 7:
		{
			PositionAcc::Get( vertex ).x = TopLeftX + StrokeThickness;
			PositionAcc::Get( vertex ).y = TopLeftY - Height + StrokeThickness;
			break;
		}
	}
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
template< class IndexBuffer >
inline void					RectangleWithBorder< VertexType, IndexType, PositionAcc >::GenerateIndexBuffer	( IndexBuffer& idxBuffer, Size startIdx )
{
	Parent::GenerateIndexBuffer( idxBuffer, startIdx );

	startIdx += Parent::GetNumberIndicies();
	for( IndexType idx = 0; idx < 4; ++idx )
	{
		AddTriangleCW( idxBuffer, startIdx, idx, ( idx + 1 ) % 4, idx % 4 + 4 );
		AddTriangleCW( idxBuffer, startIdx, ( idx + 1 ) % 4, 4 + ( idx + 1 ) % 4, idx % 4 + 4 );
	}
}


// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size					RectangleWithBorder< VertexType, IndexType, PositionAcc >::GetNumberVerticies		() const
{
	return Parent::GetNumberVerticies() + 4;
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size					RectangleWithBorder< VertexType, IndexType, PositionAcc >::GetNumberIndicies		() const
{
	return Parent::GetNumberIndicies() + GetNumberBorderIndicies();
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size					RectangleWithBorder< VertexType, IndexType, PositionAcc >::GetNumberFillIndicies		() const
{
	return Parent::GetNumberIndicies();
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size					RectangleWithBorder< VertexType, IndexType, PositionAcc	>::GetNumberBorderIndicies		() const
{
	return 24;
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline ReturnResult			RectangleWithBorder< VertexType, IndexType, PositionAcc >::ValidateParams			() const
{
	ErrorsCollector collector;
	collector.Add( Parent::ValidateParams() );

	if( Width <= 2 * StrokeThickness )
		collector.Add( "[RectangleWithBorder] Invalid parameter [StrokeThickness=" + Convert::ToString( StrokeThickness ) + "]. Width <= 2 * StrokeThickness" );

	if( Height <= 2 * StrokeThickness )
		collector.Add( "[RectangleWithBorder] Invalid parameter [StrokeThickness=" + Convert::ToString( StrokeThickness ) + "]. Height <= 2 * StrokeThickness" );

	return collector;
}



}	// geom
}	// sw

