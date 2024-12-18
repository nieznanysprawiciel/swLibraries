#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"

#include <windows.h>
#include <fstream>
#include <numeric>
#undef max
#undef min

#include "swSerialization/Interfaces/Serializer.h"
#include "swSerialization/Interfaces/Deserializer.h"


#ifdef TEST_JSON
	std::string writeFileName = "SerializerTest/serialWrite.json";
	std::string readFileName = "SerializerTest/serialRead.json";
	std::ofstream outputFile( "SerializerTest/testResultJSON.txt" );
#elif TEST_XML
	std::string writeFileName = "SerializerTest/serialWrite.xml";
	std::string readFileName = "SerializerTest/serialRead.xml";
	std::ofstream outputFile( "SerializerTest/testResultXML.txt" );
#endif


// ================================ //
//
int		SerializeToFile		()
{
	ISerializer serializer( std::make_unique< ISerializationContext >() );

	serializer.SetAttribute( "FreeValue", "value" );	// Nie pojawi si� w XMLu.
	serializer.EnterObject( "FirstObject" );
		serializer.SetAttribute( "Map", "LightmapGen1" );
		serializer.SetAttribute( "Path", "/LightmapGen1.map" );
		serializer.SetAttribute( "Load", true );
		serializer.EnterObject( "Data" );
			serializer.SetAttribute( "NumberUnits", 1266643 );
			serializer.SetAttribute( "PositionOffset", 0.4124667623 );
			serializer.SetAttribute( "Visible", true );
			serializer.SetAttribute( "Key", 218588284382834538 );
		serializer.Exit();	// Data

		serializer.EnterArray( "Actors" );
			for( unsigned int i = 0; i < 12; ++i )
			{
				serializer.EnterObject( "Actor" );
					serializer.SetAttribute( "Name", std::string( "TIE Fighter " ) + std::to_string( i ) );
					serializer.EnterObject( "Position" );
						serializer.SetAttribute( "X", 12 );
						serializer.SetAttribute( "Y", 12 );
						serializer.SetAttribute( "Z", 12 );
					serializer.Exit();
				serializer.Exit();
			}
		serializer.Exit();	// Actors



		serializer.EnterArray( "Assets" );
			serializer.SetAttribute( "Asset", "TIE Fighter model" );
			serializer.SetAttribute( "Asset", "Nebulon B" );
			serializer.SetAttribute( "Asset", "Death Star" );
			serializer.SetAttribute( "Asset", "Calamarian Cruiser" );
			serializer.SetAttribute( "Asset", "Star Destroyer" );
		serializer.Exit();	// Assets

		// Nie wiem czy takie co� ma sens
		serializer.EnterArray( "Passes" );
			serializer.EnterArray( "Lights" );
				serializer.SetAttribute( "light", "directional" );
				serializer.SetAttribute( "light", "point" );
			serializer.Exit();	//	Lights
		serializer.Exit();	// Passes

		serializer.EnterObject( "Data1" );
			serializer.SetAttribute( "Map", "LightmapGen1" );
			serializer.SetAttribute( "Path", "/LightmapGen1.map" );
			serializer.SetAttribute( "Load", true );
		serializer.Exit();	// Data

		serializer.EnterObject( "Data2" );
			serializer.SetAttribute( "Asset1", "TIE Fighter model" );
			serializer.SetAttribute( "Asset2", "Nebulon B" );
			serializer.SetAttribute( "Asset3", "Death Star" );
			serializer.SetAttribute( "Asset4", "Calamarian Cruiser" );
			serializer.SetAttribute( "Asset5", "Star Destroyer" );
		serializer.Exit();	// Data2

		serializer.EnterObject( "Data3" );
			serializer.SetAttribute( "NumberUnits", std::numeric_limits<uint32>::max() );
			serializer.SetAttribute( "UnitsModifier", std::numeric_limits<int32>::min() );
			serializer.SetAttribute( "PositionOffset", 0.412466762375758958574674674764488949497747648 );
			serializer.SetAttribute( "Visible", true );
			serializer.SetAttribute( "Key", std::numeric_limits<int64>::min() );
			serializer.SetAttribute( "KeyHash", std::numeric_limits<uint64>::max() );
		serializer.Exit();	// Data3

		serializer.EnterArray( "ActorEnemies" );
			for( unsigned int i = 0; i < 30; ++i )
			{
				serializer.EnterObject( "ActorEnemy" );
					serializer.SetAttribute( "Name", std::string( "X-wing " ) + std::to_string( i ) );
					serializer.EnterObject( "Position" );
						serializer.SetAttribute( "X", 15 );
						serializer.SetAttribute( "Y", 124 );
						serializer.SetAttribute( "Z", 97 );
					serializer.Exit();	// Position
				serializer.Exit();	// ActorEnemy
			}
		serializer.Exit();	// ActorEnemies

		// Iteracja po zwyk�ym obiekcie (zamiast tablicy)
		serializer.EnterObject( "ButtonContainer" );
			
			serializer.EnterObject( "PushButton" );
				serializer.SetAttribute( "ButtonName", "Exit" );
				serializer.SetAttribute( "Visible", true );
			serializer.Exit();	// PushButton

			serializer.EnterObject( "PushButton" );
				serializer.SetAttribute( "ButtonName", "Start" );
				serializer.SetAttribute( "Visible", true );
			serializer.Exit();	// PushButton

			serializer.EnterObject( "TriStateButton" );
				serializer.SetAttribute( "ButtonName", "GameMode" );
				serializer.SetAttribute( "Visible", false );
			serializer.Exit();	// TriStateButton

			serializer.EnterObject( "SwitchButton" );
				serializer.SetAttribute( "ButtonName", "GameMode2" );
				serializer.SetAttribute( "Visible", true );
			serializer.Exit();	// SwitchButton

			serializer.EnterObject( "SelectField" );
				serializer.SetAttribute( "ButtonName", "TankType" );
				serializer.SetAttribute( "Visible", true );
			serializer.Exit();	// SelectField

		serializer.Exit();	// ButtonContainer

	serializer.Exit();	// FirstObject


	if( !serializer.SaveFile( readFileName, WritingMode::Readable ).IsValid() )
#ifdef TEST_JSON
		OutputDebugString( L"Error: Saving \"SerializerTest/serialWrite.json\" failed!\n" );
#elif TEST_XML
		OutputDebugString( L"Error: Saving \"SerializerTest/serialWrite.xml\" failed!\n" );
#endif

	return 2;
}

