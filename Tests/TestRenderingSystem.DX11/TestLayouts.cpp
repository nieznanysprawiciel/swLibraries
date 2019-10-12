#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/DX11/TestFramework.DX11.h"

#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"
#include "swGUI/TestFramework/Utils/Mocks/Rendering/FakeDrawing.h"



using namespace sw;
using namespace sw::gui;



// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Drawing.Layout.VertexShape2D", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework* framework = GetGlobalTestFramework();
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();

	REQUIRE( drawing->CreateAndSetLayout( framework->GetResourceManagerAPI(), framework->GetRenderingSystem()->GetShaderProvider(), nullptr ) == true );

	auto& renderingData = CLASS_TESTER( Drawing )::GetGeometryRenderingData( drawing.get() );
	CHECK( renderingData.Layout != nullptr );
}


