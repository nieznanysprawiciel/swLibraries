/**
@file TestSerializerAPI.cppp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swCommonLib/External/Catch/catch.hpp"


#include "swSerialization/Serializers/SerializerXML/SerializerXML.h"


// ================================ //
//
TEST_CASE( "SerializerXML", "[Serializers][SerializerXML]" )
{
    sw::SerializerXML ser( std::make_unique< ISerializationContext >() );


}



