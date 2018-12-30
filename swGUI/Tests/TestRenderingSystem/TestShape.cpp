#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"
#include "swGUI/Core/System/Rendering/Drawings/GeometryDrawing.h"
#include "swGUI/TestFramework/Utils/Mocks/Media/FakeBrush.h"
#include "swGUI/TestFramework/Utils/Mocks/Media/FakeGeometry.h"

#include "swGUI/Core/Controls/Shapes/Shape.h"
#include "swGUI/TestFramework/Utils/ClassesUI/TestShape.h"



using namespace sw;
using namespace sw::gui;

//====================================================================================//
//			Helper functions	
//====================================================================================//


// ================================ //
//
TestShapeOPtr			CreateTestShape		()
{
	TestShapeOPtr shape = TestShapeOPtr( new TestShape() );

	FakeBrushPtr brush = std::make_shared< FakeBrush >();
	FakeBrushPtr pen = std::make_shared< FakeBrush >();
	FakeGeometryPtr geom = std::make_shared< FakeGeometry >( Geometry::ConstantBufferMode::Disable );

	shape->SetFill( brush );
	shape->SetStroke( pen );
	shape->SetGeometry( geom );

	return shape;
}



//====================================================================================//
//			Tests	
//====================================================================================//

// ================================ //
// Drawing should be created only when geometry is created.
TEST_CASE( "GUI.Rendering.GeometryDrawing.DrawingCreation", "[GUISystem][RenderingSystem][GeometryDrawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	TestShapeOPtr shape = TestShapeOPtr( new TestShape() );

	FakeBrushPtr brush = std::make_shared< FakeBrush >();
	FakeBrushPtr pen = std::make_shared< FakeBrush >();
	FakeGeometryPtr geom = std::make_shared< FakeGeometry >( Geometry::ConstantBufferMode::Disable );

	// Setting Fill without geometry shouldn't create Drawing.
	shape->SetFill( brush );
	CHECK( shape->QueryDrawing() == nullptr );

	// Setting Brush without geometry shouldn't create drawing.
	shape->SetStroke( pen );
	CHECK( shape->QueryDrawing() == nullptr );

	// Setting Geometry should create Drawing.
	shape->SetGeometry( geom );
	CHECK( shape->QueryDrawing() != nullptr );

	auto geomDrawing = static_cast< GeometryDrawing* >( shape->QueryDrawing() );
	CHECK( geomDrawing->GetBrush() == brush );
	CHECK( geomDrawing->GetPen() == pen );
	CHECK( geomDrawing->GetGeometry() == geom );
}



// ================================ //
// Setting new brush should recreate drawing.
TEST_CASE( "GUI.Rendering.GeometryDrawing.DrawingUpdate.DifferentBrush", "[GUISystem][RenderingSystem][GeometryDrawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	TestShapeOPtr shape = CreateTestShape();

	auto prevDrawing = shape->QueryDrawing();
	REQUIRE( prevDrawing != nullptr );

	FakeBrushPtr newBrush = std::make_shared< FakeBrush >();
	shape->SetFill( newBrush );

	CHECK( shape->QueryDrawing() != nullptr );
	CHECK( shape->QueryDrawing() != prevDrawing );

	auto geomDrawing = static_cast< GeometryDrawing* >( shape->QueryDrawing() );
	CHECK( geomDrawing->GetBrush() == shape->GetFill() );
	CHECK( geomDrawing->GetBrush() == newBrush );
	CHECK( geomDrawing->GetPen() == shape->GetStroke() );
	CHECK( geomDrawing->GetGeometry() == shape->GetGeometry() );
}

// ================================ //
// Setting the same brush shouldn't recreate Drawing.
TEST_CASE( "GUI.Rendering.GeometryDrawing.DrawingUpdate.SameBrush", "[GUISystem][RenderingSystem][GeometryDrawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	TestShapeOPtr shape = CreateTestShape();

	auto prevDrawing = shape->QueryDrawing();
	REQUIRE( prevDrawing != nullptr );

	shape->SetFill( shape->GetFill() );
	CHECK( shape->QueryDrawing() == prevDrawing );
}

// ================================ //
// Setting new pen should recreate drawing.
TEST_CASE( "GUI.Rendering.GeometryDrawing.DrawingUpdate.DifferentPen", "[GUISystem][RenderingSystem][GeometryDrawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	TestShapeOPtr shape = CreateTestShape();

	auto prevDrawing = shape->QueryDrawing();
	REQUIRE( prevDrawing != nullptr );

	FakeBrushPtr newPen = std::make_shared< FakeBrush >();
	shape->SetStroke( newPen );

	CHECK( shape->QueryDrawing() != nullptr );
	CHECK( shape->QueryDrawing() != prevDrawing );

	auto geomDrawing = static_cast< GeometryDrawing* >( shape->QueryDrawing() );
	CHECK( geomDrawing->GetBrush() == shape->GetFill() );
	CHECK( geomDrawing->GetPen() == shape->GetStroke() );
	CHECK( geomDrawing->GetPen() == newPen );
	CHECK( geomDrawing->GetGeometry() == shape->GetGeometry() );
}

// ================================ //
// Setting the same pen shouldn't recreate Drawing.
TEST_CASE( "GUI.Rendering.GeometryDrawing.DrawingUpdate.SamePen", "[GUISystem][RenderingSystem][GeometryDrawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	TestShapeOPtr shape = CreateTestShape();

	auto prevDrawing = shape->QueryDrawing();
	REQUIRE( prevDrawing != nullptr );

	shape->SetStroke( shape->GetStroke() );
	CHECK( shape->QueryDrawing() == prevDrawing );
}

// ================================ //
// Setting new geometry should recreate drawing.
TEST_CASE( "GUI.Rendering.GeometryDrawing.DrawingUpdate.DifferentGeometry", "[GUISystem][RenderingSystem][GeometryDrawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	TestShapeOPtr shape = CreateTestShape();

	auto prevDrawing = shape->QueryDrawing();
	REQUIRE( prevDrawing != nullptr );

	FakeGeometryPtr newGeom = std::make_shared< FakeGeometry >( Geometry::ConstantBufferMode::Disable );
	shape->SetGeometry( newGeom );

	CHECK( shape->QueryDrawing() != nullptr );
	CHECK( shape->QueryDrawing() != prevDrawing );

	auto geomDrawing = static_cast< GeometryDrawing* >( shape->QueryDrawing() );
	CHECK( geomDrawing->GetBrush() == shape->GetFill() );
	CHECK( geomDrawing->GetPen() == shape->GetStroke() );
	CHECK( geomDrawing->GetGeometry() == shape->GetGeometry() );
	CHECK( geomDrawing->GetGeometry() == newGeom );
}

// ================================ //
// Setting the same geometry shouldn't recreate Drawing.
TEST_CASE( "GUI.Rendering.GeometryDrawing.DrawingUpdate.SameGeometry", "[GUISystem][RenderingSystem][GeometryDrawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	TestShapeOPtr shape = CreateTestShape();
	FakeGeometryPtr geom = std::make_shared< FakeGeometry >( Geometry::ConstantBufferMode::Disable );
	shape->SetGeometry( geom );

	auto prevDrawing = shape->QueryDrawing();
	REQUIRE( prevDrawing != nullptr );

	shape->SetGeometry( geom );
	CHECK( shape->QueryDrawing() == prevDrawing );
}
