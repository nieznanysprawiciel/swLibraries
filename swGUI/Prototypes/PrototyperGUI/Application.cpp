#include "Application.h"

#include "swGUI/Core/Controls/Shapes/Rectangle.h"
#include "swGUI/Core/Media/Brushes/SolidColorBrush.h"

#include "PrototyperUtils.h"


#include "Sizeofs/Sizeofs.h"

#include <iostream>


using namespace sw::gui;

// ================================ //
//
void		MouseMoveEventReceived			( UIElement* sender, MouseMoveEventArgs* e )
{
	//std::cout	<< "MouseMove Window [" << sender->GetHost()->GetNativeWindow()->GetTitle()
	//			<< "] Position [" << e->WindowPosX << ", " << e->WindowPosY << "], Delta [" 
	//			<< e->MouseDeltaX << ", " << e->MouseDeltaY << "]" << std::endl;
}

// ================================ //
//
void		AddRectangle					( HostWindow* host, BrushPtr brush, BrushPtr stroke, float width, float height, float broderThickness, Position pos )
{
	RectangleOPtr rectangleControl = RectangleOPtr( new Rectangle() );

	rectangleControl->SetFill( brush );
	rectangleControl->SetStroke( stroke );

	rectangleControl->SetHeight( height );
	rectangleControl->SetWidth( width );
	rectangleControl->SetThickness( broderThickness );

	rectangleControl->SetOffset( pos );

	host->AddChild( std::move( rectangleControl ) );
}


// ================================ //
//
void		AddRectangle					( HostWindow* host )
{
	RectangleOPtr rectangleControl = RectangleOPtr( new Rectangle() );
	
	auto brush = std::make_shared< SolidColorBrush >( Color( 1.0, 0.0, 0.0, 1.0 ) );
	auto stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 1.0, 0.0, 1.0 ) );

	AddRectangle( host, brush, stroke, 1024, 30, 2, Position( 0, 40 ) );

	brush = std::make_shared< SolidColorBrush >( Color( 1.0, 0.0, 0.0, 1.0 ) );
	stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 1.0, 0.0, 1.0 ) );

	AddRectangle( host, stroke, brush, 100, 30, 2, Position( 140, 80 ) );

	brush = std::make_shared< SolidColorBrush >( Color( 1.0, 0.0, 0.0, 1.0 ) );
	stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 1.0, 0.0, 1.0 ) );

	AddRectangle( host, stroke, brush, 100, 768, 2, Position( 400, 0 ) );
}




// ================================ //
//
Application::Application	( int argc, char** argv, sw::gui::INativeGUI* gui )
	:	sw::gui::GUISystem( argc, argv, gui )
{}


/**@brief GUI subsystems initialization.

If you need specific gui initialization in your application override this function.
You can set different GraphicApi or input api.*/
bool		Application::Initialize()
{
	bool result = true;
	
	result = result && DefaultInit( 1024, 768, "Window Tittle" );
	result = result && OverridePaths();

	return result;
}

// ================================ //
//
bool		Application::OverridePaths	()
{
	auto coreGUISourcePath = FindCoreGUISourcePath( m_nativeGUI->GetOS()->GetApplicationDir() );

	return m_pathsManager->OverrideAlias( "$(CoreGUI-Shader-Dir)", coreGUISourcePath / "Core/Shaders/hlsl" ).IsValid();
}

/**@brief Function is called when GUI initialization is completed.

In this function you should initialize your application logic.
*/
bool		Application::OnInitialized()
{
	// In this function sizeofs basic classes are printed. Test purposes only.
	PrintSizeofs();

	HostWindow* window = CreateNativeHostWindow( 500, 500, "Additional window" );
	window->PreviewMouseMove() += MouseMoveEventHandler( &MouseMoveEventReceived );
	m_windows[ 0 ]->PreviewMouseMove() += MouseMoveEventHandler( &MouseMoveEventReceived );

	//AddRectangle( window );
	AddRectangle( m_windows[ 0 ] );

	return true;
}

/**@brief Function invoked when application is going to close itself.*/
void		Application::OnClosing()
{ }

/**@brief */
void		Application::OnIdle( const sw::gui::FrameTime& frameTime )
{ }
