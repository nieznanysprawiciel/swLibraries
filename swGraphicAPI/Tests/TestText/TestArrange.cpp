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


const std::wstring sLoremIpsum = L"Lorem ipsum is a dummy or placeholder text commonly used \
in graphic design, publishing, and web development to fill empty spaces in a layout that do \
not yet have content.\n\
Lorem ipsum is typically a corrupted version of De finibus bonorum et malorum, \
a 1st - century BC text by the Roman statesman and philosopher Cicero, with words altered, added, \
and removed to make it nonsensical and improper Latin. \
The first two words themselves are a truncation of dolorem ipsum( \"pain itself\" ).";



bool AlmostEqual( float a, float b )
{
    const float EPSILON = 0.00001f;
    return fabs( a - b ) < EPSILON;
}

bool PixelEqual( float a, float b )
{
    const float EPSILON = 0.6f;
    return fabs( a - b ) <= EPSILON;
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

    auto arranger = TextArranger::CreateFrom( font );
    arranger.Bounds = { 0.0f, 300.0f, 0.0f, -300.0f };
    arranger.WrapText = true;
    arranger.TextAlign = TextAlignment::Left;

    auto geometry = arranger.GenerateGeometryTextured( sLoremIpsum, font.Get(), false );
    REQUIRE_IS_VALID( geometry );

    auto& vertexBuf = geometry.Get().Verticies;
    CHECK( vertexBuf.ElementsCount() == 4 * sLoremIpsum.length() );

    Size numLeftAligned = 0;
    Size numRightAligned = 0;
    Size numRightOutside = 0;
    Size numLeftOutside = 0;
    Size numTopOutside = 0;

    for( auto idx = 0; idx < vertexBuf.ElementsCount(); idx++ )
    {
        if( TextArranger::IsWhitespace( sLoremIpsum[ idx / 4 ] ) )
            continue;

        auto& vertex = vertexBuf[ idx ].Position;
        numLeftAligned += PixelEqual( vertex.x, 0.5 ) ? 1 : 0;
        numRightOutside += vertex.x > arranger.Bounds.Right ? 1 : 0;
        numLeftOutside += vertex.x < arranger.Bounds.Left ? 1 : 0;
        numTopOutside += vertex.y > arranger.Bounds.Top ? 1 : 0;
    }

    CHECK( numLeftAligned == 30 );
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

    auto arranger = TextArranger::CreateFrom( font );
    arranger.Bounds = { 0.0f, 300.0f, 0.0f, -300.0f };
    arranger.WrapText = true;
    arranger.TextAlign = TextAlignment::Right;

    auto geometry = arranger.GenerateGeometryTextured( sLoremIpsum, font.Get(), false );
    REQUIRE_IS_VALID( geometry );

    auto& vertexBuf = geometry.Get().Verticies;
    CHECK( vertexBuf.ElementsCount() == 4 * sLoremIpsum.length() );

    Size numLeftAligned = 0;
    Size numRightAligned = 0;
    Size numRightOutside = 0;
    Size numLeftOutside = 0;
    Size numTopOutside = 0;

    for( auto idx = 0; idx < vertexBuf.ElementsCount(); idx++ )
    {
        if( TextArranger::IsWhitespace( sLoremIpsum[ idx / 4 ] ) )
            continue;

        auto& vertex = vertexBuf[ idx ].Position;
        numLeftAligned += PixelEqual( vertex.x, 0.5 ) ? 1 : 0;
        numRightAligned += PixelEqual( vertex.x, 299.5 ) ? 1 : 0;
        numRightOutside += vertex.x > arranger.Bounds.Right ? 1 : 0;
        numLeftOutside += vertex.x < arranger.Bounds.Left ? 1 : 0;
        numTopOutside += vertex.y > arranger.Bounds.Top ? 1 : 0;
    }

    CHECK( numLeftAligned == 0 );
    CHECK( numRightAligned == 30 );
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

    auto arranger = TextArranger::CreateFrom( font );
    arranger.Bounds = { 0.0f, 300.0f, 0.0f, -300.0f };
    arranger.WrapText = true;
    arranger.TextAlign = TextAlignment::Justify;

    auto geometry = arranger.GenerateGeometryTextured( sLoremIpsum, font.Get(), false );
    REQUIRE_IS_VALID( geometry );

    auto& vertexBuf = geometry.Get().Verticies;
    CHECK( vertexBuf.ElementsCount() == 4 * sLoremIpsum.length() );

    Size numLeftAligned = 0;
    Size numRightAligned = 0;
    Size numRightOutside = 0;
    Size numLeftOutside = 0;
    Size numTopOutside = 0;

    for( auto idx = 0; idx < vertexBuf.ElementsCount(); idx++ )
    {
        if( TextArranger::IsWhitespace( sLoremIpsum[ idx / 4 ] ) )
            continue;

        auto& vertex = vertexBuf[ idx ].Position;
        numLeftAligned += PixelEqual( vertex.x, 0.5 ) ? 1 : 0;
        numRightAligned += PixelEqual( vertex.x, 299.5 ) ? 1 : 0;
        numRightOutside += vertex.x > arranger.Bounds.Right ? 1 : 0;
        numLeftOutside += vertex.x < arranger.Bounds.Left ? 1 : 0;
        numTopOutside += vertex.y > arranger.Bounds.Top ? 1 : 0;
    }

    CHECK( numLeftAligned == 30 );
    CHECK( numRightAligned == 26 );     // We have 2 paragraphs, each last line is not justified.
    CHECK( numRightOutside == 0 );
    CHECK( numLeftOutside == 0 );
    CHECK( numTopOutside == 0 );
}
