#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Common/Buffers/BufferTyped.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructWithSimpleTypes.h"



using namespace sw;


// ================================ //
//
TEST_CASE( "Common.Buffers.BufferTyped.Create" )
{
	BufferTyped< StructWithSimpleTypes > buffer( 10 );

	CHECK( buffer.GetRawData() != nullptr );
	CHECK( buffer.ElementsCount() == 10 );
	CHECK( buffer.GetType() == TypeID::get< StructWithSimpleTypes >() );
	CHECK( buffer.GetSize() == 10 * sizeof( StructWithSimpleTypes ) );
}

// ================================ //
// BufferTyped can be converted to BufferRaw and back.
TEST_CASE( "Common.Buffers.BufferTyped.ToRawBuffer" )
{
	StructWithSimpleTypes example;
	example.FillWithDataset3();

	BufferTyped< StructWithSimpleTypes > buffer( 10 );
	auto prevPtr = buffer.GetRawData();

	// Fill with example data.
	for( int i = 0; i < 10; ++i )
		buffer[ i ] = example;

	BufferRaw rawBuffer = buffer.MoveToRawBuffer();

	// buffer object should be empty.
	CHECK( buffer.GetRawData() == nullptr );
	CHECK( buffer.GetSize() == 0 );
	CHECK( buffer.ElementsCount() == 0 );
	CHECK( buffer.IsValid() == false );

	CHECK( rawBuffer.GetData() == prevPtr );
	CHECK( rawBuffer.GetSize() == 10 * sizeof( StructWithSimpleTypes ) );
	CHECK( rawBuffer.IsValid() == true );


	BufferTyped< StructWithSimpleTypes > buffer2( std::move( rawBuffer ) );

	CHECK( rawBuffer.GetData() == nullptr );
	CHECK( rawBuffer.GetSize() == 0 );
	CHECK( rawBuffer.IsValid() == false );

	CHECK( buffer2.GetRawData() == prevPtr );
	CHECK( buffer2.GetSize() == 10 * sizeof( StructWithSimpleTypes ) );
	CHECK( buffer2.ElementsCount() == 10 );
	CHECK( buffer2.IsValid() == true );
	CHECK( buffer2[ 3 ] == example );
}

// ================================ //
//
TEST_CASE( "Common.Buffers.BufferTyped.CreateEmpty" )
{
	auto buffer = BufferTyped< StructWithSimpleTypes >::CreateEmpty();

	CHECK( buffer.GetData() == nullptr );
	CHECK( buffer.GetSize() == 0 );
	CHECK( buffer.GetType() == TypeID::get< StructWithSimpleTypes >() );
}

// ================================ //
//
TEST_CASE( "Common.Buffers.BufferTyped.FromMemory" )
{
	StructWithSimpleTypes* array = new StructWithSimpleTypes[ 3 ];
	auto buffer = BufferTyped< StructWithSimpleTypes >::StealMemory( std::move( array ), 3 );
	
	CHECK( array == nullptr );
	CHECK( buffer.GetRawData() != nullptr );
	CHECK( buffer.ElementsCount() == 3 );
	CHECK( buffer.GetType() == TypeID::get< StructWithSimpleTypes >() );
	CHECK( buffer.GetSize() == 3 * sizeof( StructWithSimpleTypes ) );
}
