#include "swGUI/Tests/TestGUISystem/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestHostWindowFocus.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/TestFramework/TestFramework.h"
#include "swGUI/Native/MockNativeGUI/MockGUI.h"

using namespace sw;
using namespace sw::gui;


// ================================ //
// Replicates situation, when operating system changes window focus.
// This test checks case with single window.
TEST_CASE( "GUI.Windows.HostWindow.SingleWindowFocus", "[GUISystem][HostWindow][Focus]" )
{
	// Initialize framework.
	TestFramework framework( 0, nullptr );	framework.Init();
	MockGUI* mockNativeGUI = static_cast< MockGUI* >( framework.GetNativeGUI() );

	HostWindow* window = framework.CreateNativeHostWindow( 400, 400, "TestWindow" ).Get();
	
	// IF we created window after default initialization, no one has focus.
	REQUIRE( framework.GetFocusWindow() == nullptr );

	mockNativeGUI->SendChangeFocus( window->GetNativeWindow(), true );
	CHECK( framework.GetFocusWindow() == window );

	mockNativeGUI->SendChangeFocus( window->GetNativeWindow(), false );
	REQUIRE( framework.GetFocusWindow() == nullptr );
}

// ================================ //
// Replicates situation, when operating system changes window focus.
// This test checks focus behavior of two windows present in system.
// Test written for properly sent native events.
TEST_CASE( "GUI.Windows.HostWindow.TwoWindowsFocus.ProperNativeEvents", "[GUISystem][HostWindow][Focus]" )
{
	// Initialize framework.
	TestFramework framework( 0, nullptr );	framework.Init();
	MockGUI* mockNativeGUI = static_cast< MockGUI* >( framework.GetNativeGUI() );

	HostWindow* window1 = framework.CreateNativeHostWindow( 400, 400, "TestWindow1" ).Get();
	HostWindow* window2 = framework.CreateNativeHostWindow( 400, 400, "TestWindow2" ).Get();
	
	// IF we created window after default initialization, no one has focus.
	REQUIRE( framework.GetFocusWindow() == nullptr );

	// Simple test. Set focus to first window.
	mockNativeGUI->SendChangeFocus( window1->GetNativeWindow(), true );
	REQUIRE( framework.GetFocusWindow() == window1 );

	// Proper native events: First get focus from window1 and then set focus to window2.
	mockNativeGUI->SendChangeFocus( window1->GetNativeWindow(), false );
	mockNativeGUI->SendChangeFocus( window2->GetNativeWindow(), true );
	REQUIRE( framework.GetFocusWindow() == window2 );

	// Window2 loses focus and none of our windows gets it.
	mockNativeGUI->SendChangeFocus( window2->GetNativeWindow(), false );
	REQUIRE( framework.GetFocusWindow() == nullptr );
}


// ================================ //
// Replicates situation, when operating system changes window focus.
// This test checks focus behavior of two windows present in system.
// Native systems forgets to send lost focus message to window.
TEST_CASE( "GUI.Windows.HostWindow.TwoWindowsFocus.NoLostFocusEvent", "[GUISystem][HostWindow][Focus]" )
{
	// Initialize framework.
	TestFramework framework( 0, nullptr );	framework.Init();
	MockGUI* mockNativeGUI = static_cast<MockGUI*>( framework.GetNativeGUI() );

	HostWindow* window1 = framework.CreateNativeHostWindow( 400, 400, "TestWindow1" ).Get();
	HostWindow* window2 = framework.CreateNativeHostWindow( 400, 400, "TestWindow2" ).Get();

	// IF we created window after default initialization, no one has focus.
	REQUIRE( framework.GetFocusWindow() == nullptr );

	// Simple test. Set focus to first window.
	mockNativeGUI->SendChangeFocus( window1->GetNativeWindow(), true );
	REQUIRE( framework.GetFocusWindow() == window1 );

	// Send only set focus message to window2.
	mockNativeGUI->SendChangeFocus( window2->GetNativeWindow(), true );
	REQUIRE( framework.GetFocusWindow() == window2 );
}

// ================================ //
// Replicates situation, when operating system changes window focus.
// In this case system sends set focus message to window which already has focus.
TEST_CASE( "GUI.Windows.HostWindow.TwoWindowsFocus.SetFocusForWindowWithFocus", "[GUISystem][HostWindow][Focus]" )
{
	// Initialize framework.
	TestFramework framework( 0, nullptr );	framework.Init();
	MockGUI* mockNativeGUI = static_cast<MockGUI*>( framework.GetNativeGUI() );

	HostWindow* window1 = framework.CreateNativeHostWindow( 400, 400, "TestWindow1" ).Get();
	HostWindow* window2 = framework.CreateNativeHostWindow( 400, 400, "TestWindow2" ).Get();

	// IF we created window after default initialization, no one has focus.
	REQUIRE( framework.GetFocusWindow() == nullptr );

	// Set focus.
	mockNativeGUI->SendChangeFocus( window1->GetNativeWindow(), true );
	REQUIRE( framework.GetFocusWindow() == window1 );

	// Set focus for the second time.
	mockNativeGUI->SendChangeFocus( window1->GetNativeWindow(), true );
	REQUIRE( framework.GetFocusWindow() == window1 );
}

// ================================ //
// Replicates situation, when operating system changes window focus.
// In this case system sends lost focus message to window which didn't have focus.
TEST_CASE( "GUI.Windows.HostWindow.TwoWindowsFocus.LostFocusForWindowWithoutFocus", "[GUISystem][HostWindow][Focus]" )
{
	// Initialize framework.
	TestFramework framework( 0, nullptr );	framework.Init();
	MockGUI* mockNativeGUI = static_cast<MockGUI*>( framework.GetNativeGUI() );

	HostWindow* window1 = framework.CreateNativeHostWindow( 400, 400, "TestWindow1" ).Get();
	HostWindow* window2 = framework.CreateNativeHostWindow( 400, 400, "TestWindow2" ).Get();

	// IF we created window after default initialization, no one has focus.
	REQUIRE( framework.GetFocusWindow() == nullptr );

	// Send lost focus message.
	mockNativeGUI->SendChangeFocus( window1->GetNativeWindow(), false );
	REQUIRE( framework.GetFocusWindow() == nullptr );
}
