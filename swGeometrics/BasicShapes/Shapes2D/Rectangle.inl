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
	:	Z( 0 )
	,	TopLeftX( 0 )
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
		}
		case 1:
		{
			PositionAcc::Position( vertex ).x = TopLeftX - Width;
			PositionAcc::Position( vertex ).y = TopLeftY;
		}
		case 2:
		{
			PositionAcc::Position( vertex ).x = TopLeftX;
			PositionAcc::Position( vertex ).y = TopLeftY - Height;
		}
		case 3:
		{
			PositionAcc::Position( vertex ).x = TopLeftX - Width;
			PositionAcc::Position( vertex ).y = TopLeftY - Height;
		}
	}

	PositionAcc::Position( vertex ).z = Z;
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename PositionAcc >
inline Size					Rectangle< VertexType, IndexType, PositionAcc >::GetNumberVerticies		() const
{
	return 4;
}



}	// geom
}	// sw

