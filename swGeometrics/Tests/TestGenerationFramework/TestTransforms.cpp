#include "swCommonLib/External/Catch/catch.hpp"


#include "swGeometrics/GeometricsCore/Generators/Generator.h"
#include "swGeometrics/GeometricsCore/Types/VertexLayouts/VertexShape2D.h"
#include "swGeometrics/GeometricsCore/Types/IndexTypes.h"

#include "swGeometrics/GeometricsCore/Processors/Transform/Translate2D.h"

#include "swGeometrics/BasicShapes/Shapes2D/Rectangle.h"


#include <limits>


using namespace sw;
using namespace sw::geom;



// ================================ //
//
TEST_CASE( "Geometrics.Transforms.Translate2D.TranslateRect", "[Geometrics][Transform]" )
{
	Rectangle< VertexShape2D, Index16 > rect;
	rect.TopLeftX = 30;
	rect.TopLeftY = 30;
	rect.Height = 20;
	rect.Width = 20;

	auto geometry = Generate< IndexedGeometry< VertexShape2D, Index16 > >( rect, Translate2D< VertexShape2D >( 3.5f, 5.3f ) ).Get();
	
	// Check vertex buffer.
	CHECK( geometry.Verticies.size() == 4 );

	CHECK( geometry.Verticies[ 0 ].Position.x == 33.5f );
	CHECK( geometry.Verticies[ 0 ].Position.y == 35.3f );

	CHECK( geometry.Verticies[ 1 ].Position.x == 53.5f );
	CHECK( geometry.Verticies[ 1 ].Position.y == 35.3f );

	CHECK( geometry.Verticies[ 2 ].Position.x == 53.5f );
	CHECK( geometry.Verticies[ 2 ].Position.y == 15.3f );

	CHECK( geometry.Verticies[ 3 ].Position.x == 33.5f );
	CHECK( geometry.Verticies[ 3 ].Position.y == 15.3f );
}

// ================================ //
//
TEST_CASE( "Geometrics.Transforms.Translate2D.XisInfinity", "[Geometrics][Transform]" )
{
	Rectangle< VertexShape2D, Index16 > rect;
	rect.TopLeftX = 30;
	rect.TopLeftY = 30;
	rect.Height = 20;
	rect.Width = 20;

	auto geometry = Generate< IndexedGeometry< VertexShape2D, Index16 > >( rect, Translate2D< VertexShape2D >( std::numeric_limits< float >::infinity(), 5.3f ) );
	CHECK( geometry.IsValid() == false );
}

// ================================ //
//
TEST_CASE( "Geometrics.Transforms.Translate2D.YisInfinity", "[Geometrics][Transform]" )
{
	Rectangle< VertexShape2D, Index16 > rect;
	rect.TopLeftX = 30;
	rect.TopLeftY = 30;
	rect.Height = 20;
	rect.Width = 20;

	auto geometry = Generate< IndexedGeometry< VertexShape2D, Index16 > >( rect, Translate2D< VertexShape2D >( 5.3f, std::numeric_limits< float >::infinity() ) );
	CHECK( geometry.IsValid() == false );
}

// ================================ //
//
TEST_CASE( "Geometrics.Transforms.Translate2D.XisNaN", "[Geometrics][Transform]" )
{
	Rectangle< VertexShape2D, Index16 > rect;
	rect.TopLeftX = 30;
	rect.TopLeftY = 30;
	rect.Height = 20;
	rect.Width = 20;

	auto geometry = Generate< IndexedGeometry< VertexShape2D, Index16 > >( rect, Translate2D< VertexShape2D >( std::numeric_limits< float >::quiet_NaN(), 5.3f ) );
	CHECK( geometry.IsValid() == false );
}

// ================================ //
//
TEST_CASE( "Geometrics.Transforms.Translate2D.YisNaN", "[Geometrics][Transform]" )
{
	Rectangle< VertexShape2D, Index16 > rect;
	rect.TopLeftX = 30;
	rect.TopLeftY = 30;
	rect.Height = 20;
	rect.Width = 20;

	auto geometry = Generate< IndexedGeometry< VertexShape2D, Index16 > >( rect, Translate2D< VertexShape2D >( 5.3f, std::numeric_limits< float >::quiet_NaN() ) );
	CHECK( geometry.IsValid() == false );
}