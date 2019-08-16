#include "swCommonLib/External/Catch/catch.hpp"
/**
@file LoadPath.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/PathTranslators/LoadPath.h"
#include "swGraphicAPI/MockAssets/Utils.h"


using namespace sw;


// ================================ //
// Constructor translates path using PathsManager from parameters.
TEST_CASE( "GraphicAPI.ResourceManager.PathAliases.LoadPath.Constructor", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	auto path = AssetPath::FromString( "$(MocksDir)/example.mock" );
	auto loadPath = LoadPath( path, rm->GetPathsManager() );

	CHECK( loadPath.GetFileOriginal() == "$(MocksDir)/example.mock" );
	CHECK( loadPath.GetFileTranslated() == filesystem::Path::WorkingDirectory().GetParent() / "TestAssets/mock/example.mock" );
}
