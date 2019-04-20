#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestLoadingResult.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/Loaders/LoadingResult.h"



namespace sw
{

// ================================ //
//
LoadingResult		ConstructFromString					( std::string error )
{	return error;	}

// ================================ //
// Test checks if LoadingResult works with expected syntax
// when returning value from function.
TEST_CASE( "GraphicAPI.Loading.LoadingResult.Constructor.ErrorString", "[GraphicAPI]" )
{
	auto result = ConstructFromString( "Error message" );
	
	REQUIRE( result.Assets.IsValid() == false );
	CHECK( result.Assets.GetError() != nullptr );
	CHECK( result.Assets.GetErrorReason() == "Error message" );
	CHECK( result.Warnings == nullptr );
}

// ================================ //
//
LoadingResult		ConstructFromStringAndWarning		( std::string error, ExceptionPtr warning )
{
	return { error, warning };
}

// ================================ //
// Test checks if LoadingResult works with expected syntax
// when returning value from function.
TEST_CASE( "GraphicAPI.Loading.LoadingResult.Constructor.ErrorStringAndWarning", "[GraphicAPI]" )
{
	auto result = ConstructFromStringAndWarning( "Error message", std::make_shared< RuntimeException >( "Warning" ) );

	REQUIRE( result.Assets.IsValid() == false );
	CHECK( result.Assets.GetError() != nullptr );
	CHECK( result.Assets.GetErrorReason() == "Error message" );

	REQUIRE( result.Warnings != nullptr );
	CHECK( result.Warnings->ErrorMessage() == "Warning" );
}

// ================================ //
//
LoadingResult		ConstructFromException		( ExceptionPtr error )
{
	return error;
}

// ================================ //
// Test checks if LoadingResult works with expected syntax
// when returning value from function.
TEST_CASE( "GraphicAPI.Loading.LoadingResult.Constructor.Exception", "[GraphicAPI]" )
{
	auto result = ConstructFromException( std::make_shared< RuntimeException >( "Error message" ) );

	REQUIRE( result.Assets.IsValid() == false );
	CHECK( result.Assets.GetError() != nullptr );
	CHECK( result.Assets.GetErrorReason() == "Error message" );
	CHECK( result.Warnings == nullptr );
}

// ================================ //
//
LoadingResult		ConstructFromExceptions		( ExceptionPtr error, ExceptionPtr warning )
{
	return { error, warning };
}

// ================================ //
// Test checks if LoadingResult works with expected syntax
// when returning value from function.
TEST_CASE( "GraphicAPI.Loading.LoadingResult.Constructor.ExceptionAndWarning", "[GraphicAPI]" )
{
	auto result = ConstructFromExceptions( std::make_shared< RuntimeException >( "Error message" ), std::make_shared< RuntimeException >( "Warning" ) );

	REQUIRE( result.Assets.IsValid() == false );
	CHECK( result.Assets.GetError() != nullptr );
	CHECK( result.Assets.GetErrorReason() == "Error message" );

	REQUIRE( result.Warnings != nullptr );
	CHECK( result.Warnings->ErrorMessage() == "Warning" );
}




}	// sw


