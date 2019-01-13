#include "swCommonLib/External/Catch/catch.hpp"


#include "swGeometrics/GeometricsCore/Generators/Generator.h"
#include "swGeometrics/GeometricsCore/Types/VertexLayouts/VertexShape2D.h"
#include "swGeometrics/GeometricsCore/Types/IndexTypes.h"

#include "swGeometrics/BasicShapes/Shapes2D/Rectangle.h"


using namespace sw;
using namespace sw::geom;


// ================================ //
//
TEST_CASE( "Geometrics.Generation.GeneratorOnly", "[Geometrics]" )
{
	Rectangle< VertexShape2D, Index16 > rect;
	rect.TopLeftX = 30;
	rect.TopLeftY = 30;
	rect.Height = 20;
	rect.Width = 20;

	auto geometry = Generate< IndexedGeometry< VertexShape2D, Index16 > >( rect ).Get();
	
	// Check vertex buffer.
	CHECK( geometry.Verticies.size() == 4 );

	CHECK( geometry.Verticies[ 0 ].Position.x == 30 );
	CHECK( geometry.Verticies[ 0 ].Position.y == 30 );

	CHECK( geometry.Verticies[ 1 ].Position.x == 50 );
	CHECK( geometry.Verticies[ 1 ].Position.y == 30 );

	CHECK( geometry.Verticies[ 2 ].Position.x == 30 );
	CHECK( geometry.Verticies[ 2 ].Position.y == 10 );

	CHECK( geometry.Verticies[ 3 ].Position.x == 50 );
	CHECK( geometry.Verticies[ 3 ].Position.y == 10 );

	// Check index buffer
	CHECK( geometry.Indicies.size() == 6 );
}

