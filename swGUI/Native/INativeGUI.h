#pragma once


#include "INativeWindow.h"
#include "swCommonLib/External/FastDelegate/FastDelegate.h"

#include "swInputLibrary/InputCore/IInput.h"


/**@defgroup NativeGUI Native GUI system
@brief OS specific stuff.
Here are things using underlying system API to create windows and handle events from system.
@ingroup SWGUI*/


namespace sw {
namespace gui
{

typedef fastdelegate::FastDelegate2< INativeWindow*, bool > ChangedFocusDelegate;


/**@brief Provides data needed for native GUI system initialization.
@ingroup NativeGUI*/
struct NativeGUIInitData
{
	ChangedFocusDelegate		FocusChanged;
};


/**@brief Interface encasulates native GUI system.
@ingroup NativeGUI*/
class INativeGUI
{
private:
protected:
public:
	INativeGUI() = default;
	~INativeGUI() = default;


	/**@brief Invokes main loop of native GUI.
	@return Returns true if application should close.*/
	virtual bool					MainLoop		( bool blockingMode ) = 0;

	/**@brief Initializes native GUI.
	@return Returns false if initialization failed.*/
	virtual bool					Init			( const NativeGUIInitData& initData ) = 0;

	/**@brief Initalize native api for window in parameter and return IInput object.
	GUI can use native input api for specific gui system or provide different
	library to deal directly with hardware. Classes derived from INativeGUI are reposible
	for updating native inputs in main loop. In case of using separate hardware input library
	INativeGUI does nothing.*/
	virtual sw::input::IInput*		UseNativeInput	( INativeWindow* nativeWindow ) = 0;

	/**@brief Provides posibility to specify input init arguments.
	Note that fields AppInstance and WindowHandle which can be filled by native window system, can
	be leaved as nullptr.*/
	virtual sw::input::IInput*		UseNativeInput	( INativeWindow* nativeWindow, input::InputInitInfo& initInfo ) = 0;

	/**@brief Creates native GUI window.*/
	virtual INativeWindow*			CreateWindow	( NativeWindowDescriptor& descriptor ) = 0;

	/**@brief REquest native gui to close application.*/
	virtual void					EndApplication	() = 0;
};


}	// gui
}	// sw
