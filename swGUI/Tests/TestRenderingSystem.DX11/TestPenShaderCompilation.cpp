#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/DX11/TestFramework.DX11.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"
#include "swGUI/TestFramework/Utils/Mocks/Rendering/FakeDrawing.h"


// Include Brushes
#include "swGUI/Core/Media/Brushes/SolidColorBrush.h"
#include "swGUI/Core/Media/Brushes/LinearGradientBrush.h"
#include "swGUI/Core/Media/Brushes/AngleGradientBrush.h"
#include "swGUI/Core/Media/Brushes/ImageBrush.h"




//====================================================================================//
// Tests if Pen shaders compile properly. Current implementation of shaders templates
// for Pen is the same as for Brush, so these tests have the same effect.
// In future we can change this behavior.
//====================================================================================//


using namespace sw;
using namespace sw::gui;



// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Pen.ShaderCompilation.SolidColorBrush", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework* framework = GetGlobalTestFramework();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	SolidColorBrushPtr brush = std::make_shared< SolidColorBrush >();

	drawing->UpdatePenShader( framework->GetRenderingSystem()->GetShaderProvider(), brush.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );

	INFO( "[SolidColorBrush] Pen Shader compilation failed." );
	CHECK( renderingData.PixelShader != nullptr );
}

// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Pen.ShaderCompilation.LinearGradientBrush", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework* framework = GetGlobalTestFramework();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	LinearGradientBrushPtr brush = std::make_shared< LinearGradientBrush >();

	drawing->UpdatePenShader( framework->GetRenderingSystem()->GetShaderProvider(), brush.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );

	INFO( "[LinearGradientBrush] Pen Shader compilation failed." );
	CHECK( renderingData.PixelShader != nullptr );
}

// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Pen.ShaderCompilation.AngleGradientBrush", "[GUISystem][RenderingSystem][Drawing]" )
{
    TestFramework* framework = GetGlobalTestFramework();

    FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
    AngleGradientBrushPtr brush = std::make_shared< AngleGradientBrush >();

    drawing->UpdatePenShader( framework->GetRenderingSystem()->GetShaderProvider(), brush.get() );

    auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );

    INFO( "[AngleGradientBrush] Pen Shader compilation failed." );
    CHECK( renderingData.PixelShader != nullptr );
}

// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Pen.ShaderCompilation.ImageBrush", "[GUISystem][RenderingSystem][Drawing]" )
{
    TestFramework* framework = GetGlobalTestFramework();

    FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
    ImageBrushPtr brush = std::make_shared< ImageBrush >();

    drawing->UpdatePenShader( framework->GetRenderingSystem()->GetShaderProvider(), brush.get() );

    auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );

    INFO( "[ImageBrush] Pen Shader compilation failed." );
    CHECK( renderingData.PixelShader != nullptr );
}
