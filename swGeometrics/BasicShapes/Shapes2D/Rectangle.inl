#pragma once
/**
@file Rectangle.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Rectangle.h"

#include "swCommonLib/Common/Exceptions/Exception.h"
#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"
#include "swCommonLib/Common/Converters.h"



namespace sw {
namespace geom
{


// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline						Rectangle< VertexType, IndexType, PositionAcc >::Rectangle()
	:	TopLeftX( 0 )
	,	TopLeftY( 0 )
	,	Width( 0 )
	,	Height( 0 )
{}


// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline void					Rectangle< VertexType, IndexType, PositionAcc >::GenerateVertex			( VertexType& vertex, Size vertexIdx )
{
	switch( vertexIdx )
	{
		case 0:
		{
			PositionAcc::Get( vertex ).x = TopLeftX;
			PositionAcc::Get( vertex ).y = TopLeftY;
			break;
		}
		case 1:
		{
			PositionAcc::Get( vertex ).x = TopLeftX + Width;
			PositionAcc::Get( vertex ).y = TopLeftY;
			break;
		}
		case 2:
		{
			PositionAcc::Get( vertex ).x = TopLeftX;
			PositionAcc::Get( vertex ).y = TopLeftY - Height;
			break;
		}
		case 3:
		{
			PositionAcc::Get( vertex ).x = TopLeftX + Width;
			PositionAcc::Get( vertex ).y = TopLeftY - Height;
			break;
		}
	}
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
template< class IndexBuffer >
inline void					Rectangle< VertexType, IndexType, PositionAcc >::GenerateIndexBuffer	( IndexBuffer& idxBuffer, Size startIdx )
{
	AddTriangleCW( idxBuffer, startIdx, 0, 1, 2 );
	AddTriangleCW( idxBuffer, startIdx, 0, 2, 3 );
}


// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size					Rectangle< VertexType, IndexType, PositionAcc >::GetNumberVerticies		() const
{
	return 4;
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size					Rectangle< VertexType, IndexType, PositionAcc >::GetNumberIndicies		() const
{
	return 6;
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline ReturnResult			Rectangle< VertexType, IndexType, PositionAcc >::ValidateParams			() const
{
	ErrorsCollector collector;

	if( Width <= 0.0f )
		collector.Add( "[Rectangle] Invalid parameter [Width=" + Convert::ToString( Width ) + "] should be greater then 0.0f." );

	if( Height <= 0.0f )
		collector.Add( "[Rectangle] Invalid parameter [Height=" + Convert::ToString( Height ) + "] should be greater then 0.0f." );

	return collector;
}



}	// geom
}	// sw

