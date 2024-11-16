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
TEST_CASE( "GraphicAPI.Loaders.Font.FontPicker.Metadata", "[GraphicAPI][FontLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontPicker picker;
    picker.RegisterSearchPath( "$(FontAssets)" );

    auto meta = picker.GetFontMetadata( rm->GetPathsManager(), "$(FontAssets)/arial.ttf" );
    REQUIRE_IS_VALID( meta );
    CHECK( meta.Get().Metadata.Family == "Arial" );
    CHECK( meta.Get().Metadata.Style == FontStyle::Normal );
    CHECK( meta.Get().Metadata.Weight == FontWeight::Regular );

    auto meta2 = picker.GetFontMetadata( rm->GetPathsManager(), "$(FontAssets)/ELICEN.ttf" );
    REQUIRE( meta2.IsValid() );
    CHECK( meta2.Get().Metadata.Family == "ELICEN" );
    CHECK( meta2.Get().Metadata.Style == FontStyle::Normal );
    CHECK( meta2.Get().Metadata.Weight == FontWeight::Regular );
}

// ================================ //
// Test checks if FontPicker will be able to handle incorrect files in provided directories.
TEST_CASE( "GraphicAPI.Loaders.Font.FontPicker.ListFonts", "[GraphicAPI][FontLoader]" )
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
TEST_CASE( "GraphicAPI.Loaders.Font.FontPicker.Metadata.IncorrectFiles", "[GraphicAPI][FontLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontPicker picker;
    picker.RegisterSearchPath( "$(FontAssets)" );

    auto meta = picker.GetFontMetadata( rm->GetPathsManager(), "$(FontAssets)/not-font.txt" );
    REQUIRE_INVALID( meta );

    meta = picker.GetFontMetadata( rm->GetPathsManager(), "$(FontAssets)/incorrect.ttf" );
    REQUIRE_INVALID( meta );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.Loaders.Font.FontPicker.ListFonts.MultiVariant", "[GraphicAPI][FontLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontPicker picker;
    picker.RegisterSearchPath( "$(FontAssets)" );
    picker.RegisterSearchPath( "$(FontAssets)/multi-variant" );

    auto list = picker.ListFonts( rm->GetPathsManager() );
    REQUIRE_IS_VALID( list );

    auto& files = list.Get();
    CHECK( files.size() == 6 );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.Loaders.Font.FontPicker.ChooseFont", "[GraphicAPI][FontLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontPicker picker;
    picker.RegisterSearchPath( "$(FontAssets)" );
    picker.RegisterSearchPath( "$(FontAssets)/multi-variant" );

    auto chosen = picker.ChooseFontFile( rm->GetPathsManager(), "Source Sans Pro", FontWeight::Black, FontStyle::Normal, true );
    REQUIRE_IS_VALID( chosen );
    CHECK( chosen.Get().Metadata.Family == "Source Sans Pro" );
    CHECK( chosen.Get().Metadata.Weight == FontWeight::Black );
    CHECK( chosen.Get().Metadata.Style == FontStyle::Normal );
    
    chosen = picker.ChooseFontFile( rm->GetPathsManager(), "Source Sans Pro", FontWeight::Light, FontStyle::Italic, true );
    REQUIRE_INVALID( chosen );

    chosen = picker.ChooseFontFile( rm->GetPathsManager(), "Source Sans Pro", FontWeight::Light, FontStyle::Italic, false );
    REQUIRE_IS_VALID( chosen );
    CHECK( chosen.Get().Metadata.Weight == FontWeight::ExtraLight );
    CHECK( chosen.Get().Metadata.Style == FontStyle::Italic );

    chosen = picker.ChooseFontFile( rm->GetPathsManager(), "Source Sans Pro", FontWeight::SemiBold, FontStyle::Italic, false );
    REQUIRE_IS_VALID( chosen );
    CHECK( chosen.Get().Metadata.Weight == FontWeight::SemiBold );
    CHECK( chosen.Get().Metadata.Style == FontStyle::Normal );

    chosen = picker.ChooseFontFile( rm->GetPathsManager(), "Source Sans Pro", FontWeight::Black, FontStyle::Italic, false );
    REQUIRE_IS_VALID( chosen );
    CHECK( chosen.Get().Metadata.Weight == FontWeight::Black );
    CHECK( chosen.Get().Metadata.Style == FontStyle::Normal );

    chosen = picker.ChooseFontFile( rm->GetPathsManager(), "Source Sans Pro", FontWeight::Normal, FontStyle::Italic, false );
    REQUIRE_IS_VALID( chosen );
    CHECK( chosen.Get().Metadata.Weight == FontWeight::ExtraLight );
    CHECK( chosen.Get().Metadata.Style == FontStyle::Italic );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.Loaders.Font.FontPicker.ParseStyle", "[GraphicAPI][FontLoader]" )
{
    auto result = FontPicker::ParseFontStyle( "Regular" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Normal );

    result = FontPicker::ParseFontStyle( "Black Italic" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Italic );

    result = FontPicker::ParseFontStyle( "Black" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Normal );

    result = FontPicker::ParseFontStyle( "Bold Italic" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Italic );

    result = FontPicker::ParseFontStyle( "Bold" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Normal );

    result = FontPicker::ParseFontStyle( "ExtraLight" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Normal );

    result = FontPicker::ParseFontStyle( "Italic" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Italic );

    result = FontPicker::ParseFontStyle( "Light Italic" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Italic );

    result = FontPicker::ParseFontStyle( "Light" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Normal );

    result = FontPicker::ParseFontStyle( "Semibold Italic" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Italic );

    result = FontPicker::ParseFontStyle( "Semibold" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Normal );

    result = FontPicker::ParseFontStyle( "Condensed Bold" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Normal );

    result = FontPicker::ParseFontStyle( "Condensed Bold Italic" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontStyle::Italic );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.Loaders.Font.FontPicker.ParseWeight", "[GraphicAPI][FontLoader]" )
{
    auto result = FontPicker::ParseFontWeight( "Regular" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontWeight::Regular );

    result = FontPicker::ParseFontWeight( "Black Italic" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontWeight::Black );

    result = FontPicker::ParseFontWeight( "Black" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontWeight::Black );

    result = FontPicker::ParseFontWeight( "Bold Italic" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontWeight::Bold );

    result = FontPicker::ParseFontWeight( "Bold" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontWeight::Bold );

    result = FontPicker::ParseFontWeight( "ExtraLight" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontWeight::ExtraLight );

    result = FontPicker::ParseFontWeight( "Italic" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontWeight::Normal );

    result = FontPicker::ParseFontWeight( "Light Italic" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontWeight::Light );

    result = FontPicker::ParseFontWeight( "Light" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontWeight::Light );

    result = FontPicker::ParseFontWeight( "Semibold Italic" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontWeight::SemiBold );

    result = FontPicker::ParseFontWeight( "Semibold" );
    REQUIRE_IS_VALID( result );
    CHECK( result.Get() == FontWeight::SemiBold );
}
