#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

#include "swGUI/Core/System/Rendering/Shading/ShaderProvider.h"

using namespace sw;
using namespace sw::gui;


// ================================ //
// Tests if PathsManager has registered expected paths after initialization.
TEST_CASE( "GUI.PathsManager.ShaderProvider.Requirements", "[GUISystem][RenderingSystem]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	auto pathsManager = framework.GetPathsManager();

	CHECK( pathsManager->FindAlias( "$(TMP)" ).IsValid() );
	CHECK( pathsManager->FindAlias( "$(CoreGUI-Shader-Dir)" ).IsValid() );
}



// ================================ //
// 
TEST_CASE( "GUI.ShaderProvider.GeneratePS", "[GUISystem][RenderingSystem]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	ShaderProvider sp( framework.GetResourceManager(), framework.GetPathsManager() );

	auto shader = sp.GeneratePS( "WorkingDir-RenderingSystem/shaders/FakeTemplate.ps", "WorkingDir-RenderingSystem/shaders/FakeBrush.ps" );
	CHECK( shader.Ptr() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GUI.ShaderProvider.GenerateVS", "[GUISystem][RenderingSystem]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	ShaderProvider sp( framework.GetResourceManager(), framework.GetPathsManager() );

	auto shader = sp.GenerateVS( "WorkingDir-RenderingSystem/shaders/FakeTemplate.vs", "WorkingDir-RenderingSystem/shaders/FakeGeom.vs" );
	CHECK( shader.Ptr() != nullptr );
}


