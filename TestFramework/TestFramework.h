#pragma once
/**
@file TestFramework.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/System/GUISystem.h"
#include "swInputLibrary/InputCore/Debugging/EventCapture.h"



/**@defgroup GUITestFramework TestFramework
@brief Framework for testing GUI, controls and probably in future applications written swGUI too.
@ingroup SWGUI

@section WritingTests Writing tests

Tests use special @ref sw::gui::TestFramework class which derives from @ref sw::gui::GUISystem and implements all functionalities
with minimal context and light dependencies. You can use this class directly or derive your own class normally
as you would do in application.

TestFramework gives you posibility to:
- Test events interactions by adding events from code (using @ref input::EventCapture class)
- Load bunch of events with @ref input::EventCapture class (posible in future)
- Test application state after single main loop step



@subsection LinkingTestProject Linking libraries

To write test you must link TestFramework.lib which links by itself:
- MockNativeGUI
- CoreGUI
- InputCore
- MockAPI (graphic API)

TestFramework doesn't create window nor rendering api - it uses fake subtitutes to minimize testing time.

Moreover you must link other things necessary to make GUI work like:
- CommonBase
- Reflection
- SerialzierXML
- Serialization

All these things can change in future versions.

@subsection Usage Usage examples

This code uses catch to check test condition but you can use your own testing framework.

@code

TEST_CASE( "KeyUp/KeyDown event" )
{
	// Initialize framework.
	TestFramework framework( 0, nullptr );		// Provide main function arguments.
	framework.Init();

	// Create main window (fake window) and get input::EventCapture. 
	HostWindow* window = framework.CreateNativeHostWindow( 400, 400, "TestWindow" );
	input::EventCapture* eventCapturer = framework.GetEventCapturer();

	// Set focus to window.
	framework.OnFocusChanged( window->GetNativeWindow(), true );

	// Add event handlers to tested events.
	window->KeyUp() += EventDelegate< KeyEventArgs >( &KeyEventReceived );
	window->KeyDown() += EventDelegate< KeyEventArgs >( &KeyEventReceived );

	window->PreviewKeyUp() += EventDelegate< KeyEventArgs >( &KeyEventReceived );
	window->PreviewKeyDown() += EventDelegate< KeyEventArgs >( &KeyEventReceived );

	//....
}

@endcode

@see DebugInput
*/



namespace sw {
namespace gui
{


/**@brief Class used as application entry point in tests.

TestFramework initializes graphic API as MockAPI, 

@ingroup GUITestFramework*/
class TestFramework : public GUISystem
{
private:
protected:
public:
	explicit		TestFramework		( int argc, char** argv );
	virtual			~TestFramework		() = default;


	virtual	bool				Initialize			();


public:

	///@name Test writer API
	///@{

	/**@brief Returns event capturer which can emulate events.*/
	input::EventCapturePtr		GetEventCapturer	( HostWindow* window );

	/**@brief Returns input object for window.*/
	input::IInput*				GetInput			( HostWindow* window );

	/**@brief Returns native gui manager.*/
	INativeGUI*					GetNativeGUI		() { return m_nativeGUI; }

	/**@brief Get window that has currently focus. Can return nullptr.*/
	HostWindow*					GetFocusWindow		() { return m_focusedWindow; }

	/**@brief Calls main loop but returns after making full step.*/
	bool						TesterMainStep		();

	using GUISystem::CreateNativeHostWindow;
	///@}

private:

	// Inherited via GUISystem
	virtual bool	OnInitialized			() override { return true; };
	virtual void	OnClosing				() override {};
	virtual void	OnIdle					( const FrameTime& frameTime ) override {};
};


}	// gui
}	// sw


