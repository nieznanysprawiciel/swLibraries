#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestFontLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib\TestUtils\CatchUtils\ExtendedMacros.h"

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
TEST_CASE( "GraphicAPI.Loaders.Font.Loader.FontFormat.ttf", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
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
TEST_CASE( "GraphicAPI.Loaders.Font.Loader.FontFormat.otf", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
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
TEST_CASE( "GraphicAPI.Loaders.Font.Loader.Font.Arial", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
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

    auto sGlyph = font.Get()->GetGlyph( L'Œ' );
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
