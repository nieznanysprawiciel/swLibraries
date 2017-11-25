#pragma once

#include "swGUI/Native/INativeWindow.h"


#include <Windows.h>
#undef CreateWindow
#undef min
#undef max
#undef XBUTTON1
#undef XBUTTON2

namespace sw {
namespace input
{

class WinApiInputProxy;

}	// input
}	// sw


namespace sw {
namespace gui
{


/**@brief Native window uses WinApi.
@ingroup Win32APINativeGUI*/
class Win32ApiWindow : public INativeWindow
{
private:

	HWND			m_windowHandle;
	std::wstring	m_title;

	uint16			m_width;
	uint16			m_height;

	sw::input::WinApiInputProxy*	m_input;

public:
	explicit			Win32ApiWindow	();
	~Win32ApiWindow	();


	static Win32ApiWindow*		CreateWindowInstance	( NativeWindowDescriptor& descriptor );

private:
	void			ShowAppWindow			();
	void			HideAppWindow			();

	bool			Initialize				( NativeWindowDescriptor& descriptor );


public:
	// Inherited via INativeWindow
	virtual uint16				GetWidth		() const override;
	virtual uint16				GetHeight		() const override;
	virtual uint16				GetClientWidth	() const override;
	virtual uint16				GetClientHeight	() const override;

	virtual WindowHandler		GetHandle		() const override;

	virtual std::string			GetTitle		() const override;

	virtual void				Show			() override;
	virtual void				Hide			() override;

	virtual void				SetTitle		( const std::string & newTitle ) override;

public:

	void						UseNativeInput	( sw::input::WinApiInputProxy* input );
	void						HandleEvent		( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
};


}	// gui
}	// sw
