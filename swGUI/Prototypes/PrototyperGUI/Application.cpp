#include "Application.h"

#include "swGUI/Core/Controls/Shapes/Rectangle.h"
#include "swGUI/Core/Controls/Shapes/Ellipse.h"

#include "swGUI/Core/Media/Brushes/SolidColorBrush.h"
#include "swGUI/Core/Media/Brushes/LinearGradientBrush.h"
#include "swGUI/Core/Media/Brushes/AngleGradientBrush.h"

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
void		AddEllipse						( HostWindow* host, BrushPtr brush, BrushPtr stroke, float width, float height, float broderThickness, Position pos )
{
	EllipseOPtr ellipseControl = EllipseOPtr( new Ellipse() );

	ellipseControl->SetFill( brush );
	ellipseControl->SetStroke( stroke );

	ellipseControl->SetHeight( height );
	ellipseControl->SetWidth( width );
	ellipseControl->SetThickness( broderThickness );

	ellipseControl->SetOffset( pos );

	host->AddChild( std::move( ellipseControl ) );
}


// ================================ //
//
void		AddControls						( HostWindow* host )
{
	auto brush = std::make_shared< SolidColorBrush >( Color( 1.0, 0.0, 0.0, 1.0 ) );
	auto stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 1.0, 0.0, 1.0 ) );

	AddRectangle( host, brush, stroke, 1024, 30, 2, Position( 0, 40 ) );

	brush = std::make_shared< SolidColorBrush >( Color( 1.0, 0.0, 0.0, 1.0 ) );
	stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 1.0, 0.0, 1.0 ) );

	AddRectangle( host, stroke, brush, 100, 30, 2, Position( 140, 80 ) );

	brush = std::make_shared< SolidColorBrush >( Color( 1.0, 0.0, 0.0, 1.0 ) );
	stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 1.0, 0.0, 1.0 ) );

	AddRectangle( host, stroke, brush, 100, 768, 2, Position( 400, 0 ) );

	brush = std::make_shared< SolidColorBrush >( Color( 0.0, 0.0, 1.0, 1.0 ) );
	stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 0.0, 0.0, 1.0 ) );

	AddEllipse( host, stroke, brush, 100, 200, 8, Position( 200, 300 ) );

	auto gradientBrush = std::make_shared< LinearGradientBrush >();
	gradientBrush->AddGradientStop( GradientStop( 0xFFFF0000, 0.0f ) );
	gradientBrush->AddGradientStop( GradientStop( 0xFF0000FF, 1.0f ) );
	stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 0.0, 0.0, 1.0 ) );

	AddRectangle( host, gradientBrush, stroke, 40, 768, 2, Position( 600, 0 ) );

	gradientBrush = std::make_shared< LinearGradientBrush >();
	gradientBrush->AddGradientStop( GradientStop( 0xFFFF0000, 0.3f ) );
	gradientBrush->AddGradientStop( GradientStop( 0xFF0000FF, 0.7f ) );
	stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 0.0, 0.0, 1.0 ) );

	AddRectangle( host, gradientBrush, stroke, 40, 768, 2, Position( 650, 0 ) );

	gradientBrush = std::make_shared< LinearGradientBrush >();
	gradientBrush->AddGradientStop( GradientStop( 0xFFFF0000, 0.0f ) );
	gradientBrush->AddGradientStop( GradientStop( 0xFF00FF00, 0.4f ) );
	gradientBrush->AddGradientStop( GradientStop( 0xFF0000FF, 0.7f ) );
	gradientBrush->AddGradientStop( GradientStop( 0xFFFFFF00, 1.0f ) );
	stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 0.0, 0.0, 1.0 ) );

	AddRectangle( host, gradientBrush, stroke, 40, 768, 2, Position( 700, 0 ) );

	gradientBrush = std::make_shared< LinearGradientBrush >();
	gradientBrush->SetGradientAxis( Point( 0.0f, 0.0f ), Point( 1.0f, 1.0f ) );
	gradientBrush->AddGradientStop( GradientStop( 0xFFFF0000, 0.0f ) );
	gradientBrush->AddGradientStop( GradientStop( 0xFF00FF00, 0.4f ) );
	gradientBrush->AddGradientStop( GradientStop( 0xFF0000FF, 0.7f ) );
	gradientBrush->AddGradientStop( GradientStop( 0xFFFFFF00, 1.0f ) );
	stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 0.0, 0.0, 1.0 ) );

	AddRectangle( host, gradientBrush, stroke, 120, 768, 2, Position( 750, 0 ) );
}


// ================================ //
//
void		AddControls2					( HostWindow* host )
{
    auto angleBrush = std::make_shared< AngleGradientBrush >();
    angleBrush->SetGradientCenter( Point( 0.5f, 0.5f ) );
    angleBrush->AddGradientStop( GradientStop( 0xFFFF0000, 0.0f ) );
    //angleBrush->AddGradientStop( GradientStop( 0xFF00FF00, 0.4f ) );
    //angleBrush->AddGradientStop( GradientStop( 0xFF0000FF, 0.7f ) );
    angleBrush->AddGradientStop( GradientStop( 0xFFFFFF00, 1.0f ) );
    auto stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 0.0, 0.0, 1.0 ) );

    AddRectangle( host, angleBrush, stroke, 200, 200, 2, Position( 30, 30 ) );
}



// ================================ //
//
Application::Application	( int argc, char** argv, sw::gui::INativeGUI* gui )
	:	sw::gui::GUISystem( argc, argv, gui )
{}


/**@brief GUI subsystems initialization.

If you need specific gui initialization in your application override this function.
You can set different GraphicApi or input api.*/
sw::ReturnResult		Application::Initialize()
{
	m_guiConfig.DebugGraphics = true;

    sw::ReturnResult result = sw::Result::Success;

	result = result && DefaultInit( 1024, 768, "Window Tittle" );
	result = result && OverridePaths();

	return result;
}

// ================================ //
//
sw::ReturnResult        Application::OverridePaths	()
{
	auto coreGUISourcePath = FindCoreGUISourcePath( m_nativeGUI->GetOS()->GetApplicationDir() );

	return m_pathsManager->OverrideAlias( "$(CoreGUI-Shader-Dir)", coreGUISourcePath / "Core/Shaders/hlsl" );
}

/**@brief Function is called when GUI initialization is completed.

In this function you should initialize your application logic.
*/
sw::ReturnResult		Application::OnInitialized()
{
    // In this function sizeofs basic classes are printed. Test purposes only.
    PrintSizeofs();

    auto window = CreateNativeHostWindow( 500, 500, "Additional window" );
    if( window.IsValid() )
    {
        window.Get()->PreviewMouseMove() += MouseMoveEventHandler( &MouseMoveEventReceived );
        m_windows[ 0 ]->PreviewMouseMove() += MouseMoveEventHandler( &MouseMoveEventReceived );

        AddControls( m_windows[ 0 ] );
        AddControls2( m_windows[ 1 ] );

        return sw::Result::Success;
    }
    else
	    return window.GetError();
}

/**@brief Function invoked when application is going to close itself.*/
void		Application::OnClosing()
{ }

/**@brief */
void		Application::OnIdle( const sw::gui::FrameTime& frameTime )
{ }
