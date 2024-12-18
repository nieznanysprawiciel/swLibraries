#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestNullable.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"
#include "swCommonLib/Common/Exceptions/ExceptionsList.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/fmt.h"


#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Mammals/Dog.h"


using namespace sw;


//====================================================================================//
//			Helpers for tests	
//====================================================================================//

// ================================ //
//
Nullable< Dog* >			CreateDog		( bool valid )
{
	if( valid )
		return new Dog( "TestDog", 15, "DontKnowAnyRaces" );
	else
		return "Something wrong...";
}

// ================================ //
//
Nullable< std::shared_ptr< Dog > >			CreateDogPtr		( bool valid )
{
	if( valid )
		return std::make_shared< Dog >( "TestDog", 15, "DontKnowAnyRaces" );
	else
		return "Something wrong...";
}



//====================================================================================//
//			Tests	
//====================================================================================//

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Nullable.CanReturnFromFunction", "[Nullable]" )
{
	auto dog = CreateDog( true );

	REQUIRE( dog.IsValid() == true );
	CHECK( dog.Get()->GetName() == "TestDog" );
	CHECK( dog.Get()->GetAge() == 15 );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Nullable.CanReturnFromFunction.Error", "[Nullable]" )
{
	auto dog = CreateDog( false );

	REQUIRE( dog.IsValid() == false );
	CHECK( dog.GetErrorReason() == "Something wrong..." );
	CHECK( dog.GetError() != nullptr );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Nullable.DestructibleObject", "[Nullable]" )
{
	auto dog = CreateDogPtr( true );

	REQUIRE( dog.IsValid() == true );
	CHECK( dog.Get()->GetName() == "TestDog" );
	CHECK( dog.Get()->GetAge() == 15 );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Nullable.DestructibleObject.Error", "[Nullable]" )
{
	auto dog = CreateDogPtr( false );

	REQUIRE( dog.IsValid() == false );
	CHECK( dog.GetErrorReason() == "Something wrong..." );
	CHECK( dog.GetError() != nullptr );
}

// ================================ //
// Passing string to constructor should create RuntimeException with error message.
TEST_CASE( "Common.Helpers.Exceptions.Nullable.Error.CreateFromString", "[Nullable]" )
{
	Nullable< Dog* > nullableDog( "Something wrong..." );

	REQUIRE( nullableDog.IsValid() == false );
	CHECK( nullableDog.GetErrorReason() == "Something wrong..." );
	CHECK( nullableDog.GetError() != nullptr );
}

// ================================ //
// Passing ExceptionPtr to constructor should create invalid Nullable.
TEST_CASE( "Common.Helpers.Exceptions.Nullable.Error.CreateFromException", "[Nullable]" )
{
	Nullable< Dog* > nullableDog( std::make_shared< RuntimeException >( "Something wrong..." ) );

	REQUIRE( nullableDog.IsValid() == false );
	CHECK( nullableDog.GetErrorReason() == "Something wrong..." );
	CHECK( nullableDog.GetError() != nullptr );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Nullable.RValueCast", "[Nullable]" )
{
	Nullable< Dog* > nullableDog( new Dog( "TestDog", 15, "DontKnowAnyRaces" ) );
	Nullable< Animal* > nullableAnimal( std::move( nullableDog ) );

	REQUIRE( nullableAnimal.IsValid() == true );
	CHECK( nullableAnimal.Get()->GetName() == "TestDog" );
	CHECK( nullableAnimal.Get()->GetAge() == 15 );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Nullable.RValueCast.Exception", "[Nullable]" )
{
	Nullable< Dog* > nullableDog( "Something wrong..." );
	Nullable< Animal* > nullableAnimal( std::move( nullableDog ) );

	REQUIRE( nullableAnimal.IsValid() == false );
	CHECK( nullableAnimal.GetErrorReason() == "Something wrong..." );
	CHECK( nullableAnimal.GetError() != nullptr );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Nullable.Move", "[Nullable]" )
{
	Nullable< Dog* > nullableDog( new Dog( "TestDog", 15, "DontKnowAnyRaces" ) );
	Nullable< Animal* > nullableAnimal = nullableDog.Move< Animal* >();

	REQUIRE( nullableAnimal.IsValid() == true );
	CHECK( nullableAnimal.Get()->GetName() == "TestDog" );
	CHECK( nullableAnimal.Get()->GetAge() == 15 );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Nullable.Move.Exception", "[Nullable]" )
{
	Nullable< Dog* > nullableDog( "Something wrong..." );
	Nullable< Animal* > nullableAnimal = nullableDog.Move< Animal* >();

	REQUIRE( nullableAnimal.IsValid() == false );
	CHECK( nullableAnimal.GetErrorReason() == "Something wrong..." );
	CHECK( nullableAnimal.GetError() != nullptr );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Nullable.MapErr", "[Nullable]" )
{
    auto mappedErr = Nullable< Dog* >( "Something wrong..." ).MapErr( []( auto e ) { return fmt::format( "Failure: {}", e ); } );

    REQUIRE( mappedErr.IsValid() == false );
    CHECK( mappedErr.GetErrorReason() == "Failure: Something wrong..." );
    CHECK( mappedErr.GetError() != nullptr );
}

Nullable< NotCopyable > CreateNotCopyable( bool move )
{
    if( move )
		return std::move( NotCopyable() );
    else
        return NotCopyable();
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Nullable.NotCopyAble", "[Nullable]" )
{
    auto mappedErr =
        Nullable< NotCopyable >( "Something wrong..." ).MapErr( []( auto e ) { return fmt::format( "Failure: {}", e ); } );

    REQUIRE( mappedErr.IsValid() == false );
    CHECK( mappedErr.GetErrorReason() == "Failure: Something wrong..." );
    CHECK( mappedErr.GetError() != nullptr );

	auto result = CreateNotCopyable( true );
    REQUIRE( result.IsValid() == true );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.ReturnResult.operator&&", "[Nullable]" )
{
    ReturnResult invalid( "Something wrong..." );
    ReturnResult valid = Success::True;

    auto result = invalid && valid;
    CHECK( result.IsValid() == false );
    CHECK( result.GetErrorReason() == "Something wrong..." );

    auto result2 = valid && invalid;
    CHECK( result2.IsValid() == false );
    CHECK( result2.GetErrorReason() == "Something wrong..." );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.ReturnResult.Ok.OnSuccess", "[Nullable]" )
{
    ReturnResult valid = Success::True;

    auto nullable = valid.Ok( 5 );
    CHECK( nullable.IsValid() == true );
    CHECK( nullable.Get() == 5 );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.ReturnResult.Ok.Invalid", "[Nullable]" )
{
    ReturnResult invalid( "Something wrong..." );

    auto nullable = invalid.Ok( 5 );
    CHECK( nullable.IsValid() == false );
    CHECK( nullable.GetError() != nullptr );
    CHECK( nullable.GetErrorReason() == "Something wrong..." );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.ReturnResult.MapErr", "[Nullable]" )
{
    ReturnResult mappedErr = ReturnResult( "Something wrong..." ).MapErr( []( auto e ) { return fmt::format( "Failure: {}", e ); } );

    CHECK( mappedErr.IsValid() == false );
    CHECK( mappedErr.GetErrorReason() == "Failure: Something wrong..." );
}


//====================================================================================//
//			Test Nullable impl helpers	
//====================================================================================//

// ================================ //
// Tests internal trait to enable and disable Nullable conversion to base class.
TEST_CASE( "Common.Helpers.Exceptions.Nullable.Traits.IsBaseConversion", "[Nullable]" )
{
	bool is = false;

	// Check conversion Nullable< Dog* > -> Nullable< Animal* >
	is = impl::IsBaseConversion< Dog*, Animal* >::value;
	CHECK( is == true );

	is = impl::IsBaseConversion< Animal*, Dog* >::value;
	CHECK( is == false );

	// Can't cast not pointer type to pointer.
	is = impl::IsBaseConversion< Animal, Dog* >::value;
	CHECK( is == false );

	is = impl::IsBaseConversion< Animal*, Dog >::value;
	CHECK( is == false );

	is = impl::IsBaseConversion< Animal, Dog >::value;
	CHECK( is == false );

	is = impl::IsBaseConversion< Animal&, Dog* >::value;
	CHECK( is == false );

	is = impl::IsBaseConversion< Animal*, Dog& >::value;
	CHECK( is == false );
}

