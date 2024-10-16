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
	ShaderProvider sp( framework.GetResourceManagerAPI(), framework.GetPathsManager() );

	auto shader = sp.GeneratePS( "shaders/FakeTemplate.ps", "shaders/FakeBrush.ps" );
	CHECK( shader.Ptr() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GUI.ShaderProvider.GenerateVS", "[GUISystem][RenderingSystem]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	ShaderProvider sp( framework.GetResourceManagerAPI(), framework.GetPathsManager() );

	auto shader = sp.GenerateVS( "shaders/FakeTemplate.vs", "shaders/FakeGeom.vs" );
	CHECK( shader.Ptr() != nullptr );
}

// ================================ //
// ShaderProvider shouldn't generate the same shader twice.
TEST_CASE( "GUI.ShaderProvider.GenerateVS.SecondTime", "[GUISystem][RenderingSystem]" )
{
    TestFramework framework( 0, nullptr );	framework.Init();
    ShaderProvider sp( framework.GetResourceManagerAPI(), framework.GetPathsManager() );

    auto shader1 = sp.GenerateVS( "shaders/FakeTemplate.vs", "shaders/FakeGeom.vs" );
    auto shader2 = sp.GenerateVS( "shaders/FakeTemplate.vs", "shaders/FakeGeom.vs" );
    CHECK( shader1 == shader2 );
}

// ================================ //
// ShaderProvider shouldn't generate the same shader twice.
TEST_CASE( "GUI.ShaderProvider.GeneratePS.SecondTime", "[GUISystem][RenderingSystem]" )
{
    TestFramework framework( 0, nullptr );	framework.Init();
    ShaderProvider sp( framework.GetResourceManagerAPI(), framework.GetPathsManager() );

    auto shader1 = sp.GeneratePS( "shaders/FakeTemplate.ps", "shaders/FakeGeom.ps" );
    auto shader2 = sp.GeneratePS( "shaders/FakeTemplate.ps", "shaders/FakeGeom.ps" );
    CHECK( shader1 == shader2 );
}


