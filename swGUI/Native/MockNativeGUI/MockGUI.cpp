/**
@file MockGUI.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "MockGUI.h"
#include "MockWindow.h"

#include "swInputLibrary/InputCore/Debugging/DebugInput.h"



namespace sw {
namespace gui
{



// ================================ //
//
MockGUI::MockGUI()
{}


/**@brief Creates WinAPIGUI object.*/
MockGUI*		MockGUI::Create				()
{
	return new MockGUI();
}

// ================================ //
//
void			MockGUI::SendChangeFocus	( INativeWindow* nativeWindow, bool change )
{
	m_initData.FocusChanged( nativeWindow, change );
}

// ================================ //
//
void			MockGUI::EndApplication		()
{
	/// @todo How to close application in MockGUI.
	exit( 0 );
}

// ================================ //
//
INativeOS*		MockGUI::GetOS				()
{
	return &m_os;
}



//====================================================================================//
//			Window creation	
//====================================================================================//



// ================================ //
///
sw::input::IInput*		MockGUI::UseNativeInput		( INativeWindow* nativeWindow )
{
	input::InputInitInfo info;
	info.AppInstance = nullptr;
	info.WndHandle = nullptr;

	return UseNativeInput( nativeWindow, info );
}

// ================================ //
//
sw::input::IInput*		MockGUI::UseNativeInput		( INativeWindow* nativeWindow, input::InputInitInfo& initInfo )
{
	input::IInput* input = new input::DebugInput();
	
	if( input->Init( initInfo ) )
		return input;

	return nullptr;
}



/**@copydoc INativeGUI::CreateWindow*/
INativeWindow*	MockGUI::CreateWindow		( NativeWindowDescriptor& descriptor )
{
	MockWindow* newWindow = MockWindow::CreateWindowInstance( descriptor );
	return newWindow;
}


/**@copydoc INativeGUI::Init*/
ReturnResult    MockGUI::Init				( const NativeGUIInitData& initData )
{
	assert( !initData.FocusChanged.empty() );

	m_initData = initData;
	return Result::Success;
}



//====================================================================================//
//			Window Message handler
//====================================================================================//


/**@copydoc INativeGUI::MainLoop*/
bool		MockGUI::MainLoop                 ( bool blockingMode )
{
	return false;
}



}	// gui
}	// sw
