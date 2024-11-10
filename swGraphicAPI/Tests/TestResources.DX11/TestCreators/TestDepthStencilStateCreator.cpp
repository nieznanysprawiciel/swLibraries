#include "swGraphicAPI/Tests/TestResources.DX11/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestDepthStencilStateCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/PipelineStates/DepthStencilStateCreator.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"



using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.DX11.DepthStencilStateCreator.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	DepthStencilInfo init;

	auto result = factory.CreateAsset( "::/DepthStencilState/Opaque", TypeID::get< DepthStencilState >(), std::move( init ) );
	REQUIRE_IS_VALID( result );

	REQUIRE( result.Get() != nullptr );
}