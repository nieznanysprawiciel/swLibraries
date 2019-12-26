/**
@file TestAttributesConversion.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


#include "swSerialization/Serializers/SerializerJson/SerializerJSON.h"


using namespace sw;



// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialAttribute.Conversions.Int", "[Serializers][SerializerJSON]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        root.AddAttribute( "Value", 12345678 );

        REQUIRE_IS_VALID( ser.SaveFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Int.json", sw::WritingMode::Readable ) );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Int.json" ) );

        SerialObject root = deser.Root();

        REQUIRE( root.GetElement( "Value" ).has_value() == true );
        REQUIRE( root.GetElement( "Value" ).value().IsAttribute() );

        auto valueAttribute = root.GetElement( "Value" ).value().AttributeView().value();

        REQUIRE( valueAttribute.GetType() == SerialType::UInt64 );

        // Check other conversions.
        CHECK( valueAttribute.ConvertToInt64().has_value() == true );
        CHECK( valueAttribute.ConvertToInt32().has_value() == true );
        CHECK( valueAttribute.ConvertToInt16().has_value() == false );
        CHECK( valueAttribute.ConvertToInt8().has_value() == false );
        CHECK( valueAttribute.ConvertToDouble().has_value() == true );

        CHECK( valueAttribute.ConvertToUInt64().has_value() == true );
        CHECK( valueAttribute.ConvertToUInt32().has_value() == true );
        CHECK( valueAttribute.ConvertToUInt16().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt8().has_value() == false );

        CHECK( valueAttribute.ConvertToString().has_value() == false );
        CHECK( valueAttribute.ConvertToBool().has_value() == false );
        CHECK( valueAttribute.ConvertToChar().has_value() == false );

        CHECK( valueAttribute.ConvertToDouble().value() == 12345678 );
    }
}

// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialAttribute.Conversions.Int.Negative", "[Serializers][SerializerJSON]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        root.AddAttribute( "Value", -15 );

        REQUIRE_IS_VALID( ser.SaveFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Int-Negative.json", sw::WritingMode::Readable ) );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Int-Negative.json" ) );

        SerialObject root = deser.Root();

        REQUIRE( root.GetElement( "Value" ).has_value() == true );
        REQUIRE( root.GetElement( "Value" ).value().IsAttribute() );

        auto valueAttribute = root.GetElement( "Value" ).value().AttributeView().value();

        REQUIRE( valueAttribute.GetType() == SerialType::Int64 );

        // Check other conversions.
        CHECK( valueAttribute.ConvertToInt64().has_value() == true );
        CHECK( valueAttribute.ConvertToInt32().has_value() == true );
        CHECK( valueAttribute.ConvertToInt16().has_value() == true );
        CHECK( valueAttribute.ConvertToInt8().has_value() == true );
        CHECK( valueAttribute.ConvertToDouble().has_value() == true );

        CHECK( valueAttribute.ConvertToUInt64().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt32().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt16().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt8().has_value() == false );

        CHECK( valueAttribute.ConvertToString().has_value() == false );
        CHECK( valueAttribute.ConvertToBool().has_value() == false );
        CHECK( valueAttribute.ConvertToChar().has_value() == false );

        CHECK( valueAttribute.ConvertToInt64().value() == -15 );
    }
}

// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialAttribute.Conversions.Double", "[Serializers][SerializerJSON]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        root.AddAttribute( "Value", 13.765 );

        REQUIRE_IS_VALID( ser.SaveFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Double.json", sw::WritingMode::Readable ) );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Double.json" ) );

        SerialObject root = deser.Root();

        REQUIRE( root.GetElement( "Value" ).has_value() == true );
        REQUIRE( root.GetElement( "Value" ).value().IsAttribute() );

        auto valueAttribute = root.GetElement( "Value" ).value().AttributeView().value();

        REQUIRE( valueAttribute.GetType() == SerialType::Double );

        // Check other conversions.
        CHECK( valueAttribute.ConvertToInt64().has_value() == false );
        CHECK( valueAttribute.ConvertToInt32().has_value() == false );
        CHECK( valueAttribute.ConvertToInt16().has_value() == false );
        CHECK( valueAttribute.ConvertToInt8().has_value() == false );
        CHECK( valueAttribute.ConvertToDouble().has_value() == true );

        CHECK( valueAttribute.ConvertToUInt64().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt32().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt16().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt8().has_value() == false );

        CHECK( valueAttribute.ConvertToString().has_value() == false );
        CHECK( valueAttribute.ConvertToBool().has_value() == false );
        CHECK( valueAttribute.ConvertToChar().has_value() == false );

        CHECK( valueAttribute.ConvertToDouble().value() == 13.765 );
    }
}

// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialAttribute.Conversions.Double.Double-Integer", "[Serializers][SerializerJSON]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        root.AddAttribute( "Value", 13.0 );

        REQUIRE_IS_VALID( ser.SaveFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Double-Integer.json", sw::WritingMode::Readable ) );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Double-Integer.json" ) );

        SerialObject root = deser.Root();

        REQUIRE( root.GetElement( "Value" ).has_value() == true );
        REQUIRE( root.GetElement( "Value" ).value().IsAttribute() );

        auto valueAttribute = root.GetElement( "Value" ).value().AttributeView().value();

        REQUIRE( valueAttribute.GetType() == SerialType::Double );

        // Check other conversions.
        CHECK( valueAttribute.ConvertToInt64().has_value() == true );
        CHECK( valueAttribute.ConvertToInt32().has_value() == true );
        CHECK( valueAttribute.ConvertToInt16().has_value() == true );
        CHECK( valueAttribute.ConvertToInt8().has_value() == true );
        CHECK( valueAttribute.ConvertToDouble().has_value() == true );

        CHECK( valueAttribute.ConvertToUInt64().has_value() == true );
        CHECK( valueAttribute.ConvertToUInt32().has_value() == true );
        CHECK( valueAttribute.ConvertToUInt16().has_value() == true );
        CHECK( valueAttribute.ConvertToUInt8().has_value() == true );

        CHECK( valueAttribute.ConvertToString().has_value() == false );
        CHECK( valueAttribute.ConvertToBool().has_value() == false );
        CHECK( valueAttribute.ConvertToChar().has_value() == false );

        CHECK( valueAttribute.ConvertToDouble().value() == 13.0 );
    }
}

// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialAttribute.Conversions.Bool", "[Serializers][SerializerJSON]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        root.AddAttribute( "Value", false );

        REQUIRE_IS_VALID( ser.SaveFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Bool.json", sw::WritingMode::Readable ) );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Bool.json" ) );

        SerialObject root = deser.Root();

        REQUIRE( root.GetElement( "Value" ).has_value() == true );
        REQUIRE( root.GetElement( "Value" ).value().IsAttribute() );

        auto valueAttribute = root.GetElement( "Value" ).value().AttributeView().value();

        REQUIRE( valueAttribute.GetType() == SerialType::Bool );

        // Check other conversions.
        CHECK( valueAttribute.ConvertToInt64().has_value() == false );
        CHECK( valueAttribute.ConvertToInt32().has_value() == false );
        CHECK( valueAttribute.ConvertToInt16().has_value() == false );
        CHECK( valueAttribute.ConvertToInt8().has_value() == false );
        CHECK( valueAttribute.ConvertToDouble().has_value() == false );

        CHECK( valueAttribute.ConvertToUInt64().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt32().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt16().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt8().has_value() == false );

        CHECK( valueAttribute.ConvertToString().has_value() == false );
        CHECK( valueAttribute.ConvertToBool().has_value() == true );
        CHECK( valueAttribute.ConvertToChar().has_value() == false );

        CHECK( valueAttribute.ConvertToBool().value() == false );
    }
}

// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialAttribute.Conversions.String", "[Serializers][SerializerJSON]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        root.AddAttribute( "Value", "String attribute" );

        REQUIRE_IS_VALID( ser.SaveFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-String.json", sw::WritingMode::Readable ) );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-String.json" ) );

        SerialObject root = deser.Root();

        REQUIRE( root.GetElement( "Value" ).has_value() == true );
        REQUIRE( root.GetElement( "Value" ).value().IsAttribute() );

        auto valueAttribute = root.GetElement( "Value" ).value().AttributeView().value();

        REQUIRE( valueAttribute.GetType() == SerialType::String );

        // Check other conversions.
        CHECK( valueAttribute.ConvertToInt64().has_value() == false );
        CHECK( valueAttribute.ConvertToInt32().has_value() == false );
        CHECK( valueAttribute.ConvertToInt16().has_value() == false );
        CHECK( valueAttribute.ConvertToInt8().has_value() == false );
        CHECK( valueAttribute.ConvertToDouble().has_value() == false );

        CHECK( valueAttribute.ConvertToUInt64().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt32().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt16().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt8().has_value() == false );

        CHECK( valueAttribute.ConvertToString().has_value() == true );
        CHECK( valueAttribute.ConvertToBool().has_value() == false );
        CHECK( valueAttribute.ConvertToChar().has_value() == false );

        CHECK( valueAttribute.ConvertToString().value() == "String attribute" );
    }
}

// ================================ //
// String containing number will be converted succesfully. This design decision is caused by XML
// serializer, that don't have typed fields - only strings.
TEST_CASE( "Serializer.JSON.SerialAttribute.Conversions.String-Number", "[Serializers][SerializerJSON]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        root.AddAttribute( "Value", "13" );

        REQUIRE_IS_VALID( ser.SaveFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-String-Number.json", sw::WritingMode::Readable ) );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-String-Number.json" ) );

        SerialObject root = deser.Root();

        REQUIRE( root.GetElement( "Value" ).has_value() == true );
        REQUIRE( root.GetElement( "Value" ).value().IsAttribute() );

        auto valueAttribute = root.GetElement( "Value" ).value().AttributeView().value();

        REQUIRE( valueAttribute.GetType() == SerialType::String );

        // Check other conversions.
        CHECK( valueAttribute.ConvertToInt64().has_value() == true );
        CHECK( valueAttribute.ConvertToInt32().has_value() == true );
        CHECK( valueAttribute.ConvertToInt16().has_value() == true );
        CHECK( valueAttribute.ConvertToInt8().has_value() == true );
        CHECK( valueAttribute.ConvertToDouble().has_value() == true );

        CHECK( valueAttribute.ConvertToUInt64().has_value() == true );
        CHECK( valueAttribute.ConvertToUInt32().has_value() == true );
        CHECK( valueAttribute.ConvertToUInt16().has_value() == true );
        CHECK( valueAttribute.ConvertToUInt8().has_value() == true );

        CHECK( valueAttribute.ConvertToString().has_value() == true );
        CHECK( valueAttribute.ConvertToBool().has_value() == false );
        CHECK( valueAttribute.ConvertToChar().has_value() == false );

        CHECK( valueAttribute.ConvertToString().value() == "13" );
        CHECK( valueAttribute.ConvertToInt64().value() == 13 );
    }
}

// ================================ //
// Single characters strings can be converted to chars.
TEST_CASE( "Serializer.JSON.SerialAttribute.Conversions.Char", "[Serializers][SerializerJSON]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        root.AddAttribute( "Value", "G" );

        REQUIRE_IS_VALID( ser.SaveFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Char.json", sw::WritingMode::Readable ) );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-Attribute-Conversions-Char.json" ) );

        SerialObject root = deser.Root();

        REQUIRE( root.GetElement( "Value" ).has_value() == true );
        REQUIRE( root.GetElement( "Value" ).value().IsAttribute() );

        auto valueAttribute = root.GetElement( "Value" ).value().AttributeView().value();

        REQUIRE( valueAttribute.GetType() == SerialType::String );

        // Check other conversions.
        CHECK( valueAttribute.ConvertToInt64().has_value() == false );
        CHECK( valueAttribute.ConvertToInt32().has_value() == false );
        CHECK( valueAttribute.ConvertToInt16().has_value() == false );
        CHECK( valueAttribute.ConvertToInt8().has_value() == false );
        CHECK( valueAttribute.ConvertToDouble().has_value() == false );

        CHECK( valueAttribute.ConvertToUInt64().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt32().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt16().has_value() == false );
        CHECK( valueAttribute.ConvertToUInt8().has_value() == false );

        CHECK( valueAttribute.ConvertToString().has_value() == true );
        CHECK( valueAttribute.ConvertToBool().has_value() == false );
        CHECK( valueAttribute.ConvertToChar().has_value() == true );

        CHECK( valueAttribute.ConvertToChar().value() == 'G' );
    }
}
