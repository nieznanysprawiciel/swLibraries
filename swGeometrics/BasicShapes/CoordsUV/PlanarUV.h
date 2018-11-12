#pragma once
/**
@file PlanarUV.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"



namespace sw {
namespace geom
{

/**@brief Generated planar UV mapping.
@ingroup Coordinates*/
template< typename VertexType, typename PositionAcc = DefaultPositionAcc< VertexType >, typename UVAcc = DefaultUVAcc< VertexType > >
class PlanarUV
{
private:
public:

	float			MinX;
	float			MaxX;
	float			MinY;
	float			MaxY;

public:

	inline explicit		PlanarUV				();

	inline void			GenerateVertex			( VertexType& vertex, Size vertexIdx );

};


//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
template< typename VertexType, typename PositionAcc, typename UVAcc >
inline						PlanarUV< VertexType, PositionAcc, UVAcc >::PlanarUV				()
	:	MinX( -1.0f )
	,	MaxX( 1.0f )
	,	MinY( -1.0f )
	,	MaxY( 1.0f )
{}

// ================================ //
//
template< typename VertexType, typename PositionAcc, typename UVAcc >
inline void					PlanarUV< VertexType, PositionAcc, UVAcc >::GenerateVertex			( VertexType& vertex, Size )
{
	auto& vertexPos = PositionAcc::Get( vertex );
	auto& vertexUV = UVAcc::Get( vertex );

	float xRange = MaxX - MinX;
	float yRange = MaxY - MinY;

	vertexUV.x = ( vertexPos.x - MinX ) / xRange;
	vertexUV.y = ( vertexPos.y - MinY ) / yRange;
}

}	// geom
}	// sw


