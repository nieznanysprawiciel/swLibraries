#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"
#include "swGUI/Core/Media/Brushes/LinearGradientBrush.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"


using namespace sw;
using namespace sw::gui;


// ================================ //
// Adding GradinetStops should cause change of buffer.
TEST_CASE( "GUI.Rendering.Brush.GradientBrush.AddingGradientStops", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
    LinearGradientBrushPtr brush = std::make_shared< LinearGradientBrush >();

	auto constsName = brush->ConstantsName();

	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );
	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );
	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );
	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );

	CHECK( constsName != brush->ConstantsName() );
}


// ================================ //
// Adding GradinetStops should cause change of buffer.
TEST_CASE( "GUI.Rendering.Brush.GradientBrush.RemovingGradientStops", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
    LinearGradientBrushPtr brush = std::make_shared< LinearGradientBrush >();

	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );
	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );
	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );
	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );

	auto constsName = brush->ConstantsName();

	brush->RemoveGradientStop( 0 );
	brush->RemoveGradientStop( 0 );
	brush->RemoveGradientStop( 0 );

	CHECK( constsName != brush->ConstantsName() );
}

