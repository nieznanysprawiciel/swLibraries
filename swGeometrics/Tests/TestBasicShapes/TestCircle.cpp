#include "swCommonLib/External/Catch/catch.hpp"


#include "swGeometrics/GeometricsCore/Generators/Generator.h"
#include "swGeometrics/GeometricsCore/Types/VertexLayouts/VertexShape2D.h"
#include "swGeometrics/GeometricsCore/Types/IndexTypes.h"

#include "swGeometrics/BasicShapes/Shapes2D/Circle.h"


using namespace sw;
using namespace sw::geom;


//====================================================================================//
//			Helper functions	
//====================================================================================//

// ================================ //
//
bool		IsOnCircle		( const DirectX::XMFLOAT2& vertex, float radius )
{
	auto vertexLen = pow( vertex.x, 2 ) + pow( vertex.y, 2 );
	auto radiusPow2 = radius * radius;

	if( abs( vertexLen - radiusPow2 ) < 0.0001 )
		return true;
	return false;
}

// ================================ //
//
bool		IsCircle		( const std::vector< VertexShape2D >& verticies, float radius )
{
	bool isCircle = true;
	for( auto& vertex : verticies )
	{
		if( !IsOnCircle( vertex.Position, radius ) )
			return false;
	}

	return true;
}


// ================================ //
//
TEST_CASE( "Geometrics.BasicShapes.Circle", "[Geometrics][BasicShapes]" )
{
	Circle< VertexShape2D, Index16 > circle;
	circle.Radius = 1.5f;
	circle.Tesselation = 30;

	auto geometry = Generate( circle );

	CHECK( geometry.Verticies.size() == 30 );
	CHECK( geometry.Indicies.size() == 84 );

	bool isCircle = IsCircle( geometry.Verticies, 1.5f );
	CHECK( isCircle == true );
}

