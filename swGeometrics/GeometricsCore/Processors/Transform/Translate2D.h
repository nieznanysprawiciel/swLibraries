#pragma once
/**
@file Translate2D.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"

#include "swGeometrics/GeometricsCore/Types/Traits/ProcessorTraits.h"
#include "swGeometrics/GeometricsCore/Types/Accessors/DefaultAccessors.h"


namespace sw {
namespace geom
{


/**@brief Generated planar UV mapping.
@ingroup Coordinates*/
template< typename VertexType, typename PositionAcc = DefaultPositionAcc< VertexType > >
class Translate2D : public ProcessorTraits< VertexType >
{
private:
public:

	float				TranslateX;
	float				TranslateY;

public:

	inline explicit		Translate2D				();
	inline explicit		Translate2D				( float x, float y );

	inline void			GenerateVertex			( VertexType& vertex, Size vertexIdx );


	ReturnResult		ValidateParams			() const;
};

//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
template< typename VertexType, typename PositionAcc >
inline						Translate2D< VertexType, PositionAcc >::Translate2D				()
	:	TranslateX( 0.0f )
	,	TranslateY( 0.0f )
{}

// ================================ //
//
template< typename VertexType, typename PositionAcc >
inline						Translate2D< VertexType, PositionAcc >::Translate2D				( float x, float y )
	:	TranslateX( x )
	,	TranslateY( y )
{}

// ================================ //
//
template< typename VertexType, typename PositionAcc >
inline void					Translate2D< VertexType, PositionAcc >::GenerateVertex			( VertexType& vertex, Size )
{
	auto& vertexPos = PositionAcc::Get( vertex );

	vertexPos.x += TranslateX;
	vertexPos.y += TranslateY;
}

// ================================ //
//
template< typename VertexType, typename PositionAcc >
inline ReturnResult			Translate2D< VertexType, PositionAcc >::ValidateParams			() const
{
	ErrorsCollector collector;

	if( !isfinite( TranslateX ) )
		collector.Add( "[Translate2D] Invalid parameter [TranslateX=" + Convert::ToString( TranslateX ) + "].");

	if( !isfinite( TranslateY ) )
		collector.Add( "[Translate2D] Invalid parameter [TranslateY=" + Convert::ToString( TranslateY ) + "].");

	return collector;
}




}	// geom
}	// sw

