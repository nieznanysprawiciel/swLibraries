#include "swGraphicAPI/Tests/TestResourceManager/stdafx.h"
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

// ================================ //
// Translation should normalize path.
TEST_CASE( "GraphicAPI.ResourceManager.PathAliases.LoadPath.Normalization", "[GraphicAPI]" )
{
	auto rm = CreateResourceManagerWithMocks();

	auto path = AssetPath::FromString( "$(MocksDir)/../example.mock" );
	auto loadPath = LoadPath( path, rm->GetPathsManager() );

	CHECK( loadPath.GetFileOriginal() == "$(MocksDir)/../example.mock" );
	CHECK( loadPath.GetFileTranslated() == filesystem::Path::WorkingDirectory().GetParent() / "TestAssets/example.mock" );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.ResourceManager.PathAliases.LoadPath.TranslateEmpty", "[GraphicAPI]" )
{
    auto rm = CreateResourceManagerWithMocks();

    auto path = AssetPath::FromString( "::example/TranslateEmpty" );
    auto loadPath = LoadPath( path, rm->GetPathsManager() );

    CHECK( loadPath.GetFileOriginal() == "" );
    CHECK( loadPath.GetFileTranslated().String() == "" );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.ResourceManager.PathAliases.LoadPath.TranslateRelative", "[GraphicAPI]" )
{
    auto rm = CreateResourceManagerWithMocks();

    auto path = AssetPath::FromString( "TestAssets/example.mock" );
    auto loadPath = LoadPath( path, rm->GetPathsManager() );

    CHECK( loadPath.GetFileOriginal() == "TestAssets/example.mock" );
    CHECK( loadPath.GetFileTranslated() == ( filesystem::Path::WorkingDirectory() / "TestAssets/example.mock" ).String() );
}

