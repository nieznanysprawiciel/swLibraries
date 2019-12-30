/**
@file TestRttrPreconditions.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestTwoWaySerialization/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swSerialization/Serialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructWithSimpleTypes.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/BaseObject.h"


using namespace sw;


// ================================ //
// Checks if rttr property bound as pointer has pointer type.
TEST_CASE( "Serialization.RTTR.BindingAsPointer", "[Serialization]" )
{
    auto structType = TypeID::get< StructAsPtrContainer >();
    auto simpleStructProp = structType.get_property( "SimpleStruct" );

    CHECK( simpleStructProp.get_type().is_pointer() == true );
    CHECK( simpleStructProp.get_type().is_class() == false );
}

// ================================ //
// Checks if rttr property bound as reference has class type.
TEST_CASE( "Serialization.RTTR.BindingAsReference", "[Serialization]" )
{
    auto structType = TypeID::get< StructAsRefContainer >();
    auto simpleStructProp = structType.get_property( "SimpleStruct" );

    CHECK( simpleStructProp.get_type().is_pointer() == false );
    CHECK( simpleStructProp.get_type().is_class() == true );
}



