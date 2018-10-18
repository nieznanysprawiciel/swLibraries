#pragma once
/**
@file MockGUI.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Native/INativeGUI.h"
#include "MockOS.h"




/**@defgroup MockGUI Fake GUI for tests.
@brief Fake native GUI classes for tests.
@ingroup NativeGUI*/


namespace sw {
namespace gui
{


/**@brief 
@ingroup MockGUI*/
class MockGUI : public INativeGUI
{
private:

	NativeGUIInitData				m_initData;
	MockOS							m_os;

protected:
public:
	explicit			MockGUI	();
	virtual				~MockGUI	() = default;


// Inherited via INativeGUI
	virtual bool				MainLoop		( bool blockingMode )												override;
	virtual bool				Init			( const NativeGUIInitData& initData )								override;
	virtual sw::input::IInput*	UseNativeInput	( INativeWindow* nativeWindow )										override;
	virtual sw::input::IInput*	UseNativeInput	( INativeWindow* nativeWindow, input::InputInitInfo& initInfo )		override;
	virtual INativeWindow*		CreateWindow	( NativeWindowDescriptor& descriptor )								override;
	virtual void				EndApplication	()																	override;
	virtual INativeOS*			GetOS			()																	override;

	static MockGUI*				Create			();

public:

	void						SendChangeFocus	( INativeWindow* nativeWindow, bool change );

};

}	// GUI
}	// sw
