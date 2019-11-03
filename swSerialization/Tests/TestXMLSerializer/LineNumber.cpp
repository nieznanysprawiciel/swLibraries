#include "swCommonLib/External/Catch/catch.hpp"

#include "swSerialization/Interfaces/Serializer.h"
#include "swSerialization/Interfaces/Deserializer.h"


// ================================ //
// Gets line number while serializer sits in Object.
TEST_CASE( "Deserialization.XML.LineNumber.Object", "[Serializers]" )
{
	IDeserializer deser;
	REQUIRE( deser.LoadFromFile( "SerializerTest/XML/Serialization.LineNumber.xml", ParsingMode::ParseInsitu ) );
	REQUIRE( deser.EnterObject( "FirstObject" ) );
	REQUIRE( deser.EnterObject( "Object" ) );

	auto lineNumber = deser.CurrentLineNumber();
	CHECK( lineNumber.Line == 6 );
	CHECK( lineNumber.CharPosition == 3 );
}


