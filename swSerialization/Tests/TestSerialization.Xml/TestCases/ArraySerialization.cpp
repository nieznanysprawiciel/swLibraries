/**
@file ArraySerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestSerialization.Xml/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swSerialization/Serialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/ArrayContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/ArrayPolymorphicContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/StaticArrayContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/StaticArrayContainer_Readonly.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/BaseObject.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Node.h"


using namespace sw;



// ================================ //
// Serialized file contains more elements then array can hold. The same problem occures
// when dynamic array is declared as readonly property.
// Deserialization should fail.
TEST_CASE( "Arrays.Static.PlainStructs.ToManyElements", "[Serialization]" )
{
	StaticArrayContainer* expected = new StaticArrayContainer;
	StaticArrayContainer* actual = new StaticArrayContainer;
	actual->ArraysSet2();

	sw::Serialization deserial;
	REQUIRE_FALSE( deserial.Deserialize( "Serialization/TestInput/Arrays.Static.PlainStructs.ToManyElements.xml", actual ) );
}

// ================================ //
// Deserializes empty vector.
TEST_CASE( "Arrays.Vector.Empty", "[Serialization]" )
{
	sw::Node actual;

	sw::Serialization deserial;
	REQUIRE( deserial.Deserialize( "Serialization/TestInput/Arrays.Vector.Empty.xml", actual ) );

	CHECK( actual.Children.size() == 0 );

	// We need to check if Generic field was deserialized properly.
	// This is connected to bug, where deserialization didn't Exited array if it was empty.
	REQUIRE( actual.Generic != nullptr );
}

// ================================ //
// [Bug] Deserializes not empty vector. Property following array doesn't deserialize properly
// because deserializer ends up in incorrect state (too less Exit() calls).
TEST_CASE( "Arrays.Vector.Bugs.ObjectFollowingArray", "[Serialization]" )
{
	sw::Node actual;

	sw::Serialization deserial;
	REQUIRE( deserial.Deserialize( "Serialization/TestInput/Arrays.Vector.Bugs.ObjectFollowingArray.xml", actual ) );

	CHECK( actual.Children.size() == 1 );

	// We need to check if Generic field was deserialized properly.
	// This is connected to bug, where deserialization didn't Exited array if it was empty.
	REQUIRE( actual.Generic != nullptr );
	CHECK( actual.Children[ 0 ].Generic != nullptr );
}

