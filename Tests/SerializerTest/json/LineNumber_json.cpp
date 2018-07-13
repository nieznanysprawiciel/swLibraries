#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Serialization/Serializer.h"
#include "swCommonLib/Serialization/Deserializer.h"



// ================================ //
// Gets line number while serializer resides in Object.
TEST_CASE( "Deserialization.JSON.LineNumber.Object", "[Serializers]" )
{
	IDeserializer deser;
	REQUIRE( deser.LoadFromFile( "SerializerTest/JSON/Serialization.LineNumber.json", ParsingMode::ParseInsitu ) );
	REQUIRE( deser.EnterObject( "FirstObject" ) );
	REQUIRE( deser.EnterObject( "Object" ) );

	auto lineNumber = deser.CurrentLineNumber();
	CHECK( lineNumber.Line == 10 );
	CHECK( lineNumber.CharPosition == 10 );
}


// ================================ //
// Gets line number while serializer resides in Array.
TEST_CASE( "Deserialization.JSON.LineNumber.Array", "[Serializers]" )
{
	IDeserializer deser;
	REQUIRE( deser.LoadFromFile( "SerializerTest/JSON/Serialization.LineNumber.json", ParsingMode::ParseInsitu ) );
	REQUIRE( deser.EnterObject( "FirstObject" ) );
	REQUIRE( deser.EnterArray( "Array" ) );
	REQUIRE( deser.FirstElement() );

	auto lineNumber = deser.CurrentLineNumber();
	CHECK( lineNumber.Line == 7 );
	CHECK( lineNumber.CharPosition == 13 );

	REQUIRE( deser.NextElement() );

	lineNumber = deser.CurrentLineNumber();
	CHECK( lineNumber.Line == 8 );
	CHECK( lineNumber.CharPosition == 13 );
}