int staticInit = SerializeToFile();


// ================================ //
//
TEST_CASE( "Deserialization.GetAttributes", "[Serializers]" )
{
	IDeserializer deser;
	REQUIRE_IS_VALID( deser.LoadFromFile( readFileName ) );

	REQUIRE( deser.EnterObject( "FirstObject" ) );

		CHECK( deser.GetAttribute( "Map", "GetAttribute error" ) == std::string( "LightmapGen1" ) );
		CHECK( deser.GetAttribute( "Path", "GetAttribute error" ) == std::string( "/LightmapGen1.map" ) );
		CHECK( deser.GetAttribute( "Load", "GetAttribute error" ) );

		REQUIRE( deser.EnterObject( "Data" ) );
			CHECK( deser.GetAttribute( "NumberUnits", 0 ) == 1266643 );
			CHECK( deser.GetAttribute( "PositionOffset", 0.0 ) == 0.4124667623 );
			CHECK( deser.GetAttribute( "Visible", false ) == true );
			CHECK( deser.GetAttribute( "Key", 418588284382834538 ) == 218588284382834538 );
		deser.Exit();	// Data
	deser.Exit();	// FirstObject
}

// ================================ //
//
TEST_CASE( "Deserialization.Array.ForwardIteration", "[Serializers]" )
{
	IDeserializer deser;
    REQUIRE_IS_VALID( deser.LoadFromFile( readFileName ) );

	REQUIRE( deser.EnterObject( "FirstObject" ) );
		REQUIRE( deser.EnterArray( "Actors" ) );
			REQUIRE( deser.FirstElement() );
			
			int numElements = 0;
				
			do
			{
				CHECK( deser.GetAttribute( "Name", "Wrong string" ) == "TIE Fighter " + std::to_string( numElements ) );
					
				REQUIRE( deser.EnterObject( "Position" ) );
					CHECK( deser.GetAttribute( "X", 0 ) == 12 );
					CHECK( deser.GetAttribute( "Y", 0 ) == 12 );
					CHECK( deser.GetAttribute( "Z", 0 ) == 12 );
				deser.Exit();

				numElements++;

			} while( deser.NextElement() );

			CHECK( numElements == 12 );

			deser.Exit();	// FirstElement()
		deser.Exit();	// Actors
		
	// Check state after going through array.
	CHECK( deser.EnterArray( "Actors" ) );
}

// ================================ //
//
TEST_CASE( "Deserialization.Array.BackwardIteration", "[Serializers]" )
{
	IDeserializer deser;
    REQUIRE_IS_VALID( deser.LoadFromFile( readFileName ) );

	REQUIRE( deser.EnterObject( "FirstObject" ) );
		REQUIRE( deser.EnterArray( "ActorEnemies" ) );
			REQUIRE( deser.LastElement() );
			
			int numElements = 29;
				
			do
			{
				CHECK( deser.GetAttribute( "Name", "Wrong string" ) == "X-wing " + std::to_string( numElements ) );
					
				REQUIRE( deser.EnterObject( "Position" ) );
					CHECK( deser.GetAttribute( "X", 0 ) == 15 );
					CHECK( deser.GetAttribute( "Y", 0 ) == 124 );
					CHECK( deser.GetAttribute( "Z", 0 ) == 97 );
				deser.Exit();

				numElements--;

			} while( deser.PrevElement() );

			CHECK( numElements == -1 );

			deser.Exit();	// LastElement()
		deser.Exit();	// Actors
		
	// Check state after going through array.
	CHECK( deser.EnterArray( "ActorEnemies" ) );

}

