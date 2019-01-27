#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/DX11/TestFramework.DX11.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"
#include "swGUI/TestFramework/Utils/Mocks/Rendering/FakeDrawing.h"


// Include Brushes
#include "swGUI/Core/Media/Brushes/SolidColorBrush.h"
#include "swGUI/Core/Media/Brushes/LinearGradientBrush.h"




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

