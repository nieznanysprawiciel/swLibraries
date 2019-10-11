/**
@file MipMapGenerator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "MipMapGenerator.h"

#include "Resampler/resampler.h"
#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"


namespace sw
{


const int sMaxChannels = 4;

// ================================ //
//
MipMapGenerator::MipMapGenerator()
	: NumChannels( 4 )
{}

/**@brief Generates mipmaps

Set MipMapFilter field to filter that should be used.

If texture dimension isn't power of 2, this function will scale image and modify in TextureInfo structure these fields:
- Width
- Height

These fields will be modified, if non zero CutOffMipMaps value is set.
Then the biggest mipmap will become main texture .

Moreover two fileds are set:
- MipMapLevels
- MemorySize*/
sw::Nullable< BufferRaw >		MipMapGenerator::Generate	( const BufferRaw& source, TextureInfo& texInfo )
{
	if( texInfo.Format != ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM )
		return "[MipMapGenerator] Format isn't supported. Should be R8G8B8A8.";
	
	NumChannels = 4;

	uint16 newWidth = PowerOfTwo( texInfo.Width ) >> texInfo.CutOffMipMaps;
	uint16 newHeight = PowerOfTwo( texInfo.Height ) >> texInfo.CutOffMipMaps;
	texInfo.MipMapLevels = ComputeMipMapsLevels( newWidth, newHeight );

	if( newWidth == 0 || newHeight == 0 )
		return "[MipMapGenerator] Image should be at least 1 pixel size.";

	texInfo.MemorySize = ComputeBufferSize( newWidth, newHeight, NumChannels );
	BufferTyped< uint8 > texWithMips( texInfo.MemorySize );

	if( newWidth != texInfo.Width || newHeight != texInfo.Height )
	{
		// Przeskaluj teksturê, ¿eby jej wymiary by³y potêg¹ dwójki.
		Resample( texInfo.Width, texInfo.Height, newWidth, newHeight, source.GetData(), texWithMips.GetRawData(), texInfo.MipMapFilter );
	}
	else
	{
		// Przekopiuj oryginalny obraz do nowego bufora.
		memcpy( texWithMips.GetRawData(), source.GetData(), source.GetSize() );
	}

	// Aktualizujemy informacje o teksturze.
	texInfo.Width = newWidth;
	texInfo.Height = newHeight;

	PtrOffset offset = 0;
	PtrOffset prevOffset = 0;
	uint16 prevWidth = newWidth;
	uint16 prevHeight = newHeight;

	// Tworzenie mipmap. Zaczynamy od pierwszego poziomu, bo zerowa tekstura jest ju¿ w buforze (tekstura oryginalna).
	for( int level = 1; level < texInfo.MipMapLevels; level++ )
	{
		offset += prevWidth * prevHeight * NumChannels;
		newWidth /= 2;
		newHeight /= 2;

		if( newHeight == 0 )
			newHeight = 1;
		if( newWidth == 0 )
			newWidth = 1;

		Resample( prevWidth, prevHeight, newWidth, newHeight, texWithMips.GetRawData() + prevOffset, texWithMips.GetRawData() + offset, texInfo.MipMapFilter );

		prevOffset = offset;
		prevWidth = newWidth;
		prevHeight = newHeight;
	}

	return texWithMips.MoveToRawBuffer();
}

/**@brief Scales texture, using chosen filtering method.*/
void			MipMapGenerator::Resample	( uint32 srcWidth, uint32 srcHeight, uint32 dstWidth, uint32 dstHeight, const uint8* source, uint8* dest, MipMapFilter filter )
{
	assert( NumChannels > 0 && NumChannels <= sMaxChannels );

	// ============================================== //
	// Initialization.

	Resampler* resamplers[ sMaxChannels ];
	std::vector< float > samples[ sMaxChannels ];

	resamplers[ 0 ] = new Resampler( srcWidth, srcHeight, dstWidth, dstHeight, Resampler::Boundary_Op::BOUNDARY_CLAMP, 0.0f, 1.0f, Resampler::get_filter_name( (int)filter ) );
	samples[ 0 ].resize( srcWidth );

	for( int channel = 1; channel < NumChannels; channel++ )
	{
		resamplers[ channel ] = new Resampler( srcWidth, srcHeight, dstWidth, dstHeight, Resampler::Boundary_Op::BOUNDARY_CLAMP, 0.0f, 1.0f, Resampler::get_filter_name( (int)filter ), resamplers[ 0 ]->get_clist_x(), resamplers[ 0 ]->get_clist_y() );
		samples[ channel ].resize( srcWidth );
	}

	// ============================================== //
	// Gamma correction.

   // Partial gamma correction looks better on mips. Set to 1.0 to disable gamma correction. 
	const float sourceGamma = 1.0f;//1.75f;


	float srgbToLinear[ 256 ];
	for( int i = 0; i < 256; ++i )
		srgbToLinear[ i ] = (float)pow( i * 1.0f / 255.0f, sourceGamma );

	const int linearToSrgbTableSize = 4096;
	unsigned char linearToSrgb[ linearToSrgbTableSize ];

	const float invLinearToSrgbTableSize = 1.0f / linearToSrgbTableSize;
	const float invSourceGamma = 1.0f / sourceGamma;

	for( int i = 0; i < linearToSrgbTableSize; ++i )
	{
		int k = (int)( 255.0f * pow( i * invLinearToSrgbTableSize, invSourceGamma ) + .5f );
		if( k < 0 ) k = 0; else if( k > 255 ) k = 255;
		linearToSrgb[ i ] = (unsigned char)k;
	}

	// ============================================== //
	// Resampling.

	const int srcPitch = srcWidth * NumChannels;
	const int dstPitch = dstWidth * NumChannels;
	int dstY = 0;

	for( unsigned int srcY = 0; srcY < srcHeight; srcY++ )
	{
		const uint8* pSrc = &source[ srcY * srcPitch ];

		for( unsigned int x = 0; x < srcWidth; x++ )
		{
			for( int c = 0; c < NumChannels; c++ )
			{
				if( ( c == 3 ) || ( ( NumChannels == 2 ) && ( c == 1 ) ) )
					samples[ c ][ x ] = *pSrc++ * ( 1.0f / 255.0f );
				else
					samples[ c ][ x ] = srgbToLinear[ *pSrc++ ];
			}
		}

		for( int c = 0; c < NumChannels; c++ )
		{
			if( !resamplers[ c ]->put_line( &samples[ c ][ 0 ] ) )
			{
				for( int channel = 0; channel < NumChannels; channel++ )
					delete resamplers[ channel ];

				  // Out of memory.
				return;
			}
		}

		for( ; ; )
		{
			int compIndex;
			for( compIndex = 0; compIndex < NumChannels; compIndex++ )
			{
				const float* pOutput_samples = resamplers[ compIndex ]->get_line();
				if( !pOutput_samples )
					break;

				const bool alphaChannel = ( compIndex == 3 ) || ( ( NumChannels == 2 ) && ( compIndex == 1 ) );
				assert( dstY < (int)dstHeight );
				unsigned char* pDst = &dest[ dstY * dstPitch + compIndex ];

				for( unsigned int x = 0; x < dstWidth; x++ )
				{
					if( alphaChannel )
					{
						int c = (int)( 255.0f * pOutput_samples[ x ] + .5f );
						if( c < 0 ) c = 0; else if( c > 255 ) c = 255;
						*pDst = (unsigned char)c;
					}
					else
					{
						int j = (int)( linearToSrgbTableSize * pOutput_samples[ x ] + .5f );
						if( j < 0 ) j = 0; else if( j >= linearToSrgbTableSize ) j = linearToSrgbTableSize - 1;
						*pDst = linearToSrgb[ j ];
					}

					pDst += NumChannels;
				}
			}

			if( compIndex < NumChannels )
				break;

			dstY++;
		}
	}

	// Release resources.
	for( int channel = 0; channel < NumChannels; channel++ )
		delete resamplers[ channel ];
}

/**@brief Finds nearest power of 2.*/
unsigned int	MipMapGenerator::PowerOfTwo	( unsigned int dimmension )
{
	unsigned int newDimm = 1;

	while( newDimm < dimmension )
	{
		newDimm = newDimm << 1;
	}

	return newDimm;
}

/**@brief Wylicza rozmiar bufora dla tekstury o podanych rozmiarach wliczaj¹c w to wszystkie poziomy mipmap.*/
uint32			MipMapGenerator::ComputeBufferSize( unsigned int width, unsigned int height, int bytesPerPixel )
{
	uint32 bufferSize = 0;

	while( width > 1 || height > 1 )
	{
		bufferSize += width * height * bytesPerPixel;
		width = width / 2;
		height = height / 2;

		if( width == 0 )
			width = 1;
		if( height == 0 )
			height = 1;
	}

	bufferSize += bytesPerPixel;	// Add last mipmap 1x1.
	return bufferSize;
}

// ================================ //
//
unsigned int	MipMapGenerator::ComputeMipMapsLevels( unsigned int width, unsigned int height )
{
	int widthMips = 1;
	int heightMips = 1;

	while( width > 1 )
	{
		width = width / 2;
		widthMips++;
	}

	while( height > 1 )
	{
		height = height / 2;
		heightMips++;
	}

	return std::max( widthMips, heightMips );
}

// ================================ //
//
PtrOffset		MipMapGenerator::ComputeMipLevelOffset( unsigned int initWidth, unsigned int initHeight, int bytesPerPixel, int level )
{
	PtrOffset offset = 0;

	for( int curLevel = 0; curLevel < level; curLevel++ )
	{
		offset += initHeight * initWidth * bytesPerPixel;

		initHeight /= 2;
		initWidth /= 2;
	}

	return offset;
}

}	// sw

