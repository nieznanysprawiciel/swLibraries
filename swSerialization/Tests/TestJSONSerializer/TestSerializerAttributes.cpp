/**
@file TestSerializerAttributes.cppp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


#include "swSerialization/Serializers/SerializerJson/SerializerJSON.h"


using namespace sw;



//====================================================================================//
//			Test cases	
//====================================================================================//

// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialAttribute.String", "[Serializers][SerializerXML]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        auto firstObject = root.AddObject( "FirstObject" );

        firstObject.AddAttribute( "Name", "String-Attribute" );
        firstObject.AddAttribute( "Value", "Attribute1" );

        REQUIRE_IS_VALID( ser.SaveFile( "SerializerTest/JSON/Generated/Test-Attribute-String.json", sw::WritingMode::Readable ) );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-Attribute-String.json" ) );

        SerialObject root = deser.Root();

        REQUIRE( root.GetElement( "FirstObject" ).has_value() );
        REQUIRE( root.GetElement( "FirstObject" ).value().IsObject() );

        SerialObject firstObject = root.GetElement( "FirstObject" ).value().ObjectView().value();

        REQUIRE( firstObject.GetElement( "Name" ).has_value() );
        REQUIRE( firstObject.GetElement( "Name" ).value().IsAttribute() );

        auto nameAttribute = firstObject.GetElement( "Name" ).value().AttributeView().value();
        REQUIRE( nameAttribute.ConvertToString().has_value() == true );
        CHECK( nameAttribute.ConvertToString().value() == "String-Attribute" );

        REQUIRE( firstObject.GetElement( "Value" ).has_value() );
        REQUIRE( firstObject.GetElement( "Value" ).value().IsAttribute() );

        auto valueAttribute = firstObject.GetElement( "Value" ).value().AttributeView().value();
        REQUIRE( valueAttribute.ConvertToString().has_value() == true );
        CHECK( valueAttribute.ConvertToString().value() == "Attribute1" );
    }
}

// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialAttribute.NotExistingName", "[Serializers][SerializerXML]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        // Add attribute that won't be used.
        root.AddAttribute( "Name", "String-Attribute" );

        REQUIRE_IS_VALID( ser.SaveFile( "SerializerTest/JSON/Generated/Test-Attribute-NotExistingName.json", sw::WritingMode::Readable ) );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-Attribute-NotExistingName.json" ) );

        SerialObject root = deser.Root();

        REQUIRE( root.GetElement( "Key" ).has_value() == false );
    }
}

// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialAttribute.Int", "[Serializers][SerializerXML]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        // Add attribute that won't be used.
        root.AddAttribute( "Value", 12345678 );

        REQUIRE_IS_VALID( ser.SaveFile( "SerializerTest/JSON/Generated/Test-Attribute-NotExistingName.json", sw::WritingMode::Readable ) );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-Attribute-NotExistingName.json" ) );

        SerialObject root = deser.Root();

        REQUIRE( root.GetElement( "Value" ).has_value() == true );
        REQUIRE( root.GetElement( "Value" ).value().IsAttribute() );

        auto valueAttribute = root.GetElement( "Value" ).value().AttributeView().value();
        
        REQUIRE( valueAttribute.ConvertToInt64().has_value() == true );
        CHECK( valueAttribute.ConvertToInt64().value() == 12345678 );
    }
}
