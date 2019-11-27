/**
@file TestSerializerAPI.cppp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


#include "swSerialization/Serializers/SerializerJson/SerializerJSON.h"


using namespace sw;



// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialObject.AddObject", "[Serializers][SerializerXML]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        auto firstObject = root.AddObject( "FirstObject" );

        auto saveResult = ser.SaveFile( "SerializerTest/JSON/Generated/Test-AddObject.json", sw::WritingMode::Readable );
        REQUIRE_IS_VALID( saveResult );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        auto loadResult = deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-AddObject.json" );
        REQUIRE_IS_VALID( loadResult );

        SerialObject root = deser.Root();
        REQUIRE( root.GetElement( "FirstObject" ).has_value() );
        REQUIRE( root.GetElement( "FirstObject" ).value().IsObject() );
    }
}

// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialObject.AddObject.TreeStructure", "[Serializers][SerializerXML]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        auto firstObject = root.AddObject( "FirstObject" );
        
        auto first = firstObject.AddObject( "First" );
        auto second = firstObject.AddObject( "Second" );
        auto third = firstObject.AddObject( "Third" );

        // Change order of adding elements.
        third.AddObject( "Child1" );
        second.AddObject( "Child2" );
        first.AddObject( "Child3" );

        auto saveResult = ser.SaveFile( "SerializerTest/JSON/Generated/Test-AddObject-TreeStructure.json", sw::WritingMode::Readable );
        REQUIRE_IS_VALID( saveResult );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        auto loadResult = deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-AddObject-TreeStructure.json" );
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
    }
}


