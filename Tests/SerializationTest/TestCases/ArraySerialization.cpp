/**
@file ArraySerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Tests/SerializationTest/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/ArrayContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/StaticArrayContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/StaticArrayContainer_Readonly.h"


using namespace sw;

// ================================ //
// Serializes object derived from EngineObject with array types.
TEST_CASE( "GenericObject.Arrays.Vector.PlainStructs", "[Serialization]" )
{
	ArrayContainer* expected = new ArrayContainer;
	ArrayContainer* actual = new ArrayContainer;
	actual->ArraysSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/GenericObject.Arrays.Vector.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/GenericObject.Arrays.Vector.xml", actual ) );

	CHECK( actual->StructsVec == expected->StructsVec );
}


// ================================ //
// Serializes object derived from EngineObject with static array type.
// Note that if we declare static array not as reference, it will be copied to variant.
// 
TEST_CASE( "GenericObject.Arrays.Static.PlainStructs.VariantArrayCopy", "[Serialization]" )
{
	StaticArrayContainer* expected = new StaticArrayContainer;
	StaticArrayContainer* actual = new StaticArrayContainer;
	actual->ArraysSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/GenericObject.Arrays.Static.VariantArrayCopy.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/GenericObject.Arrays.Static.VariantArrayCopy.xml", actual ) );

	CHECK( actual->Compare( *expected ) );
}

// ================================ //
// Serializes object derived from EngineObject with static array type.
// Only readonly static array can be bound by reference.
TEST_CASE( "GenericObject.Arrays.Static.PlainStructs", "[Serialization]" )
{
	StaticArrayContainer_Readonly* expected = new StaticArrayContainer_Readonly;
	StaticArrayContainer_Readonly* actual = new StaticArrayContainer_Readonly;
	actual->ArraysSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/GenericObject.Arrays.Static.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/GenericObject.Arrays.Static.xml", actual ) );

	CHECK( actual->Compare( *expected ) );
}

