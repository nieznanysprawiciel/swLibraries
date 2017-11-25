/**
@file TestFramework.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/TestFramework/stdafx.h"


#include "TestFramework.h"
#include "swInputLibrary/InputCore/Debugging/DebugInput.h"
#include "swGUI/Native/MockNativeGUI/MockGUI.h"



namespace sw {
namespace gui
{


// ================================ //
//
TestFramework::TestFramework		( int argc, char** argv )
	:	GUISystem( argc, argv, new MockGUI(), SetTestMode::True )
{}


// ================================ //
//
bool					TestFramework::Initialize		()
{
	return DefaultInitWithoutWindow();
}

// ================================ //
//
input::EventCapturePtr	TestFramework::GetEventCapturer	( HostWindow* window )
{
	if( window )
	{
		auto input = window->GetInput();
		if( input )
		{
			input::DebugInput* debugInput = static_cast<input::DebugInput*>( input );
			return debugInput->GetEventCapture();
		}
	}

	return nullptr;
}

// ================================ //
//
input::IInput*			TestFramework::GetInput			( HostWindow* window )
{
	if( window )
		return window->GetInput();
	return nullptr;
}

// ================================ //
//
bool					TestFramework::TesterMainStep	()
{
	return !MainLoopCore();
}


}	// gui
}	// sw


