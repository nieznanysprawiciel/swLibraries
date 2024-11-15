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
	sw::fs::Path path( "assets/../wombat.jpg" );
	path.Normalize();

	CHECK( path == "wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.2Dots" )
{
	sw::fs::Path path( "some-dir/dir2/assets/../../wombat.jpg" );
	path.Normalize();

	CHECK( path == "some-dir/wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.2Dots.Separate.OnRoot" )
{
	sw::fs::Path path( "some-dir/../dir2/assets/../wombat.jpg" );
	path.Normalize();

	CHECK( path == "dir2/wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.2Dots.Separate" )
{
	sw::fs::Path path( "some-dir/dir2/../assets/../wombat.jpg" );
	path.Normalize();

	CHECK( path == "some-dir/wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.RamainingDots.1Dot" )
{
	sw::fs::Path path( "../wombat.jpg" );
	path.Normalize();

	CHECK( path == "../wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.RamainingDots.2Dots" )
{
	sw::fs::Path path( "../../wombat.jpg" );
	path.Normalize();

	CHECK( path == "../../wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.RamainingDots.2Dots.NameBetween" )
{
	sw::fs::Path path( "../dir/../wombat.jpg" );
	path.Normalize();

	CHECK( path == "../wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.RamainingDots.3Dots.NameBetween" )
{
	sw::fs::Path path( "../dir/../../wombat.jpg" );
	path.Normalize();

	CHECK( path == "../../wombat.jpg" );
}

// ================================ //
//
TEST_CASE( "Filesystem.Normalize.RamainingDots.DotsOnly" )
{
	sw::fs::Path path( "../../" );
	path.Normalize();

	CHECK( path == sw::fs::Path( "../../" ) );
}

