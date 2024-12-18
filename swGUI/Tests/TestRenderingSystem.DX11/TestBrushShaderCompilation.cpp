#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/DX11/TestFramework.DX11.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"
#include "swGUI/TestFramework/Utils/Mocks/Rendering/FakeDrawing.h"


// Include Brushes
#include "swGUI/Core/Media/Brushes/SolidColorBrush.h"
#include "swGUI/Core/Media/Brushes/LinearGradientBrush.h"
#include "swGUI/Core/Media/Brushes/AngleGradientBrush.h"
#include "swGUI/Core/Media/Brushes/ImageBrush.h"




using namespace sw;
using namespace sw::gui;



// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Brush.ShaderCompilation.SolidColorBrush", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework* framework = GetGlobalTestFramework();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	SolidColorBrushPtr brush = std::make_shared< SolidColorBrush >();

	drawing->UpdateBrushShader( framework->GetRenderingSystem()->GetShaderProvider(), brush.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

	INFO( "[SolidColorBrush] Brush Shader compilation failed." );
	CHECK( renderingData.PixelShader != nullptr );
}

// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Brush.ShaderCompilation.SolidColorBrush.Opacity", "[GUISystem][RenderingSystem][Drawing]" )
{
    TestFramework* framework = GetGlobalTestFramework();

    FakeDrawingPtr     drawing = std::make_shared< FakeDrawing >();
    SolidColorBrushPtr brush = std::make_shared< SolidColorBrush >();
    ShaderProvider*    sp = framework->GetRenderingSystem()->GetShaderProvider();

    drawing->UpdateBrushShader( sp, brush.get(), sp->GetBasicPSTemplate() );

    auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

    INFO( "[SolidColorBrush] Brush Shader compilation failed." );
    CHECK( renderingData.PixelShader != nullptr );
}

// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Brush.ShaderCompilation.LinearGradientBrush", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework* framework = GetGlobalTestFramework();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	LinearGradientBrushPtr brush = std::make_shared< LinearGradientBrush >();

	drawing->UpdateBrushShader( framework->GetRenderingSystem()->GetShaderProvider(), brush.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

	INFO( "[LinearGradientBrush] Brush Shader compilation failed." );
	CHECK( renderingData.PixelShader != nullptr );
}

// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Brush.ShaderCompilation.LinearGradientBrush.Opacity", "[GUISystem][RenderingSystem][Drawing]" )
{
    TestFramework* framework = GetGlobalTestFramework();

    FakeDrawingPtr         drawing = std::make_shared< FakeDrawing >();
    LinearGradientBrushPtr brush = std::make_shared< LinearGradientBrush >();
    ShaderProvider*        sp = framework->GetRenderingSystem()->GetShaderProvider();

    drawing->UpdateBrushShader( sp, brush.get(), sp->GetBasicPSTemplate() );

    auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

    INFO( "[LinearGradientBrush] Brush Shader compilation failed." );
    CHECK( renderingData.PixelShader != nullptr );
}

// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Brush.ShaderCompilation.AngleGradientBrush", "[GUISystem][RenderingSystem][Drawing]" )
{
    TestFramework* framework = GetGlobalTestFramework();

    FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
    AngleGradientBrushPtr brush = std::make_shared< AngleGradientBrush >();

    drawing->UpdateBrushShader( framework->GetRenderingSystem()->GetShaderProvider(), brush.get() );

    auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

    INFO( "[AngleGradientBrush] Brush Shader compilation failed." );
    CHECK( renderingData.PixelShader != nullptr );
}

// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Brush.ShaderCompilation.AngleGradientBrush.Opacity", "[GUISystem][RenderingSystem][Drawing]" )
{
    TestFramework* framework = GetGlobalTestFramework();

    FakeDrawingPtr        drawing = std::make_shared< FakeDrawing >();
    AngleGradientBrushPtr brush = std::make_shared< AngleGradientBrush >();
    ShaderProvider*       sp = framework->GetRenderingSystem()->GetShaderProvider();

    drawing->UpdateBrushShader( sp, brush.get(), sp->GetBasicPSTemplate() );

    auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

    INFO( "[AngleGradientBrush] Brush Shader compilation failed." );
    CHECK( renderingData.PixelShader != nullptr );
}

// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Brush.ShaderCompilation.ImageBrush", "[GUISystem][RenderingSystem][Drawing]" )
{
    TestFramework* framework = GetGlobalTestFramework();

    FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
    ImageBrushPtr brush = std::make_shared< ImageBrush >();

    drawing->UpdateBrushShader( framework->GetRenderingSystem()->GetShaderProvider(), brush.get() );

    auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

    INFO( "[ImageBrush] Brush Shader compilation failed." );
    CHECK( renderingData.PixelShader != nullptr );
}

// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Brush.ShaderCompilation.ImageBrush.Opacity", "[GUISystem][RenderingSystem][Drawing]" )
{
    TestFramework* framework = GetGlobalTestFramework();

    FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
    ImageBrushPtr  brush = std::make_shared< ImageBrush >();
    ShaderProvider* sp = framework->GetRenderingSystem()->GetShaderProvider();

    drawing->UpdateBrushShader( sp, brush.get(), sp->GetBasicPSTemplate() );

    auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

    INFO( "[ImageBrush] Brush Shader compilation failed." );
    CHECK( renderingData.PixelShader != nullptr );
}
