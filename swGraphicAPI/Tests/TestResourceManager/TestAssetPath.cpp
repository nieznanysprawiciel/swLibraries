#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestAssetPath.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"


using namespace sw;


// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetPath.Constructor.FromPaths", "[GraphicAPI]" )
{
	AssetPath path( "C://temp/newfolder/file.mesh", "materials/checker" );

	CHECK( path.GetFile() == "C://temp/newfolder/file.mesh" );
	CHECK( path.GetInternalPath() == "materials/checker" );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetPath.Operators.EqualPaths", "[GraphicAPI]" )
{
	AssetPath path1( "C://temp/newfolder/file.mesh", "materials/checker" );
	AssetPath path2( "C://temp/newfolder/file.mesh", "materials/checker" );

	CHECK( ( path1 == path2 ) == true );
	CHECK( ( path1 != path2 ) == false );
	CHECK( ( path1 < path2 ) == false );
	CHECK( ( path1 > path2 ) == false );
	CHECK( ( path1 <= path2 ) == true );
	CHECK( ( path1 >= path2 ) == true );

	CHECK( ( path2 == path1 ) == true );
	CHECK( ( path2 != path1 ) == false );
	CHECK( ( path2 < path1 ) == false );
	CHECK( ( path2 > path1 ) == false );
	CHECK( ( path2 <= path1 ) == true );
	CHECK( ( path2 >= path1 ) == true );
}


// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetPath.Operators.FilePathDiffers", "[GraphicAPI]" )
{
	AssetPath path1( "C://temp/newfolder/fila.mesh", "materials/checker" );
	AssetPath path2( "C://temp/newfolder/file.mesh", "materials/checker" );

	CHECK( ( path1 == path2 ) == false );
	CHECK( ( path1 != path2 ) == true );
	CHECK( ( path1 < path2 ) == true );
	CHECK( ( path1 > path2 ) == false );
	CHECK( ( path1 <= path2 ) == true );
	CHECK( ( path1 >= path2 ) == false );

	CHECK( ( path2 == path1 ) == false );
	CHECK( ( path2 != path1 ) == true );
	CHECK( ( path2 < path1 ) == false );
	CHECK( ( path2 > path1 ) == true );
	CHECK( ( path2 <= path1 ) == false );
	CHECK( ( path2 >= path1 ) == true );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetPath.Operators.InternalPathDiffers", "[GraphicAPI]" )
{
	AssetPath path1( "C://temp/newfolder/file.mesh", "materials/checkerA" );
	AssetPath path2( "C://temp/newfolder/file.mesh", "materials/checkerB" );

	CHECK( ( path1 == path2 ) == false );
	CHECK( ( path1 != path2 ) == true );
	CHECK( ( path1 < path2 ) == true );
	CHECK( ( path1 > path2 ) == false );
	CHECK( ( path1 <= path2 ) == true );
	CHECK( ( path1 >= path2 ) == false );

	CHECK( ( path2 == path1 ) == false );
	CHECK( ( path2 != path1 ) == true );
	CHECK( ( path2 < path1 ) == false );
	CHECK( ( path2 > path1 ) == true );
	CHECK( ( path2 <= path1 ) == false );
	CHECK( ( path2 >= path1 ) == true );
}
