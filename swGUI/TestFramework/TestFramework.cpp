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
ReturnResult			TestFramework::Initialize		()
{
    ReturnResult result = Result::Success;
	
	result = result && DefaultInitWithoutWindow();
	result = result && OverridePaths();

	return result;
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

// ================================ //
//
ReturnResult			TestFramework::OverridePaths	()
{
	auto coreGUISourcePath = impl::FindCoreGUISourcePath( m_nativeGUI->GetOS()->GetApplicationDir() );

	return m_pathsManager->OverrideAlias( "$(CoreGUI-Shader-Dir)", coreGUISourcePath / "Core/Shaders/hlsl" );
}


namespace impl
{

// ================================ //
// CoreGUI path should have swGUI in path. We look for this string in binaryPath.
filesystem::Path		FindCoreGUISourcePath			( const filesystem::Path& binaryPath )
{
	auto path = binaryPath;
	auto fileName = path.GetFileName();

	while( !fileName.empty() )
	{
		if( fileName == "swGUI" )
		{
			return path;
		}

		path = path.GetParent();
		fileName = path.GetFileName();
	}

	return filesystem::Path();
}

}	// impl

}	// gui
}	// sw


