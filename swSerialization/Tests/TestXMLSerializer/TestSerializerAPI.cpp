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
TEST_CASE( "Serializer.XML.SerialObject.AddAttributes", "[Serializers][SerializerXML]" )
{
    {
        SerializerXML ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        auto firstObject = root.AddObject( "FirstObject" );

        firstObject.AddAttribute( "Map", "LightmapGen1" );
        firstObject.AddAttribute( "Path", "/LightmapGen1.map" );
        firstObject.AddAttribute( "Load", true );
        firstObject.AddAttribute( "Number", 32 );
        firstObject.AddAttribute( "Floating", 32.4362 );
        firstObject.AddAttribute( "Type", 'g' );

        auto saveResult = ser.SaveFile( "SerializerTest/XML/Generated/", sw::WritingMode::Readable );
        REQUIRE_IS_VALID( saveResult );
    }

    {
        SerializerXML deser( std::make_unique< ISerializationContext >() );
        auto loadResult = deser.LoadFromFile( "SerializerTest/XML/Generated/" );
        REQUIRE_IS_VALID( loadResult );

        SerialObject root = deser.Root();


    }
}



