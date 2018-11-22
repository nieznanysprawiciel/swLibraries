#include "swCommonLib/External/Catch/catch.hpp"


#include "swGeometrics/GeometricsCore/Generators/Generator.h"
#include "swGeometrics/GeometricsCore/Types/VertexLayouts/VertexShape2D.h"
#include "swGeometrics/GeometricsCore/Types/IndexTypes.h"

#include "swGeometrics/BasicShapes/Shapes2D/Rectangle.h"
#include "swGeometrics/BasicShapes/CoordsUV/PlanarUV.h"


using namespace sw;
using namespace sw::geom;




// ================================ //
//
TEST_CASE( "Geometrics.Generation.GeneratorAndProcessing", "[Geometrics]" )
{
	Rectangle< VertexShape2D, Index16 > rect;
	rect.TopLeftX = 30;
	rect.TopLeftY = 30;
	rect.Height = 20;
	rect.Width = 20;

	PlanarUV< VertexShape2D > planarUV;
	planarUV.MinX = 30;
	planarUV.MinY = 10;
	planarUV.MaxX = 50;
	planarUV.MaxY = 30;

	auto geometry = Generate( rect, planarUV );

	CHECK( geometry.Verticies.size() == 4 );
	CHECK( geometry.Indicies.size() == 6 );

	CHECK( geometry.Verticies[ 0 ].UV.x == 0.0 );
	CHECK( geometry.Verticies[ 0 ].UV.y == 1.0f );

	CHECK( geometry.Verticies[ 1 ].UV.x == 1.0f );
	CHECK( geometry.Verticies[ 1 ].UV.y == 1.0f );

	CHECK( geometry.Verticies[ 2 ].UV.x == 0.0f );
	CHECK( geometry.Verticies[ 2 ].UV.y == 0.0f );

	CHECK( geometry.Verticies[ 3 ].UV.x == 1.0f );
	CHECK( geometry.Verticies[ 3 ].UV.y == 0.0f );
}

