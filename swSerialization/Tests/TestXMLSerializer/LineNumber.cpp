#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"

#include "swSerialization/Interfaces/Serializer.h"
#include "swSerialization/Interfaces/Deserializer.h"


// ================================ //
// Gets line number while serializer sits in Object.
TEST_CASE( "Deserialization.XML.LineNumber.Object", "[Serializers]" )
{
	IDeserializer deser;
	REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/XML/Serialization.LineNumber.xml" ) );
	REQUIRE( deser.EnterObject( "FirstObject" ) );
	REQUIRE( deser.EnterObject( "Object" ) );

	auto lineNumber = deser.CurrentLineNumber();
	CHECK( lineNumber.Line == 6 );
	CHECK( lineNumber.CharPosition == 3 );
}

// ================================ //
// Gets line number when deserialization failed due to parsing error.
TEST_CASE("Deserialization.XML.ParsingError.LineNumber", "[Serializers]")
{
	IDeserializer deser;
	auto result = deser.LoadFromFile("SerializerTest/XML/Serialization.ParsingError.LineNumber.xml");
	
	REQUIRE(!result.IsValid());
    
	INFO(result.GetErrorReason());
    CHECK(result.GetErrorReason().find("line: 2") != std::string::npos);
	CHECK(result.GetErrorReason().find("position: 17") != std::string::npos);
}
