#include "swGUI/Tests/TestGUISystem/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestHostWindow.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/TestFramework/TestFramework.h"
#include "swGUI/Native/MockNativeGUI/MockGUI.h"

using namespace sw;
using namespace sw::gui;



// ================================ //
// Run single frame to check if HostWindow was initialized properly.
TEST_CASE( "GUI.Windows.HostWindow.RunSingleFrame", "[GUISystem][HostWindow][Focus]" )
{
    // Initialize framework.
    TestFramework framework( 0, nullptr );	framework.Init();
    MockGUI* mockNativeGUI = static_cast< MockGUI* >( framework.GetNativeGUI() );

    // To check if rendering code doesn't fail, we need to set focus to our window.
    HostWindow* window = framework.CreateNativeHostWindow( 400, 400, "TestWindow" ).Get();
    mockNativeGUI->SendChangeFocus( window->GetNativeWindow(), true );

    framework.MainLoopCore();
}

