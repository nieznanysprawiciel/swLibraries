#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestWindowRendering.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/TestFramework/DX11/TestFramework.DX11.h"
#include "swGUI/TestFramework/Testers/Rendering/RenderingSystemTester.h"
#include "swGUI/Native/MockNativeGUI/MockGUI.h"

#include "swGUI/Core/Controls/Shapes/Rectangle.h"
#include "swGUI/Core/Controls/Shapes/Ellipse.h"
#include "swGUI/Core/Media/Brushes/SolidColorBrush.h"
#include "swGUI/Core/Media/Brushes/LinearGradientBrush.h"


using namespace sw;
using namespace sw::gui;

//====================================================================================//
//			Helper functions for creating window content	
//====================================================================================//

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
struct FrameworkCleaner
{
    TestFramework*      Framework;

    // ================================ //
    //
    FrameworkCleaner( TestFramework* framework )
        : Framework( framework )
    {}

    // ================================ //
    //
    ~FrameworkCleaner()
    {        Framework->Clean();    }
};

//====================================================================================//
//			Test cases	
//====================================================================================//


// ================================ //
//
TEST_CASE( "GUI.RenderingSystem.WindowRendering", "[GUISystem][RenderingSystem]" )
{
    TestFramework* framework = GetGlobalTestFramework();
    FrameworkCleaner cleaner( framework );

    MockGUI* mockNativeGUI = static_cast< MockGUI* >( framework->GetNativeGUI() );

    auto window = framework->CreateNativeHostWindow( 400, 400, "Test Window" ).Get();

    auto brush = std::make_shared< SolidColorBrush >( Color( 1.0, 0.0, 0.0, 1.0 ) );
    auto stroke = std::make_shared< SolidColorBrush >( Color( 0.0, 1.0, 0.0, 1.0 ) );

    AddRectangle( window, brush, stroke, 1024, 30, 2, Position( 0, 40 ) );

    // Window must be focused to be rendered.
    mockNativeGUI->SendChangeFocus( window->GetNativeWindow(), true );

    // Run single frame. If something was wrong it should fails here.
    framework->MainLoopCore();
}



