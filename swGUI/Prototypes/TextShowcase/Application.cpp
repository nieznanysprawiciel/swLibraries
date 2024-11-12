#include "Application.h"

#include "swGUI/Core/Controls/Shapes/Rectangle.h"
#include "swGUI/Core/Controls/Shapes/Ellipse.h"
#include "swGUI/Core/Controls/TextualControls/TextBlock.h"

#include "swGUI/Core/Media/Brushes/SolidColorBrush.h"
#include "swGUI/Core/Media/Brushes/LinearGradientBrush.h"
#include "swGUI/Core/Media/Brushes/AngleGradientBrush.h"
#include "swGUI/Core/Media/Brushes/ImageBrush.h"

#include "swGUI/Core/Media/Colors.h"

#include "PrototyperUtils.h"

#include <iostream>


using namespace sw::gui;

const std::wstring sLoremIpsum = L"Lorem ipsum is a dummy or placeholder text commonly used \
in graphic design, publishing, and web development to fill empty spaces in a layout that do \
not yet have content.";


// ================================ //
//
void		AddText			( HostWindow* host, BrushPtr brush, BrushPtr pen, float width, float height, Position pos, const std::wstring& text )
{
    TextBlockOPtr textBlock = TextBlockOPtr( new TextBlock() );

    textBlock->SetBackground( brush );
    textBlock->SetForeground( pen );

    textBlock->SetHeight( height );
    textBlock->SetWidth( width );

    textBlock->SetOffset( pos );
    textBlock->SetText( text );

    host->AddChild( std::move( textBlock ) );
}


// ================================ //
//
void		AddControls						( HostWindow* host )
{
	auto background = std::make_shared< SolidColorBrush >( Colors::Transparent );
    auto pen = std::make_shared< SolidColorBrush >( Colors::White );
    AddText( host, background, pen, 200, 200, Position( 50, 100 ), sLoremIpsum );
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

    sw::ReturnResult result = sw::Success::True;

	result = result && DefaultInit( 1500, 768, "Text variation showcase" );
	result = result && OverridePaths();

	return result;
}

// ================================ //
//
sw::ReturnResult        Application::OverridePaths	()
{
	auto coreGUISourcePath = FindCoreGUISourcePath( m_nativeGUI->GetOS()->GetApplicationDir() );

    m_pathsManager->RegisterAlias( "$(Application-Dir)", coreGUISourcePath / "Prototypes/AppResources/" );
	return m_pathsManager->OverrideAlias( "$(CoreGUI-Shader-Dir)", coreGUISourcePath / "Core/Shaders/hlsl" );
}

/**@brief Function is called when GUI initialization is completed.

In this function you should initialize your application logic.
*/
sw::ReturnResult		Application::OnInitialized()
{
    AddControls( m_windows[ 0 ] );
    return sw::Success::True;
}

/**@brief Function invoked when application is going to close itself.*/
void		Application::OnClosing()
{ }

/**@brief */
void		Application::OnIdle( const sw::gui::FrameTime& frameTime )
{ }
