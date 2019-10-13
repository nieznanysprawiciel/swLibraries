#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"
#include "swGUI/Core/Media/Brushes/LinearGradientBrush.h"
#include "swGUI/Core/Media/Brushes/AngleGradientBrush.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"


using namespace sw;
using namespace sw::gui;


// ================================ //
// Adding GradientStops should cause change of buffer.
TEST_CASE( "GUI.Rendering.Brush.GradientBrush.AddingGradientStops", "[GUISystem][RenderingSystem][Brush]" )
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
// Adding GradientStops should cause change of buffer.
TEST_CASE( "GUI.Rendering.Brush.GradientBrush.RemovingGradientStops", "[GUISystem][RenderingSystem][Brush]" )
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

// ================================ //
// Tests if GradientBrush produces buffer with layout expected by GPU.
TEST_CASE( "GUI.Rendering.Brush.GradientBrush.BufferGeneration.LinearGradientBrush", "[GUISystem][RenderingSystem][Brush]" )
{
    TestFramework framework( 0, nullptr );	framework.Init();
    LinearGradientBrushPtr brush = std::make_shared< LinearGradientBrush >();

    brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );
    brush->AddGradientStop( GradientStop( 0xFFFF0000, 0.4f ) );
    brush->AddGradientStop( GradientStop( 0xFFFFFF00, 0.6f ) );
    brush->AddGradientStop( GradientStop( 0xFF0000FF, 1.0f ) );


    struct TestBufferLayout
    {
        Point		GradientStart;
        Point		GradientEnd;
        uint32      NumStops;
        uint32      Padding[ 3 ];

        // Note: Shader will place each Gradient stop in separate register.
        // We must add 8 bytes to achive the same in this structure.
        std::pair< GradientStop, double >    Stops[ 4 ];
    };

    auto buffer = brush->BufferData();
    auto bufferTyped = reinterpret_cast<TestBufferLayout*>( buffer.DataPtr );

    CHECK( buffer.DataSize == sizeof( TestBufferLayout ) );
    CHECK( buffer.DataSize % 16 == 0 );

    CHECK( bufferTyped->NumStops == 4 );
    CHECK( bufferTyped->Stops[ 0 ].first.Color == 0xFFFF00FF );
    CHECK( bufferTyped->Stops[ 0 ].first.Offset == 0.0f );
    CHECK( bufferTyped->Stops[ 1 ].first.Color == 0xFFFF0000 );
    CHECK( bufferTyped->Stops[ 1 ].first.Offset == 0.4f );
    CHECK( bufferTyped->Stops[ 2 ].first.Color == 0xFFFFFF00 );
    CHECK( bufferTyped->Stops[ 2 ].first.Offset == 0.6f );
    CHECK( bufferTyped->Stops[ 3 ].first.Color == 0xFF0000FF );
    CHECK( bufferTyped->Stops[ 3 ].first.Offset == 1.0f );

    // Manually check buffer offsets. If something fails here you should check
    // Brush structure, because they might change size.
    CHECK( offsetof( TestBufferLayout, NumStops ) == 16 );
    CHECK( offsetof( TestBufferLayout, Stops ) == 32 );
    CHECK( offsetof( TestBufferLayout, Stops[ 1 ] ) == 48 );
}

// ================================ //
// Tests if GradientBrush produces buffer with layout expected by GPU.
TEST_CASE( "GUI.Rendering.Brush.GradientBrush.BufferGeneration.AngleGradientBrush", "[GUISystem][RenderingSystem][Brush]" )
{
    TestFramework framework( 0, nullptr );	framework.Init();
    AngleGradientBrushPtr brush = std::make_shared< AngleGradientBrush >();

    brush->AddGradientStop( GradientStop( 0xFFFF00FF, 0.0f ) );
    brush->AddGradientStop( GradientStop( 0xFFFF0000, 0.4f ) );
    brush->AddGradientStop( GradientStop( 0xFFFFFF00, 0.6f ) );
    brush->AddGradientStop( GradientStop( 0xFF0000FF, 1.0f ) );


    struct TestBufferLayout
    {
        Point		Center;
        uint32      NumStops;
        uint32      Padding[ 1 ];

        // Note: Shader will place each Gradient stop in separate register.
        // We must add 8 bytes to achive the same in this structure.
        std::pair< GradientStop, double >    Stops[ 4 ];
    };

    auto buffer = brush->BufferData();
    auto bufferTyped = reinterpret_cast< TestBufferLayout* >( buffer.DataPtr );

    CHECK( buffer.DataSize == sizeof( TestBufferLayout ) );
    CHECK( buffer.DataSize % 16 == 0 );

    CHECK( bufferTyped->NumStops == 4 );
    CHECK( bufferTyped->Stops[ 0 ].first.Color == 0xFFFF00FF );
    CHECK( bufferTyped->Stops[ 0 ].first.Offset == 0.0f );
    CHECK( bufferTyped->Stops[ 1 ].first.Color == 0xFFFF0000 );
    CHECK( bufferTyped->Stops[ 1 ].first.Offset == 0.4f );
    CHECK( bufferTyped->Stops[ 2 ].first.Color == 0xFFFFFF00 );
    CHECK( bufferTyped->Stops[ 2 ].first.Offset == 0.6f );
    CHECK( bufferTyped->Stops[ 3 ].first.Color == 0xFF0000FF );
    CHECK( bufferTyped->Stops[ 3 ].first.Offset == 1.0f );

    // Manually check buffer offsets. If something fails here you should check
    // Brush structure, because they might change size.
    CHECK( offsetof( TestBufferLayout, NumStops ) == 8 );
    CHECK( offsetof( TestBufferLayout, Stops ) == 16 );
    CHECK( offsetof( TestBufferLayout, Stops[ 1 ] ) == 32 );
}
