#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/DX11/TestFramework.DX11.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"
#include "swGUI/TestFramework/Utils/Mocks/Rendering/FakeDrawing.h"
#include "swGUI/TestFramework/Utils/Mocks/Media/FakeGeometry.h"





using namespace sw;
using namespace sw::gui;



// ================================ //
// Test default shader for forwarding attributes.
TEST_CASE( "GUI.Rendering.DX11.Geometry.ShaderCompilation.ForwardAttributes", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework* framework = GetGlobalTestFramework();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeGeometryPtr geom = std::make_shared< FakeGeometry >( Geometry::ConstantBufferMode::Disable );
	geom->SetShaderFunction( "$(CoreGUI-Shader-Dir)/Geometry/ForwardAttributes.vsh" );

	drawing->UpdateVertexShader( framework->GetRenderingSystem()->GetShaderProvider(), geom.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetGeometryRenderingData( drawing.get() );

	INFO( "[Default ForwardAttributes.vsh] Shader compilation failed." );
	CHECK( renderingData.VertexShader != nullptr );
}

