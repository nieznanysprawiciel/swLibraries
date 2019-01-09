#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"
#include "swGUI/TestFramework/Testers/Rendering/RenderingSystemTester.h"


using namespace sw;
using namespace sw::gui;



// ================================ //
//
TEST_CASE( "GUI.RenderingSystem.Initialization", "[GUISystem][RenderingSystem]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	auto renderingSystem = framework.GetRenderingSystem();

	CHECK( renderingSystem->GetRenderer() != nullptr );
	CHECK( renderingSystem->GetShaderProvider() != nullptr );

	CHECK( CLASS_TESTER( RenderingSystem )::GetRasterizerState( renderingSystem ) != nullptr );
	CHECK( CLASS_TESTER( RenderingSystem )::GetDepthStencilState( renderingSystem ) != nullptr );
	CHECK( CLASS_TESTER( RenderingSystem )::GetTransparentBlendingState( renderingSystem ) != nullptr );
	CHECK( CLASS_TESTER( RenderingSystem )::GetOpaqueBlendingState( renderingSystem ) != nullptr );
	CHECK( CLASS_TESTER( RenderingSystem )::GetRenderingSystemConsts( renderingSystem ) != nullptr );
	CHECK( CLASS_TESTER( RenderingSystem )::GetVisualConsts( renderingSystem ) != nullptr );
}


