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

	REQUIRE( serial.Serialize( "Serialization/Struct.BindAsCopy.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.BindAsCopy.xml", actual ) );

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

	REQUIRE( serial.Serialize( "Serialization/Struct.PointerToStruct.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.PointerToStruct.xml", actual ) );

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

	REQUIRE( serial.Serialize( "Serialization/Struct.PointerToStruct.Create.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.PointerToStruct.Create.xml", actual ) );

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

	REQUIRE( serial.Serialize( "Serialization/Struct.SharedPointerToStruct.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.SharedPointerToStruct.xml", actual ) );

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

	REQUIRE( serial.Serialize( "Serialization/Struct.SharedPointerToStruct.Create.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/Struct.SharedPointerToStruct.Create.xml", actual ) );

	REQUIRE( actual.SimpleStruct != nullptr );
	CHECK( *( actual.SimpleStruct ) == *( expected.SimpleStruct ) );
}


