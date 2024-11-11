#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestArrange.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Converters/Convert.h"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"
#include "swGraphicAPI/Assets/TextAsset/Loader/FontAssetInitData.h"
#include "swGraphicAPI/Tests/TestText/Utils.h"
#include <swGraphicAPI/Assets/TextAsset/Text.h>

using namespace sw;


const std::wstring sLoremIpsum = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. \
Pellentesque pulvinar est id vehicula rutrum. Aliquam luctus consectetur erat consectetur\
 pretium. Morbi nec mi nec quam feugiat pharetra a consequat magna. Sed ac dui nec felis \
iaculis ultricies. Vivamus a maximus massa. Duis feugiat justo quis eros vestibulum, non mattis\
 turpis tincidunt. Proin tristique, felis auctor placerat maximus, dui augue hendrerit risus, \
consectetur molestie nisl quam ac dui. Aliquam et erat arcu. Nam at nisl dapibus sem fringilla \
sodales sit amet in turpis. Vivamus interdum nunc vitae orci pretium aliquam. Vivamus ut \
consectetur diam. Duis dictum auctor accumsan. Morbi a nibh leo. Nam elementum lorem sit \
amet dignissim hendrerit.";

const std::wstring sLoremIpsumWithNewlines = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. \n\
Pellentesque pulvinar est id vehicula rutrum. Aliquam luctus consectetur erat consectetur\n\
 pretium. Morbi nec mi nec quam feugiat pharetra a consequat magna. Sed ac dui nec felis \n\
iaculis ultricies. Vivamus a maximus massa. Duis feugiat justo quis eros vestibulum, non mattis\n\
 turpis tincidunt. Proin tristique, felis auctor placerat maximus, dui augue hendrerit risus, \n\
consectetur molestie nisl quam ac dui. Aliquam et erat arcu. Nam at nisl dapibus sem fringilla \n\
sodales sit amet in turpis. Vivamus interdum nunc vitae orci pretium aliquam. Vivamus ut \n\
consectetur diam. Duis dictum auctor accumsan. Morbi a nibh leo. Nam elementum lorem sit \n\
amet dignissim hendrerit.";



bool AlmostEqual( float a, float b )
{
    const float EPSILON = 0.00001f;
    return fabs( a - b ) < EPSILON;
}

// ================================ //
//
TEST_CASE( "GraphicAPI.Text.Arrange.WithBounds.AlignLeft", "[GraphicAPI][Text]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init );
    REQUIRE_IS_VALID( font );

    TextArranger arranger;
    arranger.Bounds = { 0.0f, 200.0f, 0.0f, 200.0f };
    arranger.WrapText = true;
    arranger.TextAlign = TextAlignment::Left;

    auto geometry = arranger.GenerateGeometryTextured( sLoremIpsum, font.Get(), false );
    REQUIRE_IS_VALID( geometry );

    auto& vertexBuf = geometry.Get().Verticies;

    Size numLeftAligned = 0;
    Size numRightAligned = 0;
    Size numRightOutside = 0;
    Size numLeftOutside = 0;
    Size numTopOutside = 0;

    for( auto idx = 0; idx < vertexBuf.ElementsCount(); idx++ )
    {
        auto& vertex = vertexBuf[ idx ].Position;
        numLeftAligned += AlmostEqual( vertex.x, 0.0 ) ? 1 : 0;
        numRightAligned += AlmostEqual( vertex.x, 200.0 ) ? 1 : 0;
        numRightOutside += vertex.x > arranger.Bounds.Right ? 1 : 0;
        numLeftOutside += vertex.x < arranger.Bounds.Left ? 1 : 0;
        numTopOutside += vertex.y > arranger.Bounds.Top ? 1 : 0;
    }

    CHECK( numLeftAligned == 28 );
    CHECK( numRightAligned == 0 );
    CHECK( numRightOutside == 0 );
    CHECK( numLeftOutside == 0 );
    CHECK( numTopOutside == 0 );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.Text.Arrange.WithBounds.AlignRight", "[GraphicAPI][Text]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init );
    REQUIRE_IS_VALID( font );

    TextArranger arranger;
    arranger.Bounds = { 0.0f, 200.0f, 0.0f, 200.0f };
    arranger.WrapText = true;
    arranger.TextAlign = TextAlignment::Right;

    auto geometry = arranger.GenerateGeometryTextured( sLoremIpsum, font.Get(), false );
    REQUIRE_IS_VALID( geometry );

    auto& vertexBuf = geometry.Get().Verticies;

    Size numLeftAligned = 0;
    Size numRightAligned = 0;
    Size numRightOutside = 0;
    Size numLeftOutside = 0;
    Size numTopOutside = 0;

    for( auto idx = 0; idx < vertexBuf.ElementsCount(); idx++ )
    {
        auto& vertex = vertexBuf[ idx ].Position;
        numLeftAligned += AlmostEqual( vertex.x, 0.0 ) ? 1 : 0;
        numRightAligned += AlmostEqual( vertex.x, 200.0 ) ? 1 : 0;
        numRightOutside += vertex.x > arranger.Bounds.Right ? 1 : 0;
        numLeftOutside += vertex.x < arranger.Bounds.Left ? 1 : 0;
        numTopOutside += vertex.y > arranger.Bounds.Top ? 1 : 0;
    }

    CHECK( numLeftAligned == 0 );
    CHECK( numRightAligned == 28 );
    CHECK( numRightOutside == 0 );
    CHECK( numLeftOutside == 0 );
    CHECK( numTopOutside == 0 );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.Text.Arrange.WithBounds.Justify", "[GraphicAPI][Text]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init );
    REQUIRE_IS_VALID( font );

    TextArranger arranger;
    arranger.Bounds = { 0.0f, 200.0f, 0.0f, 200.0f };
    arranger.WrapText = true;
    arranger.TextAlign = TextAlignment::Justify;

    auto geometry = arranger.GenerateGeometryTextured( sLoremIpsum, font.Get(), false );
    REQUIRE_IS_VALID( geometry );

    auto& vertexBuf = geometry.Get().Verticies;

    Size numLeftAligned = 0;
    Size numRightAligned = 0;
    Size numRightOutside = 0;
    Size numLeftOutside = 0;
    Size numTopOutside = 0;

    for( auto idx = 0; idx < vertexBuf.ElementsCount(); idx++ )
    {
        auto& vertex = vertexBuf[ idx ].Position;
        numLeftAligned += AlmostEqual( vertex.x, 0.0 ) ? 1 : 0;
        numRightAligned += AlmostEqual( vertex.x, 200.0 ) ? 1 : 0;
        numRightOutside += vertex.x > arranger.Bounds.Right ? 1 : 0;
        numLeftOutside += vertex.x < arranger.Bounds.Left ? 1 : 0;
        numTopOutside += vertex.y > arranger.Bounds.Top ? 1 : 0;
    }

    CHECK( numLeftAligned == 28 );
    CHECK( numRightAligned == 28 );
    CHECK( numRightOutside == 0 );
    CHECK( numLeftOutside == 0 );
    CHECK( numTopOutside == 0 );
}
