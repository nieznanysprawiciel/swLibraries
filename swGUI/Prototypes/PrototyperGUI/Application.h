#pragma once
/**
@file Application.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/System/GUISystem.h"



/**@brief Application template class.

User should implement virtual functions to use GUI.*/
class Application : public sw::gui::GUISystem
{
private:
protected:
public:
	explicit	Application		( int argc, char** argv, sw::gui::INativeGUI* gui );
				~Application	() = default;

protected:

	virtual	sw::ReturnResult	Initialize		() override;
	virtual sw::ReturnResult	OnInitialized	() override;
	virtual void	            OnClosing		() override;
	virtual void	            OnIdle			( const sw::gui::FrameTime& frameTime ) override;

    sw::ReturnResult            OverridePaths	();

};

