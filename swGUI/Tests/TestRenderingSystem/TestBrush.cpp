#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"
#include "swGUI/Core/Media/Brushes/LinearGradientBrush.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"


using namespace sw;
using namespace sw::gui;


// ================================ //
//
TEST_CASE( "GUI.Rendering.Brush.GradientBrush.AddingGradientStops", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	LinearGradientPtr brush = std::make_shared< LinearGradient >();

	auto constsName = brush->ConstantsName();

	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );
	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );
	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );
	brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );

	CHECK( constsName != brush->ConstantsName() );
}




