#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestRasterizerStateCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/PipelineStates/RasterizerStateCreator.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"



using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.RasterizerStateCreator.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	RasterizerStateInfo init;

	auto result = factory.CreateAsset( "::RasterizerState::Default", TypeID::get< RasterizerState >(), std::move( init ) );

	if( !result.IsValid() )
	{
		INFO( result.GetErrorReason() );
		REQUIRE( result.IsValid() == true );
	}

	REQUIRE( result.Get() != nullptr );
}