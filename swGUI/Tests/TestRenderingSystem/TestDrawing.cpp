#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"
#include "swGUI/TestFramework/Utils/Mocks/Rendering/FakeDrawing.h"
#include "swGUI/TestFramework/Utils/Mocks/Media/FakeBrush.h"
#include "swGUI/TestFramework/Utils/Mocks/Media/FakeGeometry.h"

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
	brush->SetShaderFunction( "shaders/FakeBrush.ps" );
	drawing->UpdateBrushShader( framework.GetRenderingSystem()->GetShaderProvider(), brush.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

	auto prevShader = renderingData.PixelShader;
	CHECK( renderingData.PixelShader != nullptr );

	// Change shader and check if ew shader was loaded.
	brush->SetShaderFunction( "shaders/FakeBrush2.ps" );
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
	FakeBrushPtr pen = std::make_shared< FakeBrush >();
	
	// Set first shader
	pen->SetShaderFunction( "shaders/FakeBrush.ps" );
	drawing->UpdatePenShader( framework.GetRenderingSystem()->GetShaderProvider(), pen.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );

	auto prevShader = renderingData.PixelShader;
	CHECK( renderingData.PixelShader != nullptr );

	// Change shader and check if ew shader was loaded.
	pen->SetShaderFunction( "shaders/FakeBrush2.ps" );
	REQUIRE( pen->NeedsShaderUpdate() == true );										// Update request should be set.

	drawing->UpdatePenShader( framework.GetRenderingSystem()->GetShaderProvider(), pen.get() );
	CHECK( renderingData.PixelShader != nullptr );										// Shader was loaded.
	CHECK( renderingData.PixelShader != prevShader );									// Shader is different then previous shader.

	CHECK( pen->NeedsShaderUpdate() == false );										// Update function should reset update flag.
}

// ================================ //
// Tests Drawing class shader update functions (interface for derived classes).
// Shader should be loaded on first use and updated after flag NeedsShaderUpdate is set to true.
TEST_CASE( "GUI.Rendering.Drawing.Geometry.UpdateShader", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeGeometryPtr geom = std::make_shared< FakeGeometry >( Geometry::ConstantBufferMode::Disable );
	
	// Set first shader
	geom->SetShaderFunction( "shaders/FakeGeom.vs" );
	drawing->UpdateVertexShader( framework.GetRenderingSystem()->GetShaderProvider(), geom.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetGeometryRenderingData( drawing.get() );

	auto prevShader = renderingData.VertexShader;
	CHECK( renderingData.VertexShader != nullptr );

	// Change shader and check if ew shader was loaded.
	geom->SetShaderFunction( "shaders/FakeGeom2.vs" );
	REQUIRE( geom->NeedsShaderUpdate() == true );										// Update request should be set.

	drawing->UpdateVertexShader( framework.GetRenderingSystem()->GetShaderProvider(), geom.get() );
	CHECK( renderingData.VertexShader != nullptr );										// Shader was loaded.
	CHECK( renderingData.VertexShader != prevShader );									// Shader is different then previous shader.

	CHECK( geom->NeedsShaderUpdate() == false );										// Update function should reset update flag.
}


//====================================================================================//
//			Textures update	
//====================================================================================//

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.Brush.UpdateTexture", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr brush = std::make_shared< FakeBrush >();

	auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

	brush->SetTextureFile( "textures/Tex1.png" );
	REQUIRE( brush->NeedsTextureUpdate() == true );										// Update request should be set.

	drawing->UpdateBrushTexture( framework.GetResourceManagerAPI(), brush.get() );
	CHECK( renderingData.Texture != nullptr );
	CHECK( brush->NeedsTextureUpdate() == false );

	brush->SetTextureFile( "textures/Tex2.png" );
	REQUIRE( brush->NeedsTextureUpdate() == true );										// Update request should be set.

	drawing->UpdateBrushTexture( framework.GetResourceManagerAPI(), brush.get() );
	CHECK( renderingData.Texture != nullptr );
	CHECK( brush->NeedsTextureUpdate() == false );
}

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.Pen.UpdateTexture", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr pen = std::make_shared< FakeBrush >();

	auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );

	pen->SetTextureFile( "textures/Tex1.png" );
	REQUIRE( pen->NeedsTextureUpdate() == true );										// Update request should be set.

	drawing->UpdatePenTexture( framework.GetResourceManagerAPI(), pen.get() );
	CHECK( renderingData.Texture != nullptr );
	CHECK( pen->NeedsTextureUpdate() == false );

	pen->SetTextureFile( "textures/Tex2.png" );
	REQUIRE( pen->NeedsTextureUpdate() == true );										// Update request should be set.

	drawing->UpdatePenTexture( framework.GetResourceManagerAPI(), pen.get() );
	CHECK( renderingData.Texture != nullptr );
	CHECK( pen->NeedsTextureUpdate() == false );
}


