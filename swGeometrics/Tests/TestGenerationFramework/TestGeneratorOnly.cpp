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


}

