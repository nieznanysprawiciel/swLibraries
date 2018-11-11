#pragma once
/**
@file Rectangle.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Rectangle.h"



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
			PositionAcc::Position( vertex ).x = TopLeftX;
			PositionAcc::Position( vertex ).y = TopLeftY;
			break;
		}
		case 1:
		{
			PositionAcc::Position( vertex ).x = TopLeftX + Width;
			PositionAcc::Position( vertex ).y = TopLeftY;
			break;
		}
		case 2:
		{
			PositionAcc::Position( vertex ).x = TopLeftX;
			PositionAcc::Position( vertex ).y = TopLeftY - Height;
			break;
		}
		case 3:
		{
			PositionAcc::Position( vertex ).x = TopLeftX + Width;
			PositionAcc::Position( vertex ).y = TopLeftY - Height;
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
	idxBuffer[ startIdx + 0 ] = 0;
	idxBuffer[ startIdx + 1 ] = 1;
	idxBuffer[ startIdx + 2 ] = 2;

	idxBuffer[ startIdx + 3 ] = 1;
	idxBuffer[ startIdx + 4 ] = 3;
	idxBuffer[ startIdx + 5 ] = 2;
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



}	// geom
}	// sw

