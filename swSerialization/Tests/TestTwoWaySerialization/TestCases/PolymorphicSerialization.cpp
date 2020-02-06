#pragma once
/**
@file PolymorphicSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestTwoWaySerialization/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swSerialization/Serialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/PolymorphicObjectContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/PolymorphicSharedPtrContainer.h"


using namespace sw;


// ================================ //
// Serializes polymorphic object with base class set.
TEST_CASE( "Polymorphic.BaseClass", "[Serialization]" )
{
	PolymorphicObjectContainer expected;
	PolymorphicObjectContainer actual;
	expected.ObjectPtr = new BaseObject();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Polymorphic.BaseClass.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Polymorphic.BaseClass.ser", actual ) );

	CHECK( actual.ObjectPtr->GetType() == TypeID::get< BaseObject >() );
	CHECK( actual.ObjectPtr->GetType() == expected.ObjectPtr->GetType() );
}



// ================================ //
// Serializes polymorphic object with derived class set.
TEST_CASE( "Polymorphic.DerivedObject", "[Serialization]" )
{
	PolymorphicObjectContainer expected;
	PolymorphicObjectContainer actual;
	expected.ObjectPtr = new DerivedObject();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Polymorphic.DerivedObject.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Polymorphic.DerivedObject.ser", actual ) );

	CHECK( actual.ObjectPtr->GetType() == TypeID::get< DerivedObject >() );
	CHECK( actual.ObjectPtr->GetType() == expected.ObjectPtr->GetType() );
}

// ================================ //
// Deserialize polymorphic object stored in class as shared_ptr.
TEST_CASE( "Polymorphic.BaseClass.SharedPtr", "[Serialization]" )
{
    PolymorphicSharedPtrContainer expected;
    PolymorphicSharedPtrContainer actual;
    expected.ObjectPtr = std::make_shared< SharedObject >();

    sw::Serialization serial;
    sw::Serialization deserial;

    REQUIRE( serial.Serialize( "Serialization/Polymorphic.BaseClass.SharedPtr.ser", expected ) );
    REQUIRE( deserial.Deserialize( "Serialization/Polymorphic.BaseClass.SharedPtr.ser", actual ) );

    CHECK( actual.ObjectPtr->GetType() == TypeID::get< SharedObject >() );
    CHECK( actual.ObjectPtr->GetType() == expected.ObjectPtr->GetType() );
}

// ================================ //
// Serializes and deserializees nullptr stored as raw pointer.
TEST_CASE( "Polymorphic.Nullptr.RawPointer", "[Serialization]" )
{
    PolymorphicObjectContainer expected;
    PolymorphicObjectContainer actual;
    expected.ObjectPtr = nullptr;

    sw::Serialization serial;
    sw::Serialization deserial;

    REQUIRE( serial.Serialize( "Serialization/Polymorphic.Nullptr.RawPointer.ser", expected ) );
    REQUIRE( deserial.Deserialize( "Serialization/Polymorphic.Nullptr.RawPointer.ser", actual ) );

    CHECK( actual.ObjectPtr == nullptr );
}

// ================================ //
// Serializes and deserializees nullptr stored as shared pointer.
TEST_CASE( "Polymorphic.Nullptr.SharedPtr", "[Serialization]" )
{
    PolymorphicSharedPtrContainer expected;
    PolymorphicSharedPtrContainer actual;
    expected.ObjectPtr = nullptr;

    sw::Serialization serial;
    sw::Serialization deserial;

    REQUIRE( serial.Serialize( "Serialization/Polymorphic.Nullptr.SharedPtr.ser", expected ) );
    REQUIRE( deserial.Deserialize( "Serialization/Polymorphic.Nullptr.SharedPtr.ser", actual ) );

    CHECK( actual.ObjectPtr == nullptr );
}
