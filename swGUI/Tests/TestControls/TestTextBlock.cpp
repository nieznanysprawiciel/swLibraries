#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"
#include "swGUI/TestFramework/DX11/TestFramework.DX11.h"
#include "swGUI/Native/MockNativeGUI/MockGUI.h"

#include "swGUI/Core/Controls/TextualControls/TextBlock.h"
#include "swGUI/Core/Media/Brushes/SolidColorBrush.h"


using namespace sw;
using namespace sw::gui;

//====================================================================================//
//			Helper functions	
//====================================================================================//

// ================================ //
//
TextBlock* AddText( HostWindow* host, BrushPtr brush, BrushPtr pen, float width, float height, Position pos,
                    const std::wstring& text )
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

const std::wstring sLoremIpsum = L"Lorem ipsum is a dummy or placeholder text commonly used \
in graphic design, publishing, and web development to fill empty spaces in a layout that do \
not yet have content.\n\
Lorem ipsum is typically a corrupted version of De finibus bonorum et malorum, \
a 1st - century BC text by the Roman statesman and philosopher Cicero, with words altered, added, \
and removed to make it nonsensical and improper Latin. \
The first two words themselves are a truncation of dolorem ipsum( \"pain itself\" ).";


//====================================================================================//
//			Tests	
//====================================================================================//

// ================================ //
// 
TEST_CASE( "GUI.Controls.TextBlock.BasicFlow", "[GUISystem][Controls][Text]" )
{
    TestFramework* framework = GetGlobalTestFramework();
    FrameworkCleaner cleaner( framework );

    MockGUI* mockNativeGUI = static_cast< MockGUI* >( framework->GetNativeGUI() );
    auto window = framework->CreateNativeHostWindow( 400, 400, "Test Window" ).Get();
    
    // Window must be focused to be rendered.
    mockNativeGUI->SendChangeFocus( window->GetNativeWindow(), true );

    auto background = std::make_shared< SolidColorBrush >( Colors::WhiteSmoke );
    auto pen = std::make_shared< SolidColorBrush >( Colors::Black );

    auto text = AddText( window, background, pen, 300, 300, Position( 0, 40 ), sLoremIpsum );

    // Run single frame. If something was wrong it should fails here.
    REQUIRE_NOTHROW( framework->MainLoopCore() );

    auto drawing = text->QueryDrawing();
    auto geometry = text->GetGeometry();
    auto font = std::static_pointer_cast< TextGeometry >( text->GetGeometry() )->GetFont();

    REQUIRE( drawing != nullptr );
    REQUIRE( geometry != nullptr );

    // Parameters don't change Geometry an Drawing.
    text->SetText( L"New text" );
    text->SetTextAlignment( TextAlignment::Center );

    REQUIRE_NOTHROW( framework->MainLoopCore() );

    CHECK( text->QueryDrawing() == drawing );
    CHECK( text->GetGeometry() == geometry );

    // Updates require Geometry re-creation
    text->SetFontFamily( "Source Sans Pro" );
    REQUIRE_NOTHROW( framework->MainLoopCore() );

    auto newDrawing = text->QueryDrawing();
    auto newGeometry = text->GetGeometry();
    auto newFont = std::static_pointer_cast< TextGeometry >( text->GetGeometry() )->GetFont();
    CHECK( newDrawing != drawing );
    CHECK( newGeometry != geometry );
    CHECK( newFont != font );
    CHECK( newFont->GetMetadata().Family == "Source Sans Pro" );
    CHECK( newFont->GetMetadata().Style == FontStyle::Normal );
    CHECK( newFont->GetMetadata().Weight == FontWeight::Regular );


    text->SetFontWeight( FontWeight::Bold );
    REQUIRE_NOTHROW( framework->MainLoopCore() );

    drawing = text->QueryDrawing();
    geometry = text->GetGeometry();
    font = std::static_pointer_cast< TextGeometry >( text->GetGeometry() )->GetFont();
    CHECK( newDrawing != drawing );
    CHECK( newGeometry != geometry );
    CHECK( font != newFont );
    CHECK( font->GetMetadata().Family == "Source Sans Pro" );
    CHECK( font->GetMetadata().Style == FontStyle::Normal );
    CHECK( font->GetMetadata().Weight == FontWeight::Bold );


    text->SetFontStyle( FontStyle::Italic );
    text->SetFontWeight( FontWeight::Regular );
    REQUIRE_NOTHROW( framework->MainLoopCore() );

    newDrawing = text->QueryDrawing();
    newGeometry = text->GetGeometry();
    newFont = std::static_pointer_cast< TextGeometry >( text->GetGeometry() )->GetFont();
    CHECK( newDrawing != drawing );
    CHECK( newGeometry != geometry );
    CHECK( newFont != font );
    CHECK( newFont->GetMetadata().Family == "Source Sans Pro" );
    CHECK( newFont->GetMetadata().Style == FontStyle::Italic );
    CHECK( Eqivalent( newFont->GetMetadata().Weight, FontWeight::Normal ) );
}

