#include "swCommonLib/External/Catch/catch.hpp"


#include "swGeometrics/GeometricsCore/Generators/Generator.h"
#include "swGeometrics/GeometricsCore/Types/VertexLayouts/VertexShape2D.h"
#include "swGeometrics/GeometricsCore/Types/IndexTypes.h"

#include "swGeometrics/BasicShapes/Shapes2D/Rectangle.h"
#include "swGeometrics/BasicShapes/CoordsUV/PlanarUV.h"

#include "swGeometrics/GeometricsCore/Types/Traits/GeneratorTraits.h"
#include "swGeometrics/GeometricsCore/Types/Traits/ProcessorTraits.h"



using namespace sw;
using namespace sw::geom;


// ================================ //
//
TEST_CASE( "Geometrics.Traits.isGenerator", "[Geometrics]" )
{
	bool isRectangleGenerator = isGenerator< Rectangle< VertexShape2D, Index16 > >::value;
	CHECK( isRectangleGenerator == true );

	bool isIntGenerator = isGenerator< int >::value;
	CHECK( isIntGenerator == false );

	bool isPlanarUVGenerator = isGenerator< PlanarUV< VertexShape2D > >::value;
	CHECK( isPlanarUVGenerator == false );
}


// ================================ //
//
TEST_CASE( "Geometrics.Traits.sProcessor", "[Geometrics]" )
{
	bool isRectangleProcessor = isProcessor< Rectangle< VertexShape2D, Index16 > >::value;
	CHECK( isRectangleProcessor == false );

	bool isIntProcessor = isProcessor< int >::value;
	CHECK( isIntProcessor == false );

	bool isPlanarUVProcessor = isProcessor< PlanarUV< VertexShape2D > >::value;
	CHECK( isPlanarUVProcessor == true );
}


