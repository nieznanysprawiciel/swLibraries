/**
@file StlTypesSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestTwoWaySerialization/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swSerialization/Serialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/StringContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Arrays/ArrayContainer.h"


using namespace sw;


// ================================ //
// Serializes object derived from Object with strings types.
TEST_CASE( "GenericObject.Strings", "[Serialization]" )
{
	StringContainer* expected = new StringContainer;
	StringContainer* actual = new StringContainer;
	actual->StringsSet2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/GenericObject.Strings.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/GenericObject.Strings.ser", actual ) );

	CHECK( actual->Description == expected->Description );
	CHECK( actual->Content == expected->Content );
}




