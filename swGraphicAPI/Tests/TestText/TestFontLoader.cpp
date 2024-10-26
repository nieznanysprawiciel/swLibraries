#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestSWMaterialLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"
#include "swGraphicAPI/Tests/TestText/Utils.h"


using namespace sw;


//====================================================================================//
//			Negative tests	
//====================================================================================//

// ================================ //
// 
TEST_CASE( "GraphicAPI.Loaders.FontLoader.Basic", "[GraphicAPI][FontLoader][FreeTypeLoader]" )
{
    auto rm = CreateResourceManagerWithFonts();
    auto api = ResourceManagerAPI( rm.get() );

    auto material = api.Load< FontAsset >( "$(FontAssets)/no-header.swmat", nullptr );
    REQUIRE( !material.IsValid() );
}
