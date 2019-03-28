#include "swCommonLib/External/Catch/catch.hpp"


#include "GraphicAPI.h"


// ================================ //
//
TEST_CASE( "GraphicAPI.DX11.Resources.BlendingState.Creation", "[GraphicAPI][Resources]" )
{
	auto& graphic = GetGraphic();

	sw::BlendingInfo blendDesc;
	blendDesc.EnableBlending = true;

	auto blendingState = graphic.RM->CreateBlendingState( L"TransparentBlendState", blendDesc );

	CHECK( blendingState != nullptr );
}
