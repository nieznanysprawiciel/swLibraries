/**
@file StlTypesSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Tests/SerializationTest/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/StringContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/ArrayContainer.h"


using namespace sw;


// ================================ //
// Serializes object derived from EngineObject with strings types.
TEST_CASE( "GenericObject.Strings", "[Serialization]" )
{
	StringContainer* expected = new StringContainer;
	StringContainer* actual = new StringContainer;
	actual->StringsSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/GenericObject.Strings.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/GenericObject.Strings.xml", actual ) );

	CHECK( actual->Description == expected->Description );
	CHECK( actual->Content == expected->Content );
}

// ================================ //
// Serializes object derived from EngineObject with array types.
TEST_CASE( "GenericObject.Arrays.PlainStructs", "[Serialization]" )
{
	ArrayContainer* expected = new ArrayContainer;
	ArrayContainer* actual = new ArrayContainer;
	actual->ArraysSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/GenericObject.Arrays.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/GenericObject.Arrays.xml", actual ) );

	CHECK( actual->StructsVec == expected->StructsVec );
}



