#pragma once
/**
@file PolymorphicSerialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestSerialization.Xml/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swSerialization/Serialization/Serialization.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/PolymorphicObjectContainer.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/PolymorphicSharedPtrContainer.h"


using namespace sw;



// ================================ //
// Deserialized xml with class not derived from BaseObject as expected.
// Deserialization shouldn't set any object.
TEST_CASE( "Polymorphic.NotRelatedClasses", "[Serialization]" )
{
	PolymorphicObjectContainer actual;
	sw::Serialization deserial;

	REQUIRE( deserial.Deserialize( "Serialization/TestInput/Polymorphic.NotRelatedClasses.xml", actual ) );
	CHECK( actual.ObjectPtr == nullptr );
}

// ================================ //
// ObjectPtr is set to not nullptr value.
// In this case serialization destroys object and sets property to nullptr.
TEST_CASE( "Polymorphic.NotNullptrObject", "[Serialization]" )
{
	PolymorphicObjectContainer actual;
	sw::Serialization deserial;

	auto prevObject = new DerivedObject();
	actual.ObjectPtr = prevObject;

	REQUIRE( deserial.Deserialize( "Serialization/TestInput/Polymorphic.NotRelatedClasses.xml", actual ) );
	CHECK( actual.ObjectPtr == nullptr );
}

// ================================ //
// ObjectPtr is set to not nullptr object of the same type as should be deserialized.
// Deserialziation shouldn't destroy object.
TEST_CASE( "Polymorphic.NotNullptrObject.ClassWithSameType", "[Serialization]" )
{
	PolymorphicObjectContainer actual;
	sw::Serialization deserial;

	auto prevObject = new DerivedObject();
	actual.ObjectPtr = prevObject;

	// Override internal structs values.
	prevObject->m_simpleStruct1.FillWithDataset4();
	prevObject->m_simpleStruct2.FillWithDataset4();

	StructWithSimpleTypes reference;
	reference.FillWithDataset1();

	REQUIRE( deserial.Deserialize( "Serialization/TestInput/Polymorphic.NotNullptrObject.ClassWithSameType.xml", actual ) );
	CHECK( actual.ObjectPtr == prevObject );

	CHECK( actual.ObjectPtr->m_simpleStruct1 == reference );
	CHECK( static_cast< DerivedObject* >( actual.ObjectPtr )->m_simpleStruct2 == reference );
}

// ================================ //
// ObjectPtr is set to not nullptr object of different type as should be deserialized.
// Deserialization creates new object.
TEST_CASE( "Polymorphic.NotNullptrObject.ClassWithDifferentType", "[Serialization]" )
{
	PolymorphicObjectContainer actual;
	sw::Serialization deserial;

	auto prevObject = new DerivedObject();
	actual.ObjectPtr = prevObject;

	REQUIRE( deserial.Deserialize( "Serialization/TestInput/Polymorphic.NotNullptrObject.ClassWithDifferentType.xml", actual ) );
	
	CHECK( actual.ObjectPtr != prevObject );
	CHECK( actual.ObjectPtr != nullptr );
}

// ================================ //
// ObjectPtr is set to not nullptr object. Deserialization requires nullptr.
TEST_CASE( "Polymorphic.NotNullptrObject.NullptrInXml", "[Serialization]" )
{
	PolymorphicObjectContainer actual;
	sw::Serialization deserial;

	auto prevObject = new DerivedObject();
	actual.ObjectPtr = prevObject;

	REQUIRE( deserial.Deserialize( "Serialization/TestInput/Polymorphic.NotNullptrObject.NullptrInXml.xml", actual ) );
	CHECK( actual.ObjectPtr == nullptr );
}

// ================================ //
// Deserialized class constructor creates shared pointer.
// This is invalid situation, because we can't extract pointer from wrapper.
TEST_CASE( "Polymorphic.SharedPtrContructor", "[Serialization]" )
{
	PolymorphicObjectContainer actual;
	sw::Serialization deserial;

	REQUIRE( deserial.Deserialize( "Serialization/TestInput/Polymorphic.SharedPtrContructor.xml", actual ) );
	CHECK( actual.ObjectPtr == nullptr );
}

// ================================ //
// Deserializes polymorphic object stored in class as shared_ptr. Creation constructs
// raw pointer object. Assingment should fail, object remains nullptr.
TEST_CASE( "Polymorphic.PointerConstructor", "[Serialization]" )
{
	PolymorphicSharedPtrContainer actual;

	sw::Serialization deserial;

	REQUIRE( deserial.Deserialize( "Serialization/TestInput/Polymorphic.PointerConstructor.xml", actual ) );
	CHECK( actual.ObjectPtr == nullptr );
}