// ================================ //
//
TEST_CASE( "Serialization.Array.ArrayAttribute", "[Serializers]" )
{
	ISerializer ser( std::make_unique< ISerializationContext >() );

	ser.EnterObject( "FirstObject" );
	ser.EnterArray( "Array" );
	ser.SetAttribute( "ArraySize", 13 );
	ser.EnterObject( "Object1" );

	ser.SaveFile( "SerializerTest/Serialization.Array.ArrayAttribute.serialized", WritingMode::Readable );

	IDeserializer deser;
    REQUIRE_IS_VALID( deser.LoadFromFile( "SerializerTest/Serialization.Array.ArrayAttribute.serialized" ) );
	REQUIRE( deser.EnterObject( "FirstObject" ) );
	REQUIRE( deser.EnterArray( "Array" ) );

	CHECK( deser.GetAttribute( "ArraySize", 0 ) == 13 );
	
	// Serializer should Enter Object1 without problems.
	CHECK( deser.FirstElement() );
}


// ================================ //
// Iterates over elements in object. Iteration should enter all objects and arrays.
TEST_CASE( "Deserialization.Object.ForwardIteration", "[Serializers]" )
{
	IDeserializer deser;
    REQUIRE_IS_VALID( deser.LoadFromFile( readFileName ) );

	REQUIRE( deser.EnterObject( "FirstObject" ) );
		REQUIRE( deser.FirstElement() );	// Data

		CHECK( deser.GetName() == std::string( "Data" ) );
		
		REQUIRE( deser.NextElement() );
		CHECK( deser.GetName() == std::string( "Actors" ) );

		REQUIRE( deser.NextElement() );
		CHECK( deser.GetName() == std::string( "Assets" ) );

		REQUIRE( deser.NextElement() );
		CHECK( deser.GetName() == std::string( "Passes" ) );

		REQUIRE( deser.NextElement() );
		CHECK( deser.GetName() == std::string( "Data1" ) );

		REQUIRE( deser.NextElement() );
		CHECK( deser.GetName() == std::string( "Data2" ) );

		REQUIRE( deser.NextElement() );
		CHECK( deser.GetName() == std::string( "Data3" ) );

		REQUIRE( deser.NextElement() );
		CHECK( deser.GetName() == std::string( "ActorEnemies" ) );

		REQUIRE( deser.NextElement() );
		CHECK( deser.GetName() == std::string( "ButtonContainer" ) );

		// No elements left.
		REQUIRE( !deser.NextElement() );

		deser.Exit();	// Data
	deser.Exit();	// FirstObject
}

// ================================ //
// Iterates over elements in object. Iteration should enter all objects and arrays.
TEST_CASE( "Deserialization.Object.BackwardIteration", "[Serializers]" )
{
	IDeserializer deser;
	REQUIRE_IS_VALID( deser.LoadFromFile( readFileName ) );

	REQUIRE( deser.EnterObject( "FirstObject" ) );
		REQUIRE( deser.LastElement() );	// Data

		CHECK( deser.GetName() == std::string( "ButtonContainer" ) );
		
		REQUIRE( deser.PrevElement() );
		CHECK( deser.GetName() == std::string( "ActorEnemies" ) );

		REQUIRE( deser.PrevElement() );
		CHECK( deser.GetName() == std::string( "Data3" ) );

		REQUIRE( deser.PrevElement() );
		CHECK( deser.GetName() == std::string( "Data2" ) );

		REQUIRE( deser.PrevElement() );
		CHECK( deser.GetName() == std::string( "Data1" ) );

		REQUIRE( deser.PrevElement() );
		CHECK( deser.GetName() == std::string( "Passes" ) );

		REQUIRE( deser.PrevElement() );
		CHECK( deser.GetName() == std::string( "Assets" ) );

		REQUIRE( deser.PrevElement() );
		CHECK( deser.GetName() == std::string( "Actors" ) );

		REQUIRE( deser.PrevElement() );
		CHECK( deser.GetName() == std::string( "Data" ) );

		// No elements left.
		REQUIRE( !deser.PrevElement() );

		deser.Exit();	// ButtonContainer
	deser.Exit();	// FirstObject
}


