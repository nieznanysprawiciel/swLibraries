#include "swGraphicAPI/Tests/TestResourceManager/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestInputLayoutDescriptor.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"


using namespace sw;



// ================================ //
// 
TEST_CASE( "GraphicAPI.Resources.Layout.Descriptor.Offset", "[GraphicAPI]" )
{
    InputLayoutDescriptor init;
    init.AddEntry( AttributeSemantic::Position, ResourceFormat::RESOURCE_FORMAT_R32G32B32_FLOAT, 0 );
    init.AddEntry( AttributeSemantic::Texcoord, ResourceFormat::RESOURCE_FORMAT_R32G32_FLOAT, 12 );

    CHECK( init.GetEntries()[ 0 ].ByteOffset == 0 );
    CHECK( init.GetEntries()[ 1 ].ByteOffset == 12 );
}
