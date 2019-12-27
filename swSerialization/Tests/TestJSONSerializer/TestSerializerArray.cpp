/**
@file TestSerializerArray.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


#include "swSerialization/Serializers/SerializerJson/SerializerJSON.h"


using namespace sw;





// ================================ //
//
TEST_CASE( "Serializer.JSON.SerialObject.AddArray", "[Serializers][SerializerJSON]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        auto firstArray = root.AddArray( "FirstArray" );

        auto saveResult = ser.SaveFile( "SerializerTest/JSON/Generated/Test-AddArray.json", sw::WritingMode::Readable );
        REQUIRE_IS_VALID( saveResult );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        auto loadResult = deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-AddArray.json" );
        REQUIRE_IS_VALID( loadResult );

        SerialObject root = deser.Root();
        REQUIRE( root.GetElement( "FirstArray" ).has_value() );
        REQUIRE( root.GetElement( "FirstArray" ).value().IsArray() );
        REQUIRE( !root.GetElement( "FirstArray" ).value().IsObject() );
    }
}


