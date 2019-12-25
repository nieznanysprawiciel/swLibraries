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
TEST_CASE( "Serializer.JSON.SerialAttribute.Conversions.Int", "[Serializers][SerializerXML]" )
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
    }
}

