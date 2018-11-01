#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"
#include "swGUI/TestFramework/Utils/Mocks/Rendering/FakeDrawing.h"
#include "swGUI/TestFramework/Utils/Mocks/Media/FakeBrush.h"

using namespace sw;
using namespace sw::gui;


//====================================================================================//
//			Shaders updates	
//====================================================================================//

// ================================ //
// Tests Drawing class shader update functions (interface for derived classes).
// Shader should be loaded on first use and updated after flag NeedsShaderUpdate is set to true.
TEST_CASE( "GUI.Rendering.Drawing.Brush.UpdateShader", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr brush = std::make_shared< FakeBrush >();
	
	// Set first shader
	brush->SetShaderFunction( "WorkingDir-RenderingSystem/shaders/FakeBrush.ps" );
	drawing->UpdateBrushShader( framework.GetRenderingSystem()->GetShaderProvider(), brush.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

	auto prevShader = renderingData.PixelShader;
	CHECK( renderingData.PixelShader != nullptr );

	// Change shader and check if ew shader was loaded.
	brush->SetShaderFunction( "WorkingDir-RenderingSystem/shaders/FakeBrush2.ps" );
	REQUIRE( brush->NeedsShaderUpdate() == true );										// Update request should be set.

	drawing->UpdateBrushShader( framework.GetRenderingSystem()->GetShaderProvider(), brush.get() );
	CHECK( renderingData.PixelShader != nullptr );										// Shader was loaded.
	CHECK( renderingData.PixelShader != prevShader );									// Shader is different then previous shader.

	CHECK( brush->NeedsShaderUpdate() == false );										// Update function should reset update flag.
}

// ================================ //
// Tests Drawing class shader update functions (interface for derived classes).
// Shader should be loaded on first use and updated after flag NeedsShaderUpdate is set to true.
TEST_CASE( "GUI.Rendering.Drawing.Pen.UpdateShader", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr brush = std::make_shared< FakeBrush >();
	
	// Set first shader
	brush->SetShaderFunction( "WorkingDir-RenderingSystem/shaders/FakeBrush.ps" );
	drawing->UpdatePenShader( framework.GetRenderingSystem()->GetShaderProvider(), brush.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );

	auto prevShader = renderingData.PixelShader;
	CHECK( renderingData.PixelShader != nullptr );

	// Change shader and check if ew shader was loaded.
	brush->SetShaderFunction( "WorkingDir-RenderingSystem/shaders/FakeBrush2.ps" );
	REQUIRE( brush->NeedsShaderUpdate() == true );										// Update request should be set.

	drawing->UpdatePenShader( framework.GetRenderingSystem()->GetShaderProvider(), brush.get() );
	CHECK( renderingData.PixelShader != nullptr );										// Shader was loaded.
	CHECK( renderingData.PixelShader != prevShader );									// Shader is different then previous shader.

	CHECK( brush->NeedsShaderUpdate() == false );										// Update function should reset update flag.
}


//====================================================================================//
//			Constant buffers updates	
//====================================================================================//

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.UpdateBrushConstants", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr brush = std::make_shared< FakeBrush >();

	drawing->UpdateBrushConstants( framework.GetResourceManager(), brush.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

	CHECK( renderingData.BrushConstants != nullptr );
}

