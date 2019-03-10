#include "swCommonLib/External/Catch/catch.hpp"


#include "GraphicAPI.h"


// ================================ //
//
TEST_CASE( "GraphicAPI.Resources.BlendingState.Creation", "[GraphicAPI][Resources]" )
{
	auto& graphic = GetGraphic();

	sw::BlendingInfo blendDesc;
	blendDesc.EnableBlending = true;

	auto blendingState = graphic.RM->CreateBlendingState( L"TransparentBlendState", blendDesc );

	CHECK( blendingState != nullptr );
}
