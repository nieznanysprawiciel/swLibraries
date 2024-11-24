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
    REQUIRE_IS_VALID( shader );
    CHECK( shader.Get().Ptr() != nullptr );
}

// ================================ //
// 
TEST_CASE( "GUI.ShaderProvider.GenerateVS", "[GUISystem][RenderingSystem]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	ShaderProvider sp( framework.GetResourceManagerAPI(), framework.GetPathsManager() );

	auto shader = sp.GenerateVS( "shaders/FakeTemplate.vs", "shaders/FakeGeom.vs" );
    REQUIRE_IS_VALID( shader );
    CHECK( shader.Get().Ptr() != nullptr );
}

// ================================ //
// ShaderProvider shouldn't generate the same shader twice.
TEST_CASE( "GUI.ShaderProvider.GenerateVS.SecondTime", "[GUISystem][RenderingSystem]" )
{
    TestFramework framework( 0, nullptr );	framework.Init();
    ShaderProvider sp( framework.GetResourceManagerAPI(), framework.GetPathsManager() );

    auto shader1 = sp.GenerateVS( "shaders/FakeTemplate.vs", "shaders/FakeGeom.vs" );
    auto shader2 = sp.GenerateVS( "shaders/FakeTemplate.vs", "shaders/FakeGeom.vs" );
    REQUIRE_IS_VALID( shader1 );
    REQUIRE_IS_VALID( shader2 );
    CHECK( shader1.Get() == shader2.Get() );
}

// ================================ //
//
TEST_CASE( "GUI.ShaderProvider.GeneratePS.ErrorHandling.NoCode", "[GUISystem][RenderingSystem]" )
{
    TestFramework framework( 0, nullptr );
    framework.Init();
    ShaderProvider sp( framework.GetResourceManagerAPI(), framework.GetPathsManager() );

    auto shader = sp.GeneratePS( "shaders/FakeTemplate-NotExisting.ps", "shaders/FakeBrush-NotExisting.ps" );
    REQUIRE_INVALID( shader );
}
