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
TEST_CASE( "GraphicAPI.Text.Generate.Buffers", "[GraphicAPI][Text]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/arial.ttf", &init );
    REQUIRE_IS_VALID( font );

    TextArranger arranger;
    auto geometry = arranger.GenerateGeometry( L"Hello World", font.Get(), false );
    REQUIRE_IS_VALID( geometry );
}
