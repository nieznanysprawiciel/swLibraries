#include "swCommonLib/External/Catch/catch.hpp"


#include "swGeometrics/GeometricsCore/Generators/Generator.h"
#include "swGeometrics/GeometricsCore/Types/VertexLayouts/VertexShape2D.h"
#include "swGeometrics/GeometricsCore/Types/IndexTypes.h"

#include "swGeometrics/BasicShapes/Shapes2D/Ellipse.h"


using namespace sw;
using namespace sw::geom;


//====================================================================================//
//			Helper functions	
//====================================================================================//

// ================================ //
// Defined in TestCircle.cpp
bool		IsOnCircle		( const DirectX::XMFLOAT2& vertex, float radius );

// ================================ //
//
bool		IsEllipse		( const std::vector< VertexShape2D >& verticies, float width, float height )
{
	bool isCircle = true;
	for( auto& vertex : verticies )
	{
		auto scaleToCircle = DirectX::XMFLOAT2( 2.0f * vertex.Position.x / width, 2.0f * vertex.Position.y / height );
		if( !IsOnCircle( scaleToCircle, 1.0f ) )
			return false;
	}

	return true;
}


// ================================ //
//
TEST_CASE( "Geometrics.BasicShapes.Ellipse.EvenTesselation", "[Geometrics][BasicShapes]" )
{
	Ellipse< VertexShape2D, Index16 > ellipse;
	ellipse.Width = 2.5f;
	ellipse.Height = 0.5f;
	ellipse.Tesselation = 30;

	auto geometry = Generate< IndexedGeometry< VertexShape2D, Index16 > >( ellipse ).Get();

	CHECK( geometry.Verticies.size() == 30 );
	CHECK( geometry.Indicies.size() == 84 );

	bool isCircle = IsEllipse( geometry.Verticies, 2.5f, 0.5f );
	CHECK( isCircle == true );
}

// ================================ //
//
TEST_CASE( "Geometrics.BasicShapes.Ellipse.OddTesselation", "[Geometrics][BasicShapes]" )
{
	Ellipse< VertexShape2D, Index16 > ellipse;
	ellipse.Width = 1.0f;
	ellipse.Height = 4.0f;
	ellipse.Tesselation = 31;

	auto geometry = Generate< IndexedGeometry< VertexShape2D, Index16 > >( ellipse ).Get();

	CHECK( geometry.Verticies.size() == 31 );
	CHECK( geometry.Indicies.size() == 87 );

	bool isCircle = IsEllipse( geometry.Verticies, 1.0f, 4.0f );
	CHECK( isCircle == true );
}

// ================================ //
// Circle should have Tesselation parameter set at least to 3.
TEST_CASE( "Geometrics.BasicShapes.Ellipse.ToLowTesselation", "[Geometrics][BasicShapes]" )
{
	Ellipse< VertexShape2D, Index16 > ellipse;
	ellipse.Width = 2.5f;
	ellipse.Height = 0.5f;
	ellipse.Tesselation = 0;

	CHECK( Generate< IndexedGeometry< VertexShape2D, Index16 > >( ellipse ).IsValid() == false );

	ellipse.Tesselation = 1;
	CHECK( Generate< IndexedGeometry< VertexShape2D, Index16 > >( ellipse ).IsValid() == false );

	ellipse.Tesselation = 2;
	CHECK( Generate< IndexedGeometry< VertexShape2D, Index16 > >( ellipse ).IsValid() == false );
}


// ================================ //
// Radius should be greater then 0.
TEST_CASE( "Geometrics.BasicShapes.Ellipse.NegativeRadius", "[Geometrics][BasicShapes]" )
{
	Ellipse< VertexShape2D, Index16 > ellipse;
	ellipse.Width = -2.5f;
	ellipse.Height = -0.5f;
	ellipse.Tesselation = 10;

	CHECK( Generate< IndexedGeometry< VertexShape2D, Index16 > >( ellipse ).IsValid() == false );
}
