#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestRasterizerStateCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/PipelineStates/RasterizerStateCreator.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.RasterizerStateCreator.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	RasterizerStateInfo init;

	auto result = factory.CreateAsset( "::/RasterizerState/Default", TypeID::get< RasterizerState >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );
}