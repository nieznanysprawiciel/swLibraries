/**
@file EnumSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestTwoWaySerialization/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swSerialization/Serialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Enums/TriStateObject.h"

using namespace sw;


// ================================ //
// Serializes object with enumeration.
TEST_CASE( "Struct.Enum", "[Serialization]" )
{
	TriStateObject expected;
	TriStateObject actual;
	expected.State = TriStateEnum::Down;
	actual.State = TriStateEnum::Middle;

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Struct.Enum.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.Enum.ser", actual ) );

	CHECK( actual.State == expected.State );
	CHECK( actual.State == TriStateEnum::Down );
}

