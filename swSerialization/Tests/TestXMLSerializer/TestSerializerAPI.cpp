/**
@file TestSerializerAPI.cppp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


#include "swSerialization/Serializers/SerializerXML/SerializerXML.h"


using namespace sw;



// ================================ //
//
TEST_CASE( "Serializer.XML.SerialObject.AddObject", "[Serializers][SerializerXML]" )
{
    {
        SerializerXML ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        auto firstObject = root.AddObject( "FirstObject" );

        auto saveResult = ser.SaveFile( "SerializerTest/XML/Generated/Test-AddObject.xml", sw::WritingMode::Readable );
        REQUIRE_IS_VALID( saveResult );
    }

    {
        SerializerXML deser( std::make_unique< ISerializationContext >() );
        auto loadResult = deser.LoadFromFile( "SerializerTest/XML/Generated/Test-AddObject.xml" );
        REQUIRE_IS_VALID( loadResult );

        SerialObject root = deser.Root();
        REQUIRE( root.GetElement( "FirstObject" ).has_value() );
        REQUIRE( root.GetElement( "FirstObject" ).value().IsObject() );
    }
}

// ================================ //
//
TEST_CASE( "Serializer.XML.SerialObject.AddObject.TreeStructure", "[Serializers][SerializerXML]" )
{
    {
        SerializerXML ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        auto firstObject = root.AddObject( "FirstObject" );

        auto first = firstObject.AddObject( "First" );
        auto second = firstObject.AddObject( "Second" );
        auto third = firstObject.AddObject( "Third" );

        // Change order of adding elements.
        third.AddObject( "Child1" );
        second.AddObject( "Child2" );
        first.AddObject( "Child3" );

        auto saveResult = ser.SaveFile( "SerializerTest/XML/Generated/Test-AddObject-TreeStructure.xml", sw::WritingMode::Readable );
        REQUIRE_IS_VALID( saveResult );
    }

    {
        SerializerXML deser( std::make_unique< ISerializationContext >() );
        auto loadResult = deser.LoadFromFile( "SerializerTest/XML/Generated/Test-AddObject-TreeStructure.xml" );
        REQUIRE_IS_VALID( loadResult );

        SerialObject root = deser.Root();
        REQUIRE( root.GetElement( "FirstObject" ).has_value() );
        REQUIRE( root.GetElement( "FirstObject" ).value().IsObject() );

        auto firstObject = root.GetElement( "FirstObject" ).value().ObjectView().value();

        REQUIRE( firstObject.GetElement( "First" ).has_value() );
        REQUIRE( firstObject.GetElement( "First" ).value().IsObject() );

        REQUIRE( firstObject.GetElement( "Second" ).has_value() );
        REQUIRE( firstObject.GetElement( "Second" ).value().IsObject() );

        REQUIRE( firstObject.GetElement( "Third" ).has_value() );
        REQUIRE( firstObject.GetElement( "Third" ).value().IsObject() );

        auto third = firstObject.GetElement( "Third" ).value().ObjectView().value();

        CHECK( third.GetElement( "Child1" ).has_value() );
        CHECK( third.GetElement( "Child1" ).value().IsObject() );

        auto second = firstObject.GetElement( "Second" ).value().ObjectView().value();

        CHECK( second.GetElement( "Child2" ).has_value() );
        CHECK( second.GetElement( "Child2" ).value().IsObject() );

        auto first = firstObject.GetElement( "First" ).value().ObjectView().value();

        CHECK( first.GetElement( "Child3" ).has_value() );
        CHECK( first.GetElement( "Child3" ).value().IsObject() );
    }
}

// ================================ //
//
TEST_CASE( "Serializer.XML.SerialObject.GetElement.NotExisitng", "[Serializers][SerializerXML]" )
{
    {
        SerializerXML ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        auto firstObject = root.AddObject( "FirstObject" );

        auto saveResult = ser.SaveFile( "SerializerTest/XML/Generated/Test-GetElement-NotExisitng.xml", sw::WritingMode::Readable );
        REQUIRE_IS_VALID( saveResult );
    }

    {
        SerializerXML deser( std::make_unique< ISerializationContext >() );
        auto loadResult = deser.LoadFromFile( "SerializerTest/XML/Generated/Test-GetElement-NotExisitng.xml" );
        REQUIRE_IS_VALID( loadResult );

        SerialObject root = deser.Root();
        REQUIRE_FALSE( root.GetElement( "NotExisitng" ).has_value() );
    }
}
