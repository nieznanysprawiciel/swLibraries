#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Common/Buffers/Image.h"
#include "swCommonLib/Common/Buffers/ImageRegion.h"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"



using namespace sw;


// ================================ //
//
TEST_CASE( "Common.Buffers.Image.Create.FromWidthHeight" )
{
	Image< uint32 > image( 10, 11 );

	CHECK( image.GetRawData() != nullptr );
	CHECK( image.ElementsCount() == 110 );
	CHECK( image.ElementSize() == 4 );
	CHECK( image.GetType() == TypeID::get< uint32 >() );
	CHECK( image.GetSize() == image.ElementsCount() * sizeof( uint32 ) );
	
	CHECK( image.GetChannels() == 4 );
	CHECK( image.GetHeight() == 11 );
	CHECK( image.GetWidth() == 10 );

	auto ptr = image.GetRawData();
    auto buffer = image.Move();
	CHECK( buffer.GetRawData() != nullptr );
	CHECK( buffer.GetRawData() == ptr );
	CHECK( buffer.ElementsCount() == 110 );
	CHECK( buffer.ElementSize() == 4 );
	CHECK( buffer.GetType() == TypeID::get< uint32 >() );
	CHECK( buffer.GetSize() == 110 * sizeof( uint32 ) );
}

// ================================ //
//
TEST_CASE( "Common.Buffers.Image.Create.FromBuffer" )
{
    BufferTyped< uint32 > srcBuffer( 10 * 11 );
	Image< uint32 > image( std::move( srcBuffer ), 10, 11 );

	CHECK( image.GetRawData() != nullptr );
	CHECK( image.ElementsCount() == 110 );
	CHECK( image.ElementSize() == 4 );
	CHECK( image.GetType() == TypeID::get< uint32 >() );
	CHECK( image.GetSize() == image.ElementsCount() * sizeof( uint32 ) );

	CHECK( image.GetChannels() == 4 );
	CHECK( image.GetHeight() == 11 );
	CHECK( image.GetWidth() == 10 );

	auto ptr = image.GetRawData();
	auto buffer = image.Move();
	CHECK( buffer.GetRawData() != nullptr );
	CHECK( buffer.GetRawData() == ptr );
	CHECK( buffer.ElementsCount() == 110 );
	CHECK( buffer.ElementSize() == 4 );
	CHECK( buffer.GetType() == TypeID::get< uint32 >() );
	CHECK( buffer.GetSize() == 110 * sizeof( uint32 ) );
}

// ================================ //
//
TEST_CASE( "Common.Buffers.ImageRegion.Create" )
{
	Image< uint32 > image( 100, 110 );
    auto region = ImageRegion< uint32 >::From( image, { 10, 10, 10, 10 } ).Get();

	CHECK( region.ElementsCount() == 11000 );
	CHECK( region.ElementSize() == 4 );
	CHECK( region.GetType() == TypeID::get< uint32 >() );
	CHECK( region.GetSize() == image.ElementsCount() * sizeof( uint32 ) );

	CHECK( region.GetChannels() == 4 );
	CHECK( region.GetHeight() == 10 );
	CHECK( region.GetWidth() == 10 );
	CHECK( region.GetOriginalImageWidth() == 100 );
	CHECK( region.GetOriginalImageHeight() == 110 );
}

// ================================ //
//
TEST_CASE( "Common.Buffers.ImageRegion.Create.RegionOutside" )
{
	Image< uint32 > image( 100, 110 );

    REQUIRE_INVALID( ImageRegion< uint32 >::From( image, { 100, 10, 10, 10 } ) );
	REQUIRE_INVALID( ImageRegion< uint32 >::From( image, { 10, 105, 10, 10 } ) );
	REQUIRE_INVALID( ImageRegion< uint32 >::From( image, { 200, 10, 10, 10 } ) );
	REQUIRE_INVALID( ImageRegion< uint32 >::From( image, { 10, 200, 10, 10 } ) );
	
	REQUIRE_IS_VALID( ImageRegion< uint32 >::From( image, { 90, 10, 10, 10 } ) );
	REQUIRE_IS_VALID( ImageRegion< uint32 >::From( image, { 10, 100, 10, 10 } ) );
}

// ================================ //
//
TEST_CASE( "Common.Buffers.ImageRegion.AccessPixel" )
{
	Image< uint32 > image( 100, 100 );
	auto region = ImageRegion< uint32 >::From( image, { 10, 10, 10, 10 } ).Get();
	image.ZeroMemory();

	const uint32 pixelSet = 0xFFBBCCAA;

	// These pixels should be set properly
    region( 0, 0 ) = pixelSet;
	region( 3, 5 ) = pixelSet;
	region( 9, 9 ) = pixelSet;
	// These pixels are outside of ImageRegion
	region( 10, 10 ) = pixelSet;
	region( 15, 15 ) = pixelSet;
	region( 100, 100 ) = pixelSet;
	region( 50, 200 ) = pixelSet;
	region( 200, 200 ) = pixelSet;

    CHECK( image( 10, 10 ) == pixelSet );
	CHECK( image( 13, 15 ) == pixelSet );
	CHECK( image( 19, 19 ) == pixelSet );
	CHECK( image( 20, 20 ) == 0x0 );
	CHECK( image( 25, 25 ) == 0x0 );
	
	// Only 3 pixels that were set correctly should be writen to memory.
	// All other pixels should be untouched.
    uint64 numPixelsSet = 0;
	uint64 numNonZeroPixels = 0;
	for( size_t i = 0; i < image.ElementsCount(); i++ )
	{
        auto pixel = *(image.GetData() + i);
        if( pixel == pixelSet )
            numPixelsSet++;

		if( pixel != 0x0 )
			numNonZeroPixels++;
	}

    CHECK( numPixelsSet == 3 );
    CHECK( numNonZeroPixels == 3 );
}

