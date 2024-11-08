#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestArranger.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"
#include "swCommonLib/Common/Converters/Convert.h"

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"
#include "swGraphicAPI/Assets/TextAsset/Loader/FontAssetInitData.h"
#include "swGraphicAPI/Tests/TestText/Utils.h"
#include <swGraphicAPI/Assets/TextAsset/Text.h>


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.Text.Generate.TrickyTexts.SpacesAndNewlines", "[GraphicAPI][Text]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init );
    REQUIRE_IS_VALID( font );

    TextArranger arranger;
    auto geometry1 = arranger.GenerateGeometry( L"Hello World", font.Get(), false );
    REQUIRE_IS_VALID( geometry1 );

    auto geometry2 = arranger.GenerateGeometry( L"Hello World\n", font.Get(), false );
    REQUIRE_IS_VALID( geometry2 );

    auto geometry3 = arranger.GenerateGeometry( L"   Hello  World   ", font.Get(), false );
    REQUIRE_IS_VALID( geometry3 );

    auto geometry4 = arranger.GenerateGeometry( L"Hello World\n\n\n\n", font.Get(), false );
    REQUIRE_IS_VALID( geometry4 );

    auto geometry5 = arranger.GenerateGeometry( L"Hello World \n", font.Get(), false );
    REQUIRE_IS_VALID( geometry5 );

    auto geometry6 = arranger.GenerateGeometry( L"Hello World \n ", font.Get(), false );
    REQUIRE_IS_VALID( geometry6 );

    auto geometry7 = arranger.GenerateGeometry( L"Hello World \nHello World\nHello World\n", font.Get(), false );
    REQUIRE_IS_VALID( geometry7 );
}
