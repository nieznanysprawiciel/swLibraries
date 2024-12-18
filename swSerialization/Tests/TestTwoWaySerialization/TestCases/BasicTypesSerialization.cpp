/**
@file SimpleStructSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestTwoWaySerialization/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"

#include "swSerialization/Serialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructWithSimpleTypes.h"


using namespace sw;


// ================================ //
// Serializes and deserializes struct with simple types.
TEST_CASE( "Struct.BasicTypes", "[Serialization]" )
{
	StructWithSimpleTypes expected;
	StructWithSimpleTypes actual;		actual.FillWithDataset2();	// Change default dataset.

	sw::Serialization serial;

    REQUIRE_IS_VALID( serial.Serialize( "Serialization/StructWithBasicTypes.ser", expected ) );
    REQUIRE_IS_VALID( serial.Deserialize( "Serialization/StructWithBasicTypes.ser", actual ) );

	CHECK( actual.DoubleField == expected.DoubleField );
	CHECK( actual.FloatField == expected.FloatField );
	CHECK( actual.UIntField64 == expected.UIntField64 );
	CHECK( actual.IntField64 == expected.IntField64 );
	CHECK( actual.UIntField32 == expected.UIntField32 );
	CHECK( actual.IntField32 == expected.IntField32 );
	CHECK( actual.UIntField16 == expected.UIntField16 );
	CHECK( actual.IntField16 == expected.IntField16 );
	CHECK( actual.UIntField8 == expected.UIntField8 );
	CHECK( actual.IntField8 == expected.IntField8 );
	CHECK( actual.CharField == expected.CharField );
	CHECK( actual.BoolField == expected.BoolField );
}

