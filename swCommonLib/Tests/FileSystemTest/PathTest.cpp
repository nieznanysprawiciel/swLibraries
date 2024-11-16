#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/System/Path.h"







TEST_CASE( "Path.ComparisionOperator" )
{
	sw::fs::Path reference( "assets/wombat.jpg" );
	sw::fs::Path difference( "assets/wombat2.jpg" );

	sw::fs::Path newPath( reference );

	CHECK( reference == newPath );
	CHECK( reference.String() == newPath.String() );
	CHECK( reference.WString() == newPath.WString() );

	CHECK( difference != newPath );
	CHECK( difference.String() != newPath.String() );
	CHECK( difference.WString() != newPath.WString() );
}


// ================================ //
// Path should return right result for examples from http://en.cppreference.com/w/cpp/experimental/fs/path/extension
TEST_CASE( "Path.AquireExtension" )
{
	sw::fs::Path path1( "/foo/bar.txt" );
	sw::fs::Path path2( "/foo/bar." );
	sw::fs::Path path3( "/foo/bar" );
	sw::fs::Path path4( "/foo/bar.txt/bar.cc" );
	sw::fs::Path path5( "/foo/bar.txt/bar." );
	sw::fs::Path path6( "/foo/bar.txt/bar" );
	sw::fs::Path path7( "/foo/." );
	sw::fs::Path path8( "/foo/.." );
	sw::fs::Path path9( "/foo/.hidden" );

	CHECK( path1.GetExtension() == ".txt" );
	CHECK( path2.GetExtension() == "." );
	CHECK( path3.GetExtension() == "" );
	CHECK( path4.GetExtension() == ".cc" );
	CHECK( path5.GetExtension() == "." );
	CHECK( path6.GetExtension() == "" );
	CHECK( path7.GetExtension() == "" );
	CHECK( path8.GetExtension() == "" );
	CHECK( path9.GetExtension() == "" );
}

// ================================ //
//
TEST_CASE( "Path.ChangeExtension" )
{
	sw::fs::Path path1( "/foo/bar.txt" );
	sw::fs::Path path2( "/foo/bar." );
	sw::fs::Path path3( "/foo/bar" );
	sw::fs::Path path4( "/foo/bar.txt/bar.cc" );
	sw::fs::Path path7( "/foo/." );
	sw::fs::Path path8( "/foo/.." );
	sw::fs::Path path9( "/foo/.hidden" );

	CHECK( path1.ChangeExtension( ".png" ) == "/foo/bar.png");
	CHECK( path2.ChangeExtension( ".png" ) == "/foo/bar.png" );
	CHECK( path3.ChangeExtension( ".png" ) == "/foo/bar.png" );
	CHECK( path4.ChangeExtension( ".png" ) == "/foo/bar.txt/bar.png" );

	CHECK( path7.ChangeExtension( ".png" ) == "/foo/." );
	CHECK( path8.ChangeExtension( ".png" ) == "/foo/.." );
	CHECK( path9.ChangeExtension( ".png" ) == "/foo/.hidden.png" );
}

// ================================ //
//
TEST_CASE( "Path.Combine" )
{
    sw::fs::Path path1( "/foo/bar" );
    sw::fs::Path path2( "/foo/bar/" );
    sw::fs::Path path3( "boa/bao" );
    sw::fs::Path path4( "" );
    sw::fs::Path path7( "/foo/." );
    sw::fs::Path path8( "/foo/.." );
    sw::fs::Path path9( "/foo/.hidden" );

    CHECK( path1 / path3 == "/foo/bar/boa/bao" );
    CHECK( path1 / path4 == "/foo/bar/" );	// Because we add empty path `bar` is treated as directory.
    CHECK( path4 / path3 == "boa/bao" );
    CHECK( path7 / path3 == "/foo/./boa/bao" );
    CHECK( path8 / path3 == "/foo/../boa/bao" );
    CHECK( path7 / path4 == "/foo/./" );
    CHECK( path8 / path4 == "/foo/../" );
    CHECK( path2 / path3 == "/foo/bar/boa/bao" );
}

// ================================ //
//
TEST_CASE( "Path.ForbiddenChars" )
{
    sw::fs::Path path1( "/foo:blaa" );
    sw::fs::Path path2( "/foo::blaa" );
    sw::fs::Path path3( "/foo?blaa=3" );

	CHECK( path1 == "/foo:blaa" );
    CHECK( path2 == "/foo::blaa" );
    CHECK( path3 == "/foo?blaa=3" );
}

