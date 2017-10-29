/**
@file StlTypesSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"

#include "swCommonLib/Tests/SerializationTest/TestClasses/StringContainer.h"


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

