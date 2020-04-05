/**
@file ArraySerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestTwoWaySerialization/PrecompiledHeader/stdafx.h"
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
// Serializes object derived from Object with array types.
TEST_CASE( "Arrays.Vector.PlainStructs", "[Serialization]" )
{
	ArrayContainer* expected = new ArrayContainer;
	ArrayContainer* actual = new ArrayContainer;
	actual->ArraysSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Arrays.Vector.PlainStructs.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Arrays.Vector.PlainStructs.ser", actual ) );

	CHECK( actual->StructsVec == expected->StructsVec );
}


// ================================ //
// Serializes object derived from Object with static array type.
// Note that if we declare static array not as reference, it will be copied to variant.
// 
TEST_CASE( "Arrays.Static.PlainStructs.VariantArrayCopy", "[Serialization]" )
{
	StaticArrayContainer* expected = new StaticArrayContainer;
	StaticArrayContainer* actual = new StaticArrayContainer;
	actual->ArraysSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Arrays.Static.VariantArrayCopy.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Arrays.Static.VariantArrayCopy.ser", actual ) );

	CHECK( actual->Compare( *expected ) );
}

// ================================ //
// Serializes object derived from Object with static array type.
// Only readonly static array can be bound by reference.
TEST_CASE( "Arrays.Static.PlainStructs", "[Serialization]" )
{
	StaticArrayContainer_Readonly* expected = new StaticArrayContainer_Readonly;
	StaticArrayContainer_Readonly* actual = new StaticArrayContainer_Readonly;
	actual->ArraysSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Arrays.Static.PlainStructs.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Arrays.Static.PlainStructs.ser", actual ) );

	CHECK( actual->Compare( *expected ) );
}

// ================================ //
// Serializes array with polymorphic type pointer.
TEST_CASE( "Arrays.Vector.Polymorphic.Pointer", "[Serialization]" )
{
	ArrayPolymorphicContainer* expected = new ArrayPolymorphicContainer;
	ArrayPolymorphicContainer* actual = new ArrayPolymorphicContainer;
	expected->ArraysSet1();
	// actual should be empty.

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Arrays.Vector.Polymorphic.Pointer.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Arrays.Vector.Polymorphic.Pointer.ser", actual ) );

	REQUIRE( actual->PolymorphicsVec.size() == 3 );

	CHECK( actual->PolymorphicsVec[ 0 ]->GetType() == expected->PolymorphicsVec[ 0 ]->GetType() );
	CHECK( actual->PolymorphicsVec[ 1 ]->GetType() == expected->PolymorphicsVec[ 1 ]->GetType() );
	CHECK( actual->PolymorphicsVec[ 2 ]->GetType() == expected->PolymorphicsVec[ 2 ]->GetType() );
}

// ================================ //
// Serializes and deserializes array with nullptr stored as raw pointer.
TEST_CASE( "Arrays.Vector.Polymorphic.Nullptr.RawPointer", "[Serialization]" )
{
    ArrayPolymorphicContainer* expected = new ArrayPolymorphicContainer;
    ArrayPolymorphicContainer* actual = new ArrayPolymorphicContainer;
    expected->PolymorphicsVec.push_back( nullptr );
    // actual should be empty.

    sw::Serialization serial;
    sw::Serialization deserial;

    REQUIRE( serial.Serialize( "Serialization/Arrays.Vector.Polymorphic.Nullptr.RawPointer.ser", expected ) );
    REQUIRE( deserial.Deserialize( "Serialization/Arrays.Vector.Polymorphic.Nullptr.RawPointer.ser", actual ) );

    REQUIRE( actual->PolymorphicsVec.size() == 1 );

    CHECK( actual->PolymorphicsVec[ 0 ] == nullptr );
}

// ================================ //
// Serializes and deserializes array with nullptr stored as shared pointer.
TEST_CASE( "Arrays.Vector.Polymorphic.Nullptr.SharedPointer", "[Serialization]" )
{
    ArraySharedPolymorphicContainer* expected = new ArraySharedPolymorphicContainer;
    ArraySharedPolymorphicContainer* actual = new ArraySharedPolymorphicContainer;
    expected->PolymorphicsVec.push_back( nullptr );
    // actual should be empty.

    sw::Serialization serial;
    sw::Serialization deserial;

    REQUIRE( serial.Serialize( "Serialization/Arrays.Vector.Polymorphic.Nullptr.SharedPointer.ser", expected ) );
    REQUIRE( deserial.Deserialize( "Serialization/Arrays.Vector.Polymorphic.Nullptr.SharedPointer.ser", actual ) );

    REQUIRE( actual->PolymorphicsVec.size() == 1 );

    CHECK( actual->PolymorphicsVec[ 0 ] == nullptr );
}
