/**
@file TestNormalizePath.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/System/Path.h"




// ================================ //
//
TEST_CASE( "Filesystem.Normalize.1Dot" )
{
	filesystem::Path path( "assets/../wombat.jpg" );
	path.Normalize();

	CHECK( path == "wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.2Dots" )
{
	filesystem::Path path( "some-dir/dir2/assets/../../wombat.jpg" );
	path.Normalize();

	CHECK( path == "some-dir/wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.2Dots.Separate.OnRoot" )
{
	filesystem::Path path( "some-dir/../dir2/assets/../wombat.jpg" );
	path.Normalize();

	CHECK( path == "dir2/wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.2Dots.Separate" )
{
	filesystem::Path path( "some-dir/dir2/../assets/../wombat.jpg" );
	path.Normalize();

	CHECK( path == "some-dir/wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.RamainingDots.1Dot" )
{
	filesystem::Path path( "../wombat.jpg" );
	path.Normalize();

	CHECK( path == "../wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.RamainingDots.2Dots" )
{
	filesystem::Path path( "../../wombat.jpg" );
	path.Normalize();

	CHECK( path == "../../wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.RamainingDots.2Dots.NameBetween" )
{
	filesystem::Path path( "../dir/../wombat.jpg" );
	path.Normalize();

	CHECK( path == "../wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.RamainingDots.3Dots.NameBetween" )
{
	filesystem::Path path( "../dir/../../wombat.jpg" );
	path.Normalize();

	CHECK( path == "../../wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.RamainingDots.DotsOnly" )
{
	filesystem::Path path( "../../" );
	path.Normalize();

	CHECK( path == "../../" );
}

