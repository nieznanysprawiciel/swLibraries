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
not yet have content.\n\
Lorem ipsum is typically a corrupted version of De finibus bonorum et malorum, \
a 1st - century BC text by the Roman statesman and philosopher Cicero, with words altered, added, \
and removed to make it nonsensical and improper Latin. \
The first two words themselves are a truncation of dolorem ipsum( \"pain itself\" ).";



// ================================ //
//
TextBlock*  AddText			( HostWindow* host, BrushPtr brush, BrushPtr pen, float width, float height, Position pos, const std::wstring& text )
{
    TextBlockOPtr textBlock = TextBlockOPtr( new TextBlock() );

    textBlock->SetBackground( brush );
    textBlock->SetForeground( pen );

    textBlock->SetHeight( height );
    textBlock->SetWidth( width );

    textBlock->SetOffset( pos );
    textBlock->SetText( text );

    auto ptr = textBlock.get();
    host->AddChild( std::move( textBlock ) );
    return ptr;
}


// ================================ //
//
void		AddControls						( HostWindow* host )
{
    {
        auto background = std::make_shared< SolidColorBrush >( Colors::Transparent );
        auto pen = std::make_shared< SolidColorBrush >( Colors::White );
        AddText( host, background, pen, 300, 300, Position( 50, 50 ), sLoremIpsum );
    }
    {
        auto background = std::make_shared< SolidColorBrush >( Colors::WhiteSmoke );
        auto pen = std::make_shared< SolidColorBrush >( Colors::Black );
        auto textBlock = AddText( host, background, pen, 300, 300, Position( 400, 50 ), sLoremIpsum );
        textBlock->SetTextAlignment( sw::TextAlignment::Justify );
    }
    {
        auto background = std::make_shared< SolidColorBrush >( Colors::WhiteSmoke );
        auto pen = std::make_shared< SolidColorBrush >( Colors::Black );
        auto textBlock = AddText( host, background, pen, 300, 300, Position( 750, 50 ), sLoremIpsum );
        textBlock->SetTextAlignment( sw::TextAlignment::Right );
    }
    {
        auto background = std::make_shared< SolidColorBrush >( Colors::WhiteSmoke );
        auto pen = std::make_shared< SolidColorBrush >( Colors::Black );
        auto textBlock = AddText( host, background, pen, 300, 300, Position( 1100, 50 ), sLoremIpsum );
        textBlock->SetTextAlignment( sw::TextAlignment::Center );
    }

    {
        auto pen = std::make_shared< ImageBrush >();
        pen->SetTexture( "$(Application-Dir)/pool-water-texture.jpg" );

        auto background = std::make_shared< SolidColorBrush >( Colors::Transparent );
        auto textBlock = AddText( host, background, pen, 300, 300, Position( 50, 350 ), L"ABO" );
        textBlock->SetTextAlignment( sw::TextAlignment::Justify );
        textBlock->SetFontSize( 80 );
    }


    {
        auto background = std::make_shared< ImageBrush >();
        background->SetTexture( "$(Application-Dir)/pool-water-texture.jpg" );

        auto pen = std::make_shared< SolidColorBrush >( Colors::WhiteSmoke );
        auto textBlock = AddText( host, background, pen, 300, 300, Position( 50, 450 ), sLoremIpsum );
        textBlock->SetTextAlignment( sw::TextAlignment::Justify );
    }
    {
        auto pen = std::make_shared< ImageBrush >();
        pen->SetTexture( "$(Application-Dir)/pool-water-texture.jpg" );

        auto background = std::make_shared< SolidColorBrush >( Colors::Transparent );
        auto textBlock = AddText( host, background, pen, 300, 300, Position( 400, 450 ), sLoremIpsum );
        textBlock->SetTextAlignment( sw::TextAlignment::Justify );
    }
    {
        auto pen = std::make_shared< AngleGradientBrush >();
        pen->SetGradientCenter( Point( 0.5f, 0.5f ) );
        pen->AddGradientStop( GradientStop( 0xFFFF0000, 0.0f ) );
        pen->AddGradientStop( GradientStop( 0xFFFFFF00, 0.3f ) );
        pen->AddGradientStop( GradientStop( 0xFF00FFFF, 0.7f ) );
        pen->AddGradientStop( GradientStop( 0xFF0000FF, 1.0f ) );

        auto background = std::make_shared< SolidColorBrush >( Colors::Transparent );
        auto textBlock = AddText( host, background, pen, 300, 300, Position( 750, 450 ), sLoremIpsum );
        textBlock->SetTextAlignment( sw::TextAlignment::Left );
    }
    {
        auto pen = std::make_shared< LinearGradientBrush >();
        pen->SetGradientAxis( Point( 0.0f, 0.0f ), Point( 1.0f, 1.0f ) );
        pen->AddGradientStop( GradientStop( 0xFFFF0000, 0.0f ) );
        pen->AddGradientStop( GradientStop( 0xFF00FF00, 0.4f ) );
        pen->AddGradientStop( GradientStop( 0xFF0000FF, 0.7f ) );
        pen->AddGradientStop( GradientStop( 0xFFFFFF00, 1.0f ) );

        auto background = std::make_shared< SolidColorBrush >( Colors::Transparent );
        auto textBlock = AddText( host, background, pen, 300, 300, Position( 1100, 450 ), sLoremIpsum );
        textBlock->SetTextAlignment( sw::TextAlignment::Left );
    }
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
