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
TEST_CASE( "Serializer.XML.SerialObject.AddObject", "[Serializers][SerializerXML]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        auto firstObject = root.AddObject( "FirstObject" );

        auto saveResult = ser.SaveFile( "SerializerTest/JSON/Generated/Test-AddObject.xml", sw::WritingMode::Readable );
        REQUIRE_IS_VALID( saveResult );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        auto loadResult = deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-AddObject.xml" );
        REQUIRE_IS_VALID( loadResult );

        SerialObject root = deser.Root();
        REQUIRE( root.GetElement( "FirstObject" ).has_value() );
        REQUIRE( root.GetElement( "FirstObject" ).value().IsObject() );
    }
}


