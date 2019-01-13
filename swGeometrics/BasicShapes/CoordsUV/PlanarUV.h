#pragma once
/**
@file PlanarUV.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"

#include "swGeometrics/GeometricsCore/Types/Traits/ProcessorTraits.h"


namespace sw {
namespace geom
{

/**@brief Generated planar UV mapping.
@ingroup Coordinates*/
template< typename VertexType, typename PositionAcc = DefaultPositionAcc< VertexType >, typename UVAcc = DefaultUVAcc< VertexType > >
class PlanarUV : public ProcessorTraits< VertexType >
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


	ReturnResult		ValidateParams			() const;
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

// ================================ //
//
template< typename VertexType, typename PositionAcc, typename UVAcc >
inline ReturnResult			PlanarUV< VertexType, PositionAcc, UVAcc >::ValidateParams			() const
{
	ErrorsCollector collector;

	if( MinX >= MaxX )
		collector.Add( "[PlanarUV] Invalid parameter [MaxX=" + Convert::ToString( MaxX ) + "] should be greater then [MinX=" + Convert::ToString( MinX ) + "]." );

	if( MinY >= MaxY )
		collector.Add( "[PlanarUV] Invalid parameter [MaxY=" + Convert::ToString( MaxY ) + "] should be greater then [MinY=" + Convert::ToString( MinY ) + "]." );

	return collector;
}

}	// geom
}	// sw


