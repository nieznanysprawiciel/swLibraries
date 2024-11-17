#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestFontLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <regex>

#include "swCommonLib\TestUtils\CatchUtils\ExtendedMacros.h"
#include "swCommonLib/Common/Converters/Convert.h"

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"
#include "swGraphicAPI/Assets/TextAsset/Loader/FontAssetInitData.h"
#include "swGraphicAPI/Tests/TestText/Utils.h"


using namespace sw;

// ================================ //
// 
bool    NoOverlappingGlyphs( const FontLayout& layout )
{
    for( auto glyph1 = layout.Glyphs.begin(); glyph1 != layout.Glyphs.end(); ++glyph1 )
    {
        for( auto glyph2 = layout.Glyphs.begin(); glyph2 != layout.Glyphs.end(); ++glyph2 )
        {
            if( glyph1 != glyph2 )
            {
                auto rect1 = glyph1->second.GetGlyphCoords();
                auto rect2 = glyph2->second.GetGlyphCoords();

                if( rect1.Intersects( rect2 ) )
                    return false;
            }
        }
    }

    return true;
}


// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.Font.Format.ttf", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/ELICEN.ttf", &init );
    REQUIRE_IS_VALID( font );

    auto numChars = FontLoaderData::DefaultCharacterSet().length();
    CHECK( font.Get()->GetLayout().Glyphs.size() == numChars);
    CHECK( font.Get()->GetLayout().Kerning.size() == numChars * numChars );

    REQUIRE( font.Get()->GetFontAtlas() != nullptr );
    CHECK( font.Get()->GetFontAtlas()->GetDescriptor().Height == 256 );
    CHECK( font.Get()->GetFontAtlas()->GetDescriptor().Width == 512 );

    CHECK( NoOverlappingGlyphs( font.Get()->GetLayout() ) );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.Font.Format.otf", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/ELICEN.otf", &init );
    REQUIRE_IS_VALID( font );

    auto numChars = FontLoaderData::DefaultCharacterSet().length();
    CHECK( font.Get()->GetLayout().Glyphs.size() == numChars );
    CHECK( font.Get()->GetLayout().Kerning.size() == numChars * numChars );

    REQUIRE( font.Get()->GetFontAtlas() != nullptr );
    CHECK( font.Get()->GetFontAtlas()->GetDescriptor().Height == 512 );
    CHECK( font.Get()->GetFontAtlas()->GetDescriptor().Width == 512 );

    CHECK( NoOverlappingGlyphs( font.Get()->GetLayout() ) );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.Font.Arial", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init );
    REQUIRE_IS_VALID( font );

    auto numChars = FontLoaderData::DefaultCharacterSet().length();
    CHECK( font.Get()->GetLayout().Glyphs.size() == numChars );
    CHECK( font.Get()->GetLayout().Kerning.size() == numChars * numChars );

    REQUIRE( font.Get()->GetFontAtlas() != nullptr );
    CHECK( font.Get()->GetFontAtlas()->GetDescriptor().Height == 256 );
    CHECK( font.Get()->GetFontAtlas()->GetDescriptor().Width == 256 );

    // Check a few letters  to confirm that there is no regression
    auto wGlyph = font.Get()->GetGlyph( L'W' );
    CHECK( wGlyph.Width == 15 );
    CHECK( wGlyph.Height == 12 );
    CHECK( wGlyph.AdvanceX == 15 );
    CHECK( wGlyph.AdvanceY == 0 );
    CHECK( wGlyph.BearingX == 0 );
    CHECK( wGlyph.BearingY == 12 );

    auto sGlyph = font.Get()->GetGlyph( Convert::FromString< std::wstring >( std::string_view( "Ś" ) ).Get()[ 0 ] );
    CHECK( sGlyph.Width == 10 );
    CHECK( sGlyph.Height == 15 );
    CHECK( sGlyph.AdvanceX == 11 );
    CHECK( sGlyph.AdvanceY == 0 );
    CHECK( sGlyph.BearingX == 0 );
    CHECK( sGlyph.BearingY == 15 );

    auto questGlyph = font.Get()->GetGlyph( L'?' );
    CHECK( questGlyph.Width == 9 );
    CHECK( questGlyph.Height == 12 );
    CHECK( questGlyph.AdvanceX == 9 );
    CHECK( questGlyph.AdvanceY == 0 );
    CHECK( questGlyph.BearingX == 0 );
    CHECK( questGlyph.BearingY == 12 );

    CHECK( NoOverlappingGlyphs( font.Get()->GetLayout() ) );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.SameFont.2Sizes", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init );
    REQUIRE_IS_VALID( font );

    FontLoaderData init2( 30 );

    auto font2 = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init2 );
    REQUIRE_IS_VALID( font );

    CHECK( font.Get()->GetFontAtlas() != font2.Get()->GetFontAtlas());
}

// ================================ //
// Single file can be used to create many different Assets. In case of fonts we can have different sizes of the same
// font loaded. ResourceManager doesn't have mechanisms for this, so FontLoader uses hack and never registers
// any font without internal path.
// The consequence is that second attempt to load asset won't fetch it from cache, but will call Loader again.
// Better mechanisms for this should be implemented in ResourceManager, but for now we must make sure that
// Loader can handle this situation correctly.
TEST_CASE( "GraphicAPI.Loaders.SameFont.SecondLoading", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init );
    REQUIRE_IS_VALID( font );

    FontLoaderData init2( 16 );

    auto font2 = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init2 );
    REQUIRE_IS_VALID( font );

    CHECK( font.Get() == font2.Get() );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.Correctness.ExitingAtlas", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    // Don't register FontCreator. Loader will create atlas, but won't be able to create FontAsset.
    // This way we are able to check how loader behaves when atals exists in the second pass.
    auto rm = CreateResourceManagerWithMocksAndDefaults();
    rm->RegisterLoader( std::make_shared< FreeTypeLoader >() );

    auto pm = rm->GetPathsManager();
    pm->RegisterAlias( "$(FontAssets)", "$(TestAssets)/fonts/" );

    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init );
    REQUIRE_INVALID( font );
    REQUIRE( std::regex_match( font.GetErrorReason(), std::regex( ".*Asset creator.*FontAsset.*not registered.*" ) ) );

    // Register creator so Loader will be able to create FontAsset this time,
    // but it must handle existing atlas correctly.
    rm->RegisterAssetCreator( FontCreator::CreateCreator() );

    auto font2 = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init );
    REQUIRE_IS_VALID( font2 );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.Loaders.PickFont", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithMocksAndDefaults();
    auto pm = rm->GetPathsManager();

    FontPicker picker;
    picker.RegisterSearchPath( "$(FontAssets)" );
    pm->RegisterAlias( "$(FontAssets)", "$(TestAssets)/fonts/" );

    rm->RegisterLoader( std::make_shared< FreeTypeLoader >( std::move( picker ) ) );
    rm->RegisterAssetCreator( FontCreator::CreateCreator() );

    ChooseFontLoadData init( "Arial", 16 );
    init.FontWeight = FontWeight::Normal;
    init.FontStyle = FontStyle::Normal;

    auto api = ResourceManagerAPI( rm.get() );
    auto font = api.Load< FontAsset >( "", &init );
    REQUIRE_IS_VALID( font );
    
    CHECK( font.Get()->GetMetadata().Family == "Arial" );
    CHECK( font.Get()->GetMetadata().Style == FontStyle::Normal );
    CHECK( font.Get()->GetMetadata().Weight == FontWeight::Regular );  // Regular is eqivalent to Normal
}
