#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"
#include "swGUI/TestFramework/Utils/Mocks/Rendering/FakeDrawing.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


using namespace sw;
using namespace sw::gui;



// ================================ //
//
TEST_CASE( "GUI.Rendering.Drawing.Layout.VertexShape2D", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();

	REQUIRE_IS_VALID( drawing->CreateAndSetLayout( framework.GetResourceManagerAPI(), framework.GetRenderingSystem()->GetShaderProvider(), nullptr ) );

	auto& renderingData = CLASS_TESTER( Drawing )::GetGeometryRenderingData( drawing.get() );
	CHECK( renderingData.Layout != nullptr );
}


