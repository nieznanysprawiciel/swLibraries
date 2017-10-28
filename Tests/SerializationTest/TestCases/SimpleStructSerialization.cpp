/**
@file SimpleStructSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"

#include "swCommonLib/Tests/SerializationTest/TestClasses/StructWithSimpleTypes.h"


using namespace sw;


// ================================ //
// Serializes and deserializes struct with simple types.
TEST_CASE( "StructWithBasicTypes", "[Serialization]" )
{
	StructWithSimpleTypes object;

	sw::Serialization serial;
	CHECK( serial.Serialize( "Serialization/StructWithBasicTypes.xml", object ) );
}

