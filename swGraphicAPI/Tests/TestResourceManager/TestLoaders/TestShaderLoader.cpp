#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestShaderLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/nResourceManager.h"

#include "swGraphicAPI/Tests/TestResourceManager/Utils/Utils.h"

#include "swCommonLib/Common/Exceptions/Common/FileNotFoundException.h"


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.ShaderLoader.FileDoesntExists", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocksAndDefaults();

	auto resource = rm->LoadGeneric( "../TestAssets/shaders/example-notexists.vsh::main", nullptr, TypeID::get< VertexShader >() );
	REQUIRE( resource.IsValid() == false );

	CHECK( resource.GetError() != nullptr );
	CHECK( resource.GetError()->get_type() == TypeID::get< FileNotFoundException >() );
}
