#include "swCommonLib/External/Catch/catch.hpp"

#include "swSerialization/Interfaces/Serializer.h"
#include "swSerialization/Interfaces/Deserializer.h"



// ================================ //
// Gets name of current object while serializer resides in Object.
TEST_CASE( "Deserialization.JSON.GetName.Object", "[Serializers]" )
{
	IDeserializer deser;
	REQUIRE( deser.LoadFromFile( "SerializerTest/JSON/Serialization.LineNumber.json", ParsingMode::ParseInsitu ) );
	
	REQUIRE( deser.EnterObject( "FirstObject" ) );
	CHECK( deser.GetName() == std::string( "FirstObject" ) );
	
	REQUIRE( deser.EnterObject( "Object" ) );
	CHECK( deser.GetName() == std::string( "Object" ) );
}



// ================================ //
// Gets name of current object while serializer resides in Array.
TEST_CASE( "Deserialization.JSON.GetName.Array", "[Serializers]" )
{
	IDeserializer deser;
	REQUIRE( deser.LoadFromFile( "SerializerTest/JSON/Serialization.LineNumber.json", ParsingMode::ParseInsitu ) );
	REQUIRE( deser.EnterObject( "FirstObject" ) );
	REQUIRE( deser.EnterArray( "Array" ) );
	REQUIRE( deser.FirstElement() );

	CHECK( deser.GetName() == std::string() );
}
