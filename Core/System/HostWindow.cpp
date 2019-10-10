/**
@file HostWindow.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "HostWindow.h"

#include "swCommonLib/Common/Converters.h"

#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"
#include "swGraphicAPI/ResourceManager/ResourceManager.h"

#include "swInputLibrary/InputCore/Helpers/InputDispatcher.h"

#include "CommonTypes/CommonTypes.h"


// Temporary
#include <iostream>



RTTR_REGISTRATION
{
	rttr::registration::class_< sw::gui::HostWindow >( "sw::gui::HostWindow" );
}



namespace sw {
namespace gui
{



// ================================ //
//
HostWindow::HostWindow( INativeWindow* nativeWindow, input::IInput* input, ResourceManager* resourceManager, IGraphicAPIInitializer* graphicApi )
	:	m_input( input )
	,	m_nativeWindow( nativeWindow )
	,	m_resourceManager( resourceManager )
	,	m_hostLogic( this )
{
	// Create RenderTarget and SwapChain
	SwapChainInitData init;
	init.WindowHandle = m_nativeWindow->GetHandle();
	init.WindowHeight = m_nativeWindow->GetClientHeight();
	init.WindowWidth = m_nativeWindow->GetClientWidth();

	m_swapChain = graphicApi->CreateSwapChain( init );
	assert( m_swapChain.Ptr() );

	m_renderTarget = m_swapChain->GetRenderTarget();
	assert( m_renderTarget.Ptr() );

	resourceManager->AddRenderTarget( m_renderTarget.Ptr(), Convert::FromString< std::wstring >( "::" + m_nativeWindow->GetTitle(), L"" ) );
}

// ================================ //
//
HostWindow::~HostWindow()
{
	m_swapChain->DeleteObjectReference();
	if( m_swapChain->CanDelete() )
	{
		delete m_swapChain.Ptr();
		m_swapChain = nullptr;
	}

	delete m_input;
	delete m_nativeWindow;
}



/**@brief Returns memory consumed by this object and all object owned by this.*/
Size				HostWindow::GetMemorySize		()
{
	Size size = sizeof( HostWindow );
	size += m_hostLogic.GetMemorySize();

	return size;
}

/**@brief Removes control from GUI system.*/
void				HostWindow::RemoveControl		( UIElement* control )
{
	m_hostLogic.RemoveControl( control );
}

/**@brief Allows control to register it's name.*/
void				HostWindow::RegisterControlName	( const UIElement* control, const std::string& name )
{
	m_hostLogic.RegisterControlName( control, name );
}

/**@brief Gets name of registered control.*/
const std::string&	HostWindow::GetControlName		( const UIElement* control ) const
{
	return m_hostLogic.GetControlName( control );
}

// ================================ //
//
ResourcePtr< RenderTargetObject >	HostWindow::GetRenderTarget()
{
	return m_renderTarget;
}

// ================================ //
//
ResourcePtr< SwapChain >	HostWindow::GetSwapChain()
{
	return m_swapChain;
}

// ================================ //
//
INativeWindow*		HostWindow::GetNativeWindow		()
{
	return m_nativeWindow;
}

// ================================ //
//
input::IInput*		HostWindow::GetInput			()
{
	return m_input;
}

// ================================ //
//
HostWindow*			HostWindow::GetHost				() const
{
	return const_cast< HostWindow* >( this );
}

//====================================================================================//
//				GUI system interaction. Redirects to HostLogic.
//====================================================================================//

// ================================ //
//
void				HostWindow::LostFocus			()
{
	// @todo Debug. Remove in future.
	std::cout << "Window [" + m_nativeWindow->GetTitle() + "] lost focus." << std::endl;

	m_hostLogic.LostFocus();
}

// ================================ //
//
void				HostWindow::GotFocus			()
{
	// @todo Debug. Remove in future.
	std::cout << "Window [" + m_nativeWindow->GetTitle() + "] got focus." << std::endl;

	m_hostLogic.GotFocus();
}

// ================================ //
//
void				HostWindow::OnResized			( uint16 newWidth, uint16 newHeight )
{
	m_hostLogic.OnResized( newWidth, newHeight );
}

// ================================ //
//
void				HostWindow::OnMaximized			()
{
	m_hostLogic.OnMaximized();
}

// ================================ //
//
void				HostWindow::OnMinimized			()
{
	m_hostLogic.OnMinimized();
}

// ================================ //
//
void				HostWindow::HandleInput			( const FrameTime& frameTime )
{
	m_input->Update( (float)frameTime.Elapsed );

	input::InputDispatcher dispatcher( m_input );

	while( !dispatcher.NoEventsLeft() )
	{
		auto dispatched = dispatcher.NextEvent();
		switch( dispatched.Event.Type )
		{
			case input::DeviceEventType::KeyboardEvent:
				m_hostLogic.HandleKeyInput( dispatched.Event, dispatched.ProducerDevice );
				break;
			case input::DeviceEventType::CharacterEvent:
				m_hostLogic.HandleCharInput( dispatched.Event, dispatched.ProducerDevice );
				break;
			case input::DeviceEventType::ButtonEvent:
				m_hostLogic.HandleMouseButtonInput( dispatched.Event, dispatched.ProducerDevice );
				break;
			case input::DeviceEventType::AxisEvent:
				m_hostLogic.HandleMouseWheelInput( dispatched.Event, dispatched.ProducerDevice );
				break;
			case input::DeviceEventType::CursorEvent:
				m_hostLogic.HandleMouseMoveInput( dispatched.Event, dispatched.ProducerDevice );
				break;

		}
	}
}


//====================================================================================//
//			Implement pure virtuals - temporary implementation	
//====================================================================================//


// ================================ //
//
bool				HostWindow::HitTest				( const Position& point )
{
	return false;
}

// ================================ //
//
Size2D				HostWindow::Measure				( Size2D availableSize )
{
	return Size2D();
}

// ================================ //
//
void				HostWindow::Arrange				( Rect & finalRect )
{}

// ================================ //
//
Size				HostWindow::GetNumChildren		() const
{
	return m_hostLogic.GetNumChildren();
}

// ================================ //
//
Visual*				HostWindow::GetVisualChild		( Size idx ) const
{
	return m_hostLogic.GetChild( idx );
}

// ================================ //
//
bool				HostWindow::AddChild			( UIElementOPtr&& child )
{
	return m_hostLogic.AddChild( std::move( child ) );
}

// ================================ //
//
IDrawing*			HostWindow::QueryDrawing		() const
{
	return nullptr;
}



}	// gui
}	// sw
