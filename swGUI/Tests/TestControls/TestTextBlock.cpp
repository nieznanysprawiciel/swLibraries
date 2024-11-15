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
TEST_CASE( "GUI.Controls.TextBlock", "[GUISystem][Controls][Text]" )
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
    REQUIRE( text->QueryDrawing() != nullptr );
    REQUIRE( text->GetGeometry() != nullptr );

    // Run single frame. If something was wrong it should fails here.
    REQUIRE_NOTHROW( framework->MainLoopCore() );
}

