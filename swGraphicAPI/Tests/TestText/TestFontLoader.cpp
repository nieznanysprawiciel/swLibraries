#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestSWMaterialLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"
#include "swGraphicAPI/Assets/TextAsset/Loader/FontAssetInitData.h"
#include "swGraphicAPI/Tests/TestText/Utils.h"


using namespace sw;


//====================================================================================//
//			Negative tests	
//====================================================================================//

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.Font.Loader.Basic", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    FontLoaderData init( 16 );

    auto font = api.Load< FontAsset >( "$(FontAssets)/ELICEN.ttf", &init );
    REQUIRE( font.IsValid() );
}
