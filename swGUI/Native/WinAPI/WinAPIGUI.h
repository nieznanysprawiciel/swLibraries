#pragma once
/**
@file WinAPIGUI.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swGUI/Native/INativeGUI.h"
#include "WindowsOS.h"

#include <Windows.h>
#undef CreateWindow
#undef XBUTTON1
#undef XBUTTON2





namespace sw {
namespace input
{
class WinApiInputProxy;

}}	// sw::input




/**@defgroup Win32APINativeGUI WinAPI native GUI
@brief Native GUI basedon windows API.
@ingroup NativeGUI*/


namespace sw {
namespace gui
{


/**@brief 
@ingroup Win32APINativeGUI*/
class WinAPIGUI : public INativeGUI
{
private:

	NativeGUIInitData				m_initData;
	WindowsOS						m_os;

protected:
public:
	explicit			WinAPIGUI	();
	virtual				~WinAPIGUI	() = default;


	virtual bool				MainLoop		( bool blockingMode )											override;
	virtual ReturnResult    	Init			( const NativeGUIInitData& initData )							override;
	virtual sw::input::IInput*	UseNativeInput	( INativeWindow* nativeWindow )									override;
	virtual sw::input::IInput*	UseNativeInput	( INativeWindow* nativeWindow, input::InputInitInfo& initInfo )	override;
	virtual INativeWindow*		CreateWindow	( NativeWindowDescriptor& descriptor )							override;
	virtual void				EndApplication	()																override;
	virtual INativeOS*			GetOS			()																override;

	static WinAPIGUI*			Create			();

private:
	void					RegisterWindowClass		();
	bool					MainLoopCore			( MSG* msg );
	
public:
	// Helpers
	static void				PrintLastError			();
	static const wchar_t*	GetWindowClassName		();

public:
	///@Internal
	///@{
	void                    HandleEvent 			( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	void					HandleInput				( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	///@}
};

}	// GUI
}	// sw
