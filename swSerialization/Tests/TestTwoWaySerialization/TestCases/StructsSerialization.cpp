#pragma once
/**
@file StructsSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestTwoWaySerialization/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swSerialization/Serialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructAsRefContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructAsPtrContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructAsCopyContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructPtrContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructSharedPtrContainer.h"

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

	REQUIRE( serial.Serialize( "Serialization/Struct.BindAsReference.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.BindAsReference.ser", actual ) );

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

	REQUIRE( serial.Serialize( "Serialization/Struct.BindAsPointer.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.BindAsPointer.ser", actual ) );

	CHECK( actual.SimpleStruct == expected.SimpleStruct );
}

// ================================ //
// Serializes object with structure that is not bound as pointer neither as reference.
// This should cause that structure will be copied.
TEST_CASE( "Struct.BindAsCopy", "[Serialization]" )
{
	StructAsCopyContainer expected;
	StructAsCopyContainer actual;
	expected.SimpleStruct.FillWithDataset3();
	actual.SimpleStruct.FillWithDataset2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Struct.BindAsCopy.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.BindAsCopy.ser", actual ) );

	CHECK( actual.SimpleStruct == expected.SimpleStruct );
}

// ================================ //
// Serializes object with structure pointer.
TEST_CASE( "Struct.PointerToStruct", "[Serialization]" )
{
	StructPtrContainer expected;
	StructPtrContainer actual;
	expected.SimpleStruct->FillWithDataset3();
	actual.SimpleStruct->FillWithDataset2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Struct.PointerToStruct.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.PointerToStruct.ser", actual ) );

	CHECK( *( actual.SimpleStruct ) == *( expected.SimpleStruct ) );
}

// ================================ //
// Serializes object with structure pointer. Deserialized object has nullptr an must create structure by itself.
TEST_CASE( "Struct.PointerToStruct.Create", "[Serialization]" )
{
	StructPtrContainer expected;
	StructPtrContainer actual;
	expected.SimpleStruct->FillWithDataset3();
	actual.Replace( nullptr );

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Struct.PointerToStruct.Create.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.PointerToStruct.Create.ser", actual ) );

	REQUIRE( actual.SimpleStruct != nullptr );
	CHECK( *( actual.SimpleStruct ) == *( expected.SimpleStruct ) );
}

// ================================ //
// Serializes object with structure shared pointer.
TEST_CASE( "Struct.SharedPointerToStruct", "[Serialization]" )
{
	StructSharedPtrContainer expected;
	StructSharedPtrContainer actual;
	expected.SimpleStruct->FillWithDataset3();
	actual.SimpleStruct->FillWithDataset2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Struct.SharedPointerToStruct.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.SharedPointerToStruct.ser", actual ) );

	REQUIRE( actual.SimpleStruct != nullptr );
	CHECK( *( actual.SimpleStruct ) == *( expected.SimpleStruct ) );
}

// ================================ //
// Serializes object with structure shared pointer.
TEST_CASE( "Struct.SharedPointerToStruct.Create", "[Serialization]" )
{
	StructSharedPtrContainer expected;
	StructSharedPtrContainer actual;
	expected.SimpleStruct->FillWithDataset3();
	actual.Replace( nullptr );

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/Struct.SharedPointerToStruct.Create.ser", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.SharedPointerToStruct.Create.ser", actual ) );

	REQUIRE( actual.SimpleStruct != nullptr );
	CHECK( *( actual.SimpleStruct ) == *( expected.SimpleStruct ) );
}