// ================================ //
//
TEST_CASE( "GUI.Controls.TextBlock.Resources.LazyLoading", "[GUISystem][Controls][Text]" )
{
    TestFramework*   framework = GetGlobalTestFramework();
    FrameworkCleaner cleaner( framework );

    MockGUI* mockNativeGUI = static_cast< MockGUI* >( framework->GetNativeGUI() );
    auto     window = framework->CreateNativeHostWindow( 400, 400, "Test Window" ).Get();

    // Window must be focused to be rendered.
    mockNativeGUI->SendChangeFocus( window->GetNativeWindow(), true );

    auto background = std::make_shared< SolidColorBrush >( Colors::WhiteSmoke );
    auto pen = std::make_shared< SolidColorBrush >( Colors::Black );

    auto text = AddText( window, background, pen, 300, 300, Position( 0, 40 ), sLoremIpsum );

    // Run single frame. If something was wrong it should fails here.
    REQUIRE_NOTHROW( framework->MainLoopCore() );

    auto drawing = text->QueryDrawing();
    auto geometry = text->GetGeometry();
    auto font = std::static_pointer_cast< TextGeometry >( text->GetGeometry() )->GetFont();

    REQUIRE( drawing != nullptr );
    REQUIRE( geometry != nullptr );

    // Parameters don't change Geometry an Drawing.
    text->SetText( L"New text" );
    text->SetTextAlignment( TextAlignment::Center );

    CHECK( text->QueryDrawing() == drawing );
    CHECK( text->GetGeometry() == geometry );

    text->SetFontFamily( "Source Sans Pro" );
    CHECK( text->GetGeometry() == geometry );  // Lazy re-loading expected.

    text->SetFontWeight( FontWeight::Bold );
    CHECK( text->GetGeometry() == geometry );  // Lazy re-loading expected.
    CHECK( std::static_pointer_cast< TextGeometry >( text->GetGeometry() )->GetFont() == font );

    text->SetFontStyle( FontStyle::Italic );
    CHECK( text->GetGeometry() == geometry );  // Lazy re-loading expected.
    CHECK( std::static_pointer_cast< TextGeometry >( text->GetGeometry() )->GetFont() == font );
    text->SetFontStyle( FontStyle::Normal );

    REQUIRE_NOTHROW( framework->MainLoopCore() );

    // Updates should happen.
    auto newFont = std::static_pointer_cast< TextGeometry >( text->GetGeometry() )->GetFont();
    CHECK( text->QueryDrawing() != drawing );
    CHECK( text->GetGeometry() != geometry );
    CHECK( newFont != font );
    CHECK( newFont->GetMetadata().Family == "Source Sans Pro" );
    CHECK( newFont->GetMetadata().Style == FontStyle::Normal );
    CHECK( newFont->GetMetadata().Weight == FontWeight::Bold );
}
