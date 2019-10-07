#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestBlendingState.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swGraphicAPI/MockAssets/GraphicAPI.h"


// ================================ //
//
TEST_CASE( "GraphicAPI.DX11.Resources.BlendingState.Creation", "[GraphicAPI][Resources]" )
{
	auto& graphic = GetGraphic();

	sw::BlendingInfo blendDesc;
	blendDesc.EnableBlending = true;

	auto blendingState = graphic.RMApi.CreateBlendingState( "::TransparentBlendState", blendDesc );

	CHECK( blendingState != nullptr );
}
