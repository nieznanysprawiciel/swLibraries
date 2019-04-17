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
TEST_CASE( "GraphicAPI.AssetPath.Constructor.FromConstChar", "[GraphicAPI]" )
{
	AssetPath path( "C://temp/newfolder/file.mesh::/materials/checker" );

	CHECK( path.GetFile() == "C://temp/newfolder/file.mesh" );
	CHECK( path.GetInternalPath() == "/materials/checker" );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetPath.Constructor.FromString", "[GraphicAPI]" )
{
	AssetPath path( std::string( "C://temp/newfolder/file.mesh::/materials/checker" ) );

	CHECK( path.GetFile() == "C://temp/newfolder/file.mesh" );
	CHECK( path.GetInternalPath() == "/materials/checker" );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetPath.FromString.BothPathsExist", "[GraphicAPI]" )
{
	auto nullablePath = AssetPath::FromString( "C://temp/newfolder/file.mesh::/materials/checker" );
	
	REQUIRE( nullablePath.IsValid() == true );
	auto path = nullablePath.Get();

	CHECK( path.GetFile() == "C://temp/newfolder/file.mesh" );
	CHECK( path.GetInternalPath() == "/materials/checker" );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetPath.FromString.OnlyFilePath", "[GraphicAPI]" )
{
	auto nullablePath = AssetPath::FromString( "C://temp/newfolder/file.mesh" );

	REQUIRE( nullablePath.IsValid() == true );
	auto path = nullablePath.Get();

	CHECK( path.GetFile() == "C://temp/newfolder/file.mesh" );
	CHECK( path.GetInternalPath() == "" );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetPath.FromString.OnlyInternalPath", "[GraphicAPI]" )
{
	auto nullablePath = AssetPath::FromString( "::/materials/checker" );

	REQUIRE( nullablePath.IsValid() == true );
	auto path = nullablePath.Get();

	CHECK( path.GetFile() == "" );
	CHECK( path.GetInternalPath() == "/materials/checker" );
}

// ================================ //
// 
TEST_CASE( "GraphicAPI.AssetPath.FromString.OnlyFilePathSeparatorOnEnd", "[GraphicAPI]" )
{
	auto nullablePath = AssetPath::FromString( "C://temp/newfolder/file.mesh::" );

	REQUIRE( nullablePath.IsValid() == true );
	auto path = nullablePath.Get();

	CHECK( path.GetFile() == "C://temp/newfolder/file.mesh" );
	CHECK( path.GetInternalPath() == "" );
}

// ================================ //
/// If there are two separators in string we threat everything after first separator as internal name.
TEST_CASE( "GraphicAPI.AssetPath.FromString.TwoSeparators", "[GraphicAPI]" )
{
	auto nullablePath = AssetPath::FromString( "C://temp/newfolder/file.mesh::materials::checker" );

	REQUIRE( nullablePath.IsValid() == true );
	auto path = nullablePath.Get();

	CHECK( path.GetFile() == "C://temp/newfolder/file.mesh" );
	CHECK( path.GetInternalPath() == "materials::checker" );
}


//====================================================================================//
//			Operators
//====================================================================================//

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
