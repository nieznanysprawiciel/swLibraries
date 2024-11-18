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
    m_guiConfig.DebugGraphics = true;

    ReturnResult result = Success::True;
	
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
			input::DebugInput* debugInput = static_cast< input::DebugInput* >( input );
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
void                    TestFramework::Clean            ()
{
    for( auto window : m_windows )
    {
        delete window;
    }

    m_windows.clear();
    m_focusedWindow = nullptr;

    m_resourceManager->FreeUnusedAssets();
}

// ================================ //
//
ReturnResult			TestFramework::OverridePaths	()
{
	auto coreGUISourcePath = impl::FindCoreGUISourcePath( m_nativeGUI->GetOS()->GetApplicationDir() );

	ErrorsCollector results;

	results.Add( m_pathsManager->OverrideAlias( "$(CoreGUI-Shader-Dir)", coreGUISourcePath / "Core/Shaders/hlsl" ) );
    results.Add( m_pathsManager->OverrideAlias( "$(SystemFonts)", coreGUISourcePath / "TestResources/fonts" ) );

	return results;
}


namespace impl
{

// ================================ //
// CoreGUI path should have swGUI in path. We look for this string in binaryPath.
fs::Path				FindCoreGUISourcePath			( const fs::Path& binaryPath )
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

	return fs::Path();
}

}	// impl

}	// gui
}	// sw


