#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestBlendingStateCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/PipelineStates/BlendingStateCreator.h"
#include "swGraphicAPI/Resources/PipelineStates/BlendingState.h"



using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.BlendingStateCreator.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	BlendingInfo init;
	init.EnableBlending = false;

	auto result = factory.CreateAsset( "::BlendingState::Opaque", TypeID::get< BlendingState >(), std::move( init ) );

	if( !result.IsValid() )
	{
		INFO( result.GetErrorReason() );
		REQUIRE( result.IsValid() == true );
	}

	REQUIRE( result.Get() != nullptr );
}