#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestSWMaterialLoader.cpp
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
TEST_CASE( "GraphicAPI.Loaders.Font.Loader.FontFormat.ttf", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/ELICEN.ttf", &init );
    REQUIRE_IS_VALID( font );

    auto numChars = FontLoaderData::DefaultCharacterSet().length();
    CHECK( font.Get()->GetGlyphs().size() == numChars );
    CHECK( font.Get()->GetKerning().size() == numChars * numChars );
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
    CHECK( font.Get()->GetGlyphs().size() == numChars );
    CHECK( font.Get()->GetKerning().size() == numChars * numChars );
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
    CHECK( font.Get()->GetGlyphs().size() == numChars );
    CHECK( font.Get()->GetKerning().size() == numChars * numChars );
}
