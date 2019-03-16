#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestDepthStencilStateCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/PipelineStates/DepthStencilStateCreator.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"



using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.DepthStencilStateCreator.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	DepthStencilInfo init;

	auto result = factory.CreateAsset( "::DepthStencilState::Opaque", TypeID::get< DepthStencilState >(), std::move( init ) );

	if( !result.IsValid() )
	{
		INFO( result.GetErrorReason() );
		REQUIRE( result.IsValid() == true );
	}

	REQUIRE( result.Get() != nullptr );
}