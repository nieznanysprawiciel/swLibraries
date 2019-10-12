#pragma once
/**
@file HostWindow.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "HostLogic.h"
#include "swGUI/Native/INativeWindow.h"
#include "swGUI/Core/System/Time/FrameTime.h"

#include "swInputLibrary/InputCore/IInput.h"

#include <vector>
#include <map>




namespace sw
{
	class IGraphicAPIInitializer;
}	// sw


namespace sw {
namespace gui
{

/**@brief Root class for controls hierarchy, contains native window.

This class connects native window and gui windows. GUI system logic is redirected to HostLogic class.
HostWindow is responsible for rendering and presenting content on native window by using render target and swap chain.

@ingroup GUICore
@ingroup ControlsFramework*/
class HostWindow : public UIElement
{
	RTTR_ENABLE( UIElement );
	friend class HostWindowTester;
private:

	INativeWindow*				m_nativeWindow;
	input::IInput*				m_input;
	ResourceManager*			m_resourceManager;

	ResourcePtr< RenderTarget >	m_renderTarget;
	ResourcePtr< SwapChain >			m_swapChain;

	HostLogic					m_hostLogic;

protected:
public:

	explicit		HostWindow	( INativeWindow* nativeWindow, input::IInput* input, ResourceManager* resourceManager, sw::IGraphicAPIInitializer* graphicApi );
	virtual			~HostWindow	();


	void				RemoveControl		( UIElement* control );

	void				RegisterControlName	( const UIElement* control, const std::string& name );
	const std::string&	GetControlName		( const UIElement* control ) const;


	ResourcePtr< RenderTarget >	GetRenderTarget		();
	ResourcePtr< SwapChain >			GetSwapChain		();

	INativeWindow*						GetNativeWindow		();
	input::IInput*						GetInput			();

	virtual HostWindow*					GetHost				() const override;

public:

	Size				GetMemorySize		();

public:
	///@name GUI system interaction
	///@{
	void				LostFocus		();
	void				GotFocus		();

	void				OnResized		( uint16 newWidth, uint16 newHeight );
	void				OnMaximized		();
	void				OnMinimized		();

	void				HandleInput		( const FrameTime& frameTime );
	///@}


	// Inherited via UIElement
	virtual bool					HitTest			( const Position& point )		override;
	virtual Size2D					Measure			( Size2D availableSize )		override;
	virtual void					Arrange			( Rect& finalRect )				override;
	virtual IDrawing*				QueryDrawing	() const						override;

	virtual Size					GetNumChildren	() const						override;
	virtual Visual*					GetVisualChild	( Size idx ) const				override;
	virtual bool					AddChild		( UIElementOPtr&& child )		override;
};

DEFINE_OPTR_TYPE( HostWindow );
DEFINE_PTR_TYPE( HostWindow );


}	// gui
}	// sw
