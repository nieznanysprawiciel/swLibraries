#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestLayoutCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Shaders/LayoutCreator.h"
#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"



using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.LayoutCreator.Create", "[GraphicAPI]" )
{
	AssetsFactory factory;
	
	InputLayoutDescriptor init( L"::Layout" );
	init.AddEntry( AttributeSemantic::Position, ResourceFormat::RESOURCE_FORMAT_R32G32B32_FLOAT );


	auto result = factory.CreateAsset( "::Layout", TypeID::get< ShaderInputLayout >(), std::move( init ) );

	if( !result.IsValid() )
	{
		INFO( result.GetErrorReason() );
		REQUIRE( result.IsValid() == true );
	}

	REQUIRE( result.Get() != nullptr );
}
