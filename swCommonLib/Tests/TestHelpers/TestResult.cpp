#include "swCommonLib/External/Catch/catch.hpp"

/**
@file TestResult.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"
#include "swCommonLib/Common/Exceptions/ExceptionsList.h"
#include "swCommonLib/Common/Exceptions/Result.h"
#include "swCommonLib/Common/Converters/Convert.h"


#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Mammals/Dog.h"


using namespace sw;


//====================================================================================//
//			Helpers for tests	
//====================================================================================//

// ================================ //
//
enum CreationError
{
    SomethingWrong,
    AccessDenied,
};

RTTR_REGISTRATION
{
    rttr::registration::enumeration< CreationError >( "CreationError" )
    (
        rttr::value( "Something wrong...",      CreationError::SomethingWrong ),
        rttr::value( "Access denied...",        CreationError::AccessDenied )
    );
}


// ================================ //
//
Result< Dog*, CreationError >			            CreateDog           ( bool valid )
{
    if( valid )
        return new Dog( "TestDog", 15, "DontKnowAnyRaces" );
    else
        return CreationError::SomethingWrong;
}

// ================================ //
//
Result< std::shared_ptr< Dog >, CreationError >     CreateDogPtr		( bool valid )
{
    if( valid )
        return std::make_shared< Dog >( "TestDog", 15, "DontKnowAnyRaces" );
    else
        return CreationError::SomethingWrong;
}


//====================================================================================//
//			Tests	
//====================================================================================//

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Result.CanReturnFromFunction", "[Nullable]" )
{
    auto dog = CreateDog( true );

    REQUIRE( dog.IsValid() == true );
    CHECK( dog.Get()->GetName() == "TestDog" );
    CHECK( dog.Get()->GetAge() == 15 );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Result.CanReturnFromFunction.Error", "[Nullable]" )
{
    auto dog = CreateDog( false );

    REQUIRE( dog.IsValid() == false );
    CHECK( dog.GetErrorReason() == "Something wrong..." );
    CHECK( dog.GetError() == CreationError::SomethingWrong );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Result.DestructibleObject", "[Nullable]" )
{
    auto dog = CreateDogPtr( true );

    REQUIRE( dog.IsValid() == true );
    CHECK( dog.Get()->GetName() == "TestDog" );
    CHECK( dog.Get()->GetAge() == 15 );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Result.DestructibleObject.Error", "[Nullable]" )
{
    auto dog = CreateDogPtr( false );

    REQUIRE( dog.IsValid() == false );
    CHECK( dog.GetErrorReason() == "Something wrong..." );
    CHECK( dog.GetError() == CreationError::SomethingWrong );
}

// ================================ //
// Passing string to constructor should create RuntimeException with error message.
TEST_CASE( "Common.Helpers.Exceptions.Result.Error.CreateFromEnum", "[Nullable]" )
{
    Result< Dog*, CreationError > nullableDog( CreationError::SomethingWrong );

    REQUIRE( nullableDog.IsValid() == false );
    CHECK( nullableDog.GetErrorReason() == "Something wrong..." );
    CHECK( nullableDog.GetError() == CreationError::SomethingWrong );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Result.RValueCast", "[Nullable]" )
{
    Result< Dog*, CreationError > nullableDog( new Dog( "TestDog", 15, "DontKnowAnyRaces" ) );
    Result< Animal*, CreationError > nullableAnimal( std::move( nullableDog ) );

    REQUIRE( nullableAnimal.IsValid() == true );
    CHECK( nullableAnimal.Get()->GetName() == "TestDog" );
    CHECK( nullableAnimal.Get()->GetAge() == 15 );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Result.RValueCast.Exception", "[Nullable]" )
{
    Result< Dog*, CreationError > nullableDog( CreationError::SomethingWrong );
    Result< Animal*, CreationError > nullableAnimal( std::move( nullableDog ) );

    REQUIRE( nullableAnimal.IsValid() == false );
    CHECK( nullableAnimal.GetErrorReason() == "Something wrong..." );
    CHECK( nullableAnimal.GetError() == CreationError::SomethingWrong );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Result.Move", "[Nullable]" )
{
    Result< Dog*, CreationError > nullableDog( new Dog( "TestDog", 15, "DontKnowAnyRaces" ) );
    Result< Animal*, CreationError > nullableAnimal = nullableDog.Move< Animal* >();

    REQUIRE( nullableAnimal.IsValid() == true );
    CHECK( nullableAnimal.Get()->GetName() == "TestDog" );
    CHECK( nullableAnimal.Get()->GetAge() == 15 );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Result.Move.Error", "[Nullable]" )
{
    Result< Dog*, CreationError > nullableDog( CreationError::SomethingWrong );
    Result< Animal*, CreationError > nullableAnimal = nullableDog.Move< Animal* >();

    REQUIRE( nullableAnimal.IsValid() == false );
    CHECK( nullableAnimal.GetErrorReason() == "Something wrong..." );
    CHECK( nullableAnimal.GetError() == CreationError::SomethingWrong );
}

// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Result.operator&&", "[Nullable]" )
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