//====================================================================================//
//			Constant buffers updates	
//====================================================================================//

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.Brush.UpdateConstants", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr brush = std::make_shared< FakeBrush >();

	auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );
	REQUIRE( renderingData.BrushConstants == nullptr );

	drawing->UpdateBrushConstants( framework.GetResourceManagerAPI(), brush.get() );

	CHECK( renderingData.BrushConstants != nullptr );
}

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.Pen.UpdateConstants", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr pen = std::make_shared< FakeBrush >();

	auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );
	REQUIRE( renderingData.BrushConstants == nullptr );

	drawing->UpdatePenConstants( framework.GetResourceManagerAPI(), pen.get() );

	CHECK( renderingData.BrushConstants != nullptr );
}

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.Geometry.UpdateConstants", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();

	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeGeometryPtr geom = std::make_shared< FakeGeometry >( Geometry::ConstantBufferMode::UseShared );

	auto& renderingData = CLASS_TESTER( Drawing )::GetGeometryRenderingData( drawing.get() );
	REQUIRE( renderingData.GeometryConstants == nullptr );

	drawing->UpdateGeometryConstants( framework.GetResourceManagerAPI(), geom.get() );

	CHECK( renderingData.GeometryConstants != nullptr );
}

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.Brush.ChangeConstantsBuffer", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr brush = std::make_shared< FakeBrush >();

	auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );
	REQUIRE( renderingData.BrushConstants == nullptr );

	drawing->UpdateBrushConstants( framework.GetResourceManagerAPI(), brush.get() );

	auto prevBuff = renderingData.BrushConstants;
	CHECK( prevBuff != nullptr );

	brush->ChangeConstsBuffer( "NewBuffer" );
	CHECK( brush->NeedsBufferChange() == true );

	drawing->UpdateBrushConstants( framework.GetResourceManagerAPI(), brush.get() );

	CHECK( prevBuff != renderingData.BrushConstants );
	CHECK( brush->NeedsBufferChange() == false );
}

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.Pen.ChangeConstantsBuffer", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr pen = std::make_shared< FakeBrush >();

	auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );
	REQUIRE( renderingData.BrushConstants == nullptr );

	drawing->UpdatePenConstants( framework.GetResourceManagerAPI(), pen.get() );

	auto prevBuff = renderingData.BrushConstants;
	CHECK( prevBuff != nullptr );

	pen->ChangeConstsBuffer( "NewBuffer" );
	CHECK( pen->NeedsBufferChange() == true );

	drawing->UpdatePenConstants( framework.GetResourceManagerAPI(), pen.get() );

	CHECK( prevBuff != renderingData.BrushConstants );
	CHECK( pen->NeedsBufferChange() == false );
}


//====================================================================================//
//			Geometry update	
//====================================================================================//


// ================================ //
// Test initialization and second update of geometry.
TEST_CASE( "GUI.Rendering.Drawing.Geometry.UpdateGeometry", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeGeometryPtr geom = std::make_shared< FakeGeometry >( Geometry::ConstantBufferMode::Disable );

	auto& renderingData = CLASS_TESTER( Drawing )::GetGeometryRenderingData( drawing.get() );
	REQUIRE( renderingData.VertexBuffer == nullptr );
	REQUIRE( renderingData.IndexBuffer == nullptr );
	REQUIRE( geom->NeedsGeometryUpdate() == true );
	
	// Initialization of geometry.
	drawing->UpdateGeometry( framework.GetResourceManagerAPI(), geom.get() );

	CHECK( renderingData.VertexBuffer != nullptr );
	CHECK( renderingData.IndexBuffer != nullptr );
	CHECK( geom->NeedsGeometryUpdate() == false );

	// Change geometry and check if buffers were updated.
	auto vb = renderingData.VertexBuffer;
	auto ib = renderingData.IndexBuffer;

	geom->ChangeGeometry( "NewGeom" );
	CHECK( geom->NeedsGeometryUpdate() == true );

	drawing->UpdateGeometry( framework.GetResourceManagerAPI(), geom.get() );

	CHECK( renderingData.VertexBuffer != nullptr );
	CHECK( renderingData.IndexBuffer != nullptr );
	CHECK( renderingData.VertexBuffer != vb );			// New buffers should be generated.
	CHECK( renderingData.IndexBuffer != ib );			// New buffers should be generated.
	CHECK( geom->NeedsGeometryUpdate() == false );
}

// ================================ //
// If new geometry has the same name as previously used, it should use this existing geometry.
TEST_CASE( "GUI.Rendering.Drawing.Geometry.UpdateGeometry.UseExisting", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeGeometryPtr geom = std::make_shared< FakeGeometry >( Geometry::ConstantBufferMode::Disable );

	auto& renderingData = CLASS_TESTER( Drawing )::GetGeometryRenderingData( drawing.get() );
	
	geom->ChangeGeometry( "Geometry1" );
	drawing->UpdateGeometry( framework.GetResourceManagerAPI(), geom.get() );

	auto vb = renderingData.VertexBuffer;
	auto ib = renderingData.IndexBuffer;

	geom->ChangeGeometry( "Geometry2" );
	drawing->UpdateGeometry( framework.GetResourceManagerAPI(), geom.get() );

	// Use Geometry1 again.
	geom->ChangeGeometry( "Geometry1" );
	drawing->UpdateGeometry( framework.GetResourceManagerAPI(), geom.get() );

	CHECK( renderingData.VertexBuffer == vb );
	CHECK( renderingData.IndexBuffer == ib );
}

