#pragma once
/**
@file StructsSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Tests/SerializationTest/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructAsRefContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructAsPtrContainer.h"

using namespace sw;



// ================================ //
// Serializes object with structure bound as reference.
TEST_CASE( "Struct.BindAsReference", "[Serialization]" )
{
	StructAsRefContainer expected;
	StructAsRefContainer actual;
	expected.SimpleStruct.FillWithDataset3();
	actual.SimpleStruct.FillWithDataset2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Struct.BindAsReference.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.BindAsReference.xml", actual ) );

	CHECK( actual.SimpleStruct == expected.SimpleStruct );
}

// ================================ //
// Serializes object with structure bound as pointer.
TEST_CASE( "Struct.BindAsPointer", "[Serialization]" )
{
	StructAsPtrContainer expected;
	StructAsPtrContainer actual;
	expected.SimpleStruct.FillWithDataset3();
	actual.SimpleStruct.FillWithDataset2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Struct.BindAsPointer.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.BindAsPointer.xml", actual ) );

	CHECK( actual.SimpleStruct == expected.SimpleStruct );
}
