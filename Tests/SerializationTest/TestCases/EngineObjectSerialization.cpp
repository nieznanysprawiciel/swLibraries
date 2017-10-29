/**
@file EngineObjectSerialziation.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"

#include "swCommonLib/Tests/SerializationTest/TestClasses/StructWithSimpleTypes.h"
#include "swCommonLib/Tests/SerializationTest/TestClasses/BaseObject.h"


using namespace sw;


// ================================ //
// Serializes object with structure bound as pointer.
TEST_CASE( "GenericObject.StructField.AsPointer", "[Serialization]" )
{
	BaseObject* expected = new BaseObject;
	BaseObject* actual = new BaseObject;
	actual->m_simpleStruct1.FillWithDataset2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/GenericObject.StructField.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/GenericObject.StructField.xml", actual ) );

	CHECK( actual->m_simpleStruct1 == expected->m_simpleStruct1 );
}

// ================================ //
// Serializes object passing reference to it instead of EngineObject*.
TEST_CASE( "GenericObject.PassRefToObject", "[Serialization]" )
{
	BaseObject expected;
	BaseObject actual;
	actual.m_simpleStruct1.FillWithDataset2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE( serial.Serialize( "Serialization/GenericObject.PassRefToObject.xml", expected ) );
	REQUIRE( deserial.Deserialize( "Serialization/GenericObject.PassRefToObject.xml", actual ) );

	CHECK( actual.m_simpleStruct1 == expected.m_simpleStruct1 );
}

