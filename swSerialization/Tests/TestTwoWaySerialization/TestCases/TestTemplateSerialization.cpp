#pragma once
/**
@file TestTemplateSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestTwoWaySerialization/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"

#include "swSerialization/Serialization/Serialization.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Templates/TemplateStructWrapper.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructWithSimpleTypes.h"


using namespace sw;


// ================================ //
// Serializes template structure.
// rttr name for <StructWithSimpleTypes> contains '<' and '>' characters, which are illigal in xml.
// Test validates escaping.
TEST_CASE("Template.Struct.Wrapper", "[Serialization]")
{
	TemplateWrapper<StructWithSimpleTypes> expected;
	TemplateWrapper<StructWithSimpleTypes> actual;
	expected.Data.FillWithDataset3();
	actual.Data.FillWithDataset2();

	sw::Serialization serial;
	sw::Serialization deserial;

	REQUIRE_IS_VALID(serial.Serialize("Serialization/Template.Struct.Wrapper.ser", expected));
	REQUIRE_IS_VALID(deserial.Deserialize("Serialization/Template.Struct.Wrapper.ser", actual));

	CHECK(actual.Data == expected.Data);
}

