#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/DX11/TestFramework.DX11.h"
#include "swGUI/TestFramework/Testers/Rendering/RenderingSystemTester.h"


using namespace sw;
using namespace sw::gui;



// ================================ //
//
TEST_CASE( "GUI.RenderingSystem.DX11.Initialization", "[GUISystem][RenderingSystem]" )
{
	TestFramework* framework = GetGlobalTestFramework();
	auto renderingSystem = framework->GetRenderingSystem();

	CHECK( renderingSystem->GetRenderer() != nullptr );
	CHECK( renderingSystem->GetShaderProvider() != nullptr );

	CHECK( CLASS_TESTER( RenderingSystem )::GetRasterizerState( renderingSystem ) != nullptr );
	CHECK( CLASS_TESTER( RenderingSystem )::GetDepthStencilState( renderingSystem ) != nullptr );
	CHECK( CLASS_TESTER( RenderingSystem )::GetTransparentBlendingState( renderingSystem ) != nullptr );
	CHECK( CLASS_TESTER( RenderingSystem )::GetOpaqueBlendingState( renderingSystem ) != nullptr );
	CHECK( CLASS_TESTER( RenderingSystem )::GetRenderingSystemConsts( renderingSystem ) != nullptr );
}


