#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestFontPicker.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <algorithm>

#include "swCommonLib/Common/Converters/Convert.h"
#include "swCommonLib\TestUtils\CatchUtils\ExtendedMacros.h"

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"
#include "swGraphicAPI/Assets/TextAsset/Loader/FontPicker.h"
#include "swGraphicAPI/Tests/TestText/Utils.h"

using namespace sw;


// ================================ //
//
TEST_CASE( "GraphicAPI.Loaders.Font.FontPicker.Metadata", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontPicker picker;
    picker.RegisterSearchPath( "$(FontAssets)" );

    auto meta = picker.FontMetadata( rm->GetPathsManager(), "$(FontAssets)/arial.ttf" );
    REQUIRE_IS_VALID( meta );
    CHECK( meta.Get().Metadata.Family == "Arial" );
    CHECK( meta.Get().Style == FontStyle::Normal );
    CHECK( meta.Get().Weight == FontWeight::Normal );

    auto meta2 = picker.FontMetadata( rm->GetPathsManager(), "$(FontAssets)/ELICEN.ttf" );
    REQUIRE( meta2.IsValid() );
    CHECK( meta2.Get().Metadata.Family == "ELICEN" );
    CHECK( meta2.Get().Style == FontStyle::Normal );
    CHECK( meta2.Get().Weight == FontWeight::Normal );
}

// ================================ //
// Test checks if FontPicker will be able to handle incorrect files in provided directories.
TEST_CASE( "GraphicAPI.Loaders.Font.FontPicker.ListFonts", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontPicker picker;
    picker.RegisterSearchPath( "$(FontAssets)" );

    auto list = picker.ListFonts( rm->GetPathsManager() );
    REQUIRE_IS_VALID( list );

    auto& files = list.Get();
    CHECK( files.size() == 3 );
    
    CHECK( std::find_if( files.begin(), files.end(), []( auto& file ) { return file.Metadata.Family == "Arial"; } )
           != files.end() );
    CHECK( std::find_if( files.begin(), files.end(), []( auto& file ) { return file.Metadata.Family == "ELICEN"; } )
           != files.end() );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.Loaders.Font.FontPicker.Metadata.IncorrectFiles", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontPicker picker;
    picker.RegisterSearchPath( "$(FontAssets)" );

    auto meta = picker.FontMetadata( rm->GetPathsManager(), "$(FontAssets)/not-font.txt" );
    REQUIRE_INVALID( meta );

    meta = picker.FontMetadata( rm->GetPathsManager(), "$(FontAssets)/incorrect.ttf" );
    REQUIRE_INVALID( meta );
}
