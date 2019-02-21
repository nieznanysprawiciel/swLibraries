/**
@file TestNullable.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"
#include "swCommonLib/Common/Exceptions/ExceptionsList.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"


#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Mammals/Dog.h"


using namespace sw;


// ================================ //
//
TEST_CASE( "Common.Helpers.Exceptions.Nullable.RValueCast" )
{
	Nullable< Dog* > nullableDog( new Dog( "TestDog", 15, "DontKnowAnyRaces" ) );
	Nullable< Animal* > nullableAnimal( std::move( nullableDog ) );

	REQUIRE( nullableAnimal.IsValid() == true );
	CHECK( nullableAnimal.Get()->GetName() == "TestDog" );
	CHECK( nullableAnimal.Get()->GetAge() == 15 );
}

