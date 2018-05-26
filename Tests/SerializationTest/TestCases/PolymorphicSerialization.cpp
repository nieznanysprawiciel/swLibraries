#pragma once
/**
@file PolymorphicSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Tests/SerializationTest/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/PolymorphicObjectContainer.h"


using namespace sw;


// ================================ //
// Serializes polymorphic object with base class set.
TEST_CASE( "Polymorphic.BaseObject", "[Serialization]" )
{
	PolymorphicObjectContainer expected;
	PolymorphicObjectContainer actual;
	expected.ObjectPtr = new BaseObject();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Polymorphic.BaseObject.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Polymorphic.BaseObject.xml", actual ) );

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

	REQUIRE( serial.Serialize( "Serialization/Polymorphic.DerivedObject.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Polymorphic.DerivedObject.xml", actual ) );

	CHECK( actual.ObjectPtr->GetType() == TypeID::get< DerivedObject >() );
	CHECK( actual.ObjectPtr->GetType() == expected.ObjectPtr->GetType() );
}


// ================================ //
// Deserialized xml with class not derived from BaseObject as expected.
// Deserialization shouldn't set any object.
TEST_CASE( "Polymorphic.NotRelatedClasses", "[Serialization]" )
{
	PolymorphicObjectContainer actual;
	sw::Serialization deserial;

	REQUIRE( deserial.Deserialize( "Serialization/TestInput/Polymorphic.NotRelatedClasses.xml", actual ) );
	CHECK( actual.ObjectPtr == nullptr );
}

// ================================ //
// Object pointer is set to not nullptr value.
// In this case serialization doesn't change object.
TEST_CASE( "Polymorphic.NotNullptrObject", "[Serialization]" )
{
	PolymorphicObjectContainer actual;
	sw::Serialization deserial;

	auto prevObject = new DerivedObject();
	actual.ObjectPtr = prevObject;

	REQUIRE( deserial.Deserialize( "Serialization/TestInput/Polymorphic.NotRelatedClasses.xml", actual ) );
	CHECK( actual.ObjectPtr == prevObject );
}

