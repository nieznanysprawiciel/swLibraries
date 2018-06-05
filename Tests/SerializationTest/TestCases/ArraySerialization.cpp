/**
@file ArraySerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Tests/SerializationTest/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/ArrayContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/ArrayPolymorphicContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/StaticArrayContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/StaticArrayContainer_Readonly.h"


using namespace sw;

// ================================ //
// Serializes object derived from EngineObject with array types.
TEST_CASE( "Arrays.Vector.PlainStructs", "[Serialization]" )
{
	ArrayContainer* expected = new ArrayContainer;
	ArrayContainer* actual = new ArrayContainer;
	actual->ArraysSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Arrays.Vector.PlainStructs.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Arrays.Vector.PlainStructs.xml", actual ) );

	CHECK( actual->StructsVec == expected->StructsVec );
}


// ================================ //
// Serializes object derived from EngineObject with static array type.
// Note that if we declare static array not as reference, it will be copied to variant.
// 
TEST_CASE( "Arrays.Static.PlainStructs.VariantArrayCopy", "[Serialization]" )
{
	StaticArrayContainer* expected = new StaticArrayContainer;
	StaticArrayContainer* actual = new StaticArrayContainer;
	actual->ArraysSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Arrays.Static.VariantArrayCopy.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Arrays.Static.VariantArrayCopy.xml", actual ) );

	CHECK( actual->Compare( *expected ) );
}

// ================================ //
// Serializes object derived from EngineObject with static array type.
// Only readonly static array can be bound by reference.
TEST_CASE( "Arrays.Static.PlainStructs", "[Serialization]" )
{
	StaticArrayContainer_Readonly* expected = new StaticArrayContainer_Readonly;
	StaticArrayContainer_Readonly* actual = new StaticArrayContainer_Readonly;
	actual->ArraysSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Arrays.Static.PlainStructs.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Arrays.Static.PlainStructs.xml", actual ) );

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

	REQUIRE( serial.Serialize( "Serialization/Arrays.Vector.Polymorphic.Pointer.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Arrays.Vector.Polymorphic.Pointer.xml", actual ) );

	REQUIRE( actual->PolymorphicsVec.size() == 3 );

	CHECK( actual->PolymorphicsVec[ 0 ]->GetType() == expected->PolymorphicsVec[ 0 ]->GetType() );
	CHECK( actual->PolymorphicsVec[ 1 ]->GetType() == expected->PolymorphicsVec[ 1 ]->GetType() );
	CHECK( actual->PolymorphicsVec[ 2 ]->GetType() == expected->PolymorphicsVec[ 2 ]->GetType() );
}

