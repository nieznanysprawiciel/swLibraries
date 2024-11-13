#pragma once
/**
@file Application.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/System/GUISystem.h"
#include "swGUI/Core/System/DataBinding/DependencyObject.h"
#include "swGUI/Core/System/DataBinding/DependencyProperty.h"


/**@brief View of content that will be bound as DataContext to present information.*/
class ViewModel : public sw::gui::DependencyObject
{
    RTTR_ENABLE( sw::gui::DependencyObject )
    RTTR_REGISTRATION_FRIEND

private:
    static sw::gui::DependencyProperty sTimeCounter;

private:

    std::wstring m_timeCounter;

public:

    explicit ViewModel() = default;

    const std::wstring&     GetTimeCounter() const { return m_timeCounter; }
    void                    SetTimeCounter( const std::wstring& value ) { SetValue( sTimeCounter, value, &ViewModel::m_timeCounter ); }

};


/**@brief Application template class.

User should implement virtual functions to use GUI.*/
class Application : public sw::gui::GUISystem
{
private:
protected:

    ViewModel   m_viewModel;

public:
	explicit	Application		( int argc, char** argv, sw::gui::INativeGUI* gui );
				~Application	() = default;

protected:

	virtual	sw::ReturnResult	Initialize		() override;
	virtual sw::ReturnResult	OnInitialized	() override;
	virtual void	            OnClosing		() override;
	virtual void	            OnIdle			( const sw::gui::FrameTime& frameTime ) override;

    sw::ReturnResult            OverridePaths	();

    void                        AddControls     ( sw::gui::HostWindow* host );

};

