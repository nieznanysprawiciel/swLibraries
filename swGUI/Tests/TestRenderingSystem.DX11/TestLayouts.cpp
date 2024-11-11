#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/DX11/TestFramework.DX11.h"

#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"
#include "swGUI/Core/Media/Geometry/Layouts/VertexShape2D.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"
#include "swGUI/TestFramework/Utils/Mocks/Rendering/FakeDrawing.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"



using namespace sw;
using namespace sw::gui;



// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Drawing.Layout.VertexShape2D", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework* framework = GetGlobalTestFramework();
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();

	REQUIRE_IS_VALID( drawing->CreateAndSetLayout( framework->GetResourceManagerAPI(), framework->GetRenderingSystem()->GetShaderProvider(), nullptr ) );

	auto& renderingData = CLASS_TESTER( Drawing )::GetGeometryRenderingData( drawing.get() );
	CHECK( renderingData.Layout != nullptr );
}

// ================================ //
//
TEST_CASE( "GUI.Rendering.DX11.Drawing.Layout.VertexText2D", "[GUISystem][RenderingSystem][Drawing]" )
{
    TestFramework* framework = GetGlobalTestFramework();
    FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();

    REQUIRE_IS_VALID( drawing->CreateAndSetLayoutForVertexType< VertexText2D >(
        framework->GetResourceManagerAPI(), framework->GetRenderingSystem()->GetShaderProvider(), nullptr ) );

    auto& renderingData = CLASS_TESTER( Drawing )::GetGeometryRenderingData( drawing.get() );
    CHECK( renderingData.Layout != nullptr );
}