int main_bla()
{
	SerializeToFile();

	IDeserializer deser;


	if( deser.LoadFromFile( readFileName ).IsValid() )
	{
		outputFile << deser.GetAttribute( "FreeValue", "GetAttribute error" ) << std::endl;
		deser.EnterObject( "FirstObject" );
			outputFile << deser.GetAttribute( "Map", "GetAttribute error" ) << std::endl;
			outputFile << deser.GetAttribute( "Path", "GetAttribute error" ) << std::endl;
			outputFile << deser.GetAttribute( "Load", false ) << std::endl;
			deser.EnterObject( "Data" );
				outputFile << deser.GetAttribute( "NumberUnits", 0 ) << std::endl;
				outputFile << deser.GetAttribute( "PositionOffset", 0.0 ) << std::endl;
				outputFile << deser.GetAttribute( "Visible", false ) << std::endl;
				outputFile << deser.GetAttribute( "Key", 0 ) << std::endl;
			deser.Exit();	// Data
		if( deser.EnterArray( "Actors" ) )
		{
			if( deser.FirstElement() )
			{
				do
				{
					outputFile << deser.GetAttribute( "Name", "Wrong string" ) << std::endl;
					
					deser.EnterObject( "Position" );
						outputFile << "\t" << deser.GetAttribute( "X", 0 ) << std::endl;
						outputFile << "\t" << deser.GetAttribute( "Y", 0 ) << std::endl;
						outputFile << "\t" << deser.GetAttribute( "Z", 0 ) << std::endl;
					deser.Exit();

				} while( deser.NextElement() );
				//deser.Exit();		// Mo�e to jest do wyrzucenia. Serializator m�g�by sam wycyhodzi�.
			}

			deser.Exit();	// Actors
		}

		if( deser.EnterObject( "Data1" ) )
		{
			outputFile << deser.GetAttribute( "Map", "GetAttribute error" ) << std::endl;
			outputFile << deser.GetAttribute( "Path", "GetAttribute error" ) << std::endl;
			outputFile << deser.GetAttribute( "Load", false ) << std::endl;

			deser.Exit();	// Data1
		}

		if( deser.EnterObject( "Data2" ) )
		{
			outputFile << deser.GetAttribute( "Asset1", "GetAttribute error" ) << std::endl;
			outputFile << deser.GetAttribute( "Asset2", "GetAttribute error" ) << std::endl;
			outputFile << deser.GetAttribute( "Asset3", "GetAttribute error" ) << std::endl;
			outputFile << deser.GetAttribute( "Asset4", "GetAttribute error" ) << std::endl;
			outputFile << deser.GetAttribute( "Asset5", "GetAttribute error" ) << std::endl;

			deser.Exit();	// Data2
		}

		if( deser.EnterObject( "Data3" ) )
		{
			outputFile << deser.GetAttribute( "NumberUnits", (uint32)0 ) << std::endl;
			outputFile << deser.GetAttribute( "UnitsModifier", (int32)0 ) << std::endl;
			outputFile << deser.GetAttribute( "PositionOffset", 0.0 ) << std::endl;
			outputFile << deser.GetAttribute( "Visible", false ) << std::endl;
			outputFile << deser.GetAttribute( "Key", (int64)0 ) << std::endl;
			outputFile << deser.GetAttribute( "KeyHash", (uint64)0 ) << std::endl;
			
			deser.Exit();	// Data3
		}

		if( deser.EnterArray( "ActorEnemies" ) )
		{
			if( deser.LastElement() )
			{
				do
				{
					outputFile << deser.GetAttribute( "Name", "Wrong string" ) << std::endl;
					
					deser.EnterObject( "Position" );
						outputFile << "\t" << deser.GetAttribute( "X", 0 ) << std::endl;
						outputFile << "\t" << deser.GetAttribute( "Y", 0 ) << std::endl;
						outputFile << "\t" << deser.GetAttribute( "Z", 0 ) << std::endl;
					deser.Exit();

				} while( deser.PrevElement() );
				//deser.Exit();		// Mo�e to jest do wyrzucenia. Serializator m�g�by sam wycyhodzi�.
			}

			deser.Exit();	// ActorEnemies
		}

		if( deser.EnterObject( "ButtonContainer" ) )
		{
			if( deser.FirstElement() )
			{
				do
				{
					outputFile << "Name: " << deser.GetName() << std::endl;
					outputFile << "\tButtonName: " << deser.GetAttribute( "ButtonName", "Wrong string" ) << std::endl;
					outputFile << "\tVisible: " << deser.GetAttribute( "Visible", false ) << std::endl;

				} while( deser.NextElement() );
			}
			deser.Exit();	// ButtonContainer
		}

		deser.Exit();	// FirstObject

	}
	else
	{
		std::string errorMessage = deser.GetError();
		OutputDebugString( std::wstring( errorMessage.begin(), errorMessage.end() ).c_str() );
		OutputDebugString( L"\n" );
	}

	return 0;
}