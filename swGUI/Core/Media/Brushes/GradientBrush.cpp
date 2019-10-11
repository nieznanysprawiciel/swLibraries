/**
@file GradientBrush.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "GradientBrush.h"

#include "swCommonLib/Common/Buffers/BufferTyped.h"
#include "swCommonLib/Common/fmt.h"


#include <algorithm>


namespace sw {
namespace gui
{


// ================================ //
//
GradientBrush::GradientBrush( Size constantsSize )
	:	Brush( ConstantBufferMode::Enable )
	,	m_buffer( BufferTyped< uint8 >( ExpectedBufferSize( constantsSize ) ).MoveToRawBuffer() )
{}


// ================================ //
//
void						GradientBrush::AddGradientStop		( GradientStop stop )
{
	m_gradientStops.push_back( stop );
	std::sort( m_gradientStops.begin(), m_gradientStops.end(), []( const GradientStop& left, const GradientStop& right )
	{ 
		if( left.Offset < right.Offset )
			return true;
		return false;
	} );

	if( m_buffer.GetSize() != ExpectedBufferSize() )
		InvalidateConstants();
}

// ================================ //
//
void						GradientBrush::RemoveGradientStop	( Size idx )
{
	m_gradientStops.erase( m_gradientStops.begin() +  idx );

	if( m_buffer.GetSize() != ExpectedBufferSize() )
		InvalidateConstants();
}

// ================================ //
//
AssetPath   				GradientBrush::ConstantsName		()
{
	auto expSize = ExpectedBufferSize();
	return fmt::format( "::sw::gui::GradientBrush::CB[Size={}]", expSize );
}

// ================================ //
//
AssetPath   				GradientBrush::TextureSource		()
{
	// No texture by default.
	return AssetPath();
}


// ================================ //
//
BufferRange					GradientBrush::PrepareBuffer		( BufferRange constants )
{
	auto expectedSize = ExpectedBufferSize();
	if( m_buffer.GetSize() != expectedSize )
		ReallocateBuffer( expectedSize );

	FillBufferContent( constants );

	return BufferRange( m_buffer.GetData(), m_buffer.GetSize() );
}

// ================================ //
//
Size						GradientBrush::ExpectedBufferSize	() const
{
	return ExpectedBufferSize( GradientStopsSize() );
}

// ================================ //
//
Size						GradientBrush::ExpectedBufferSize	( Size constantsSize ) const
{
	auto neededSize = GradientStopsSize() + constantsSize;
	neededSize = neededSize + neededSize % 16;

	return neededSize;
}

// ================================ //
//
Size						GradientBrush::GradientStopsSize	() const
{
	auto gradientStopsAlign = sizeof( GradientStop ) % 16;

	// Size of GradientStops array + size of number of array elements on the begining.
	return ( sizeof( GradientStop ) + gradientStopsAlign ) * m_gradientStops.size() + NumStopsSize();
}

// ================================ //
//
Size						GradientBrush::NumStopsSize			() const
{
	// uint32 size + alignement.
	return sizeof( uint32 ) + 12;
}

// ================================ //
//
void						GradientBrush::ReallocateBuffer		( Size newSize )
{
	BufferTyped< uint8 > bufferTyped( newSize );
	m_buffer = bufferTyped.MoveToRawBuffer();
}

// ================================ //
//
void						GradientBrush::FillBufferContent	( BufferRange constants )
{
	// Copy buffer from derived class.
	auto dataPtr = m_buffer.GetData();
	memcpy( dataPtr, constants.DataPtr, constants.DataSize );

	// Copy GradientStops.
	dataPtr += constants.DataSize;

	uint32 numGradientStops = (uint32)m_gradientStops.size();
	memcpy( dataPtr, &numGradientStops, sizeof( uint32 ) );

	dataPtr += NumStopsSize();

	for( Size i = 0; i < m_gradientStops.size(); i++ )
	{
		auto gradientStopsAlign = sizeof( GradientStop ) % 16;

		memcpy( dataPtr, &m_gradientStops[ i ], sizeof( GradientStop ) );
		dataPtr += ( sizeof( GradientStop ) + gradientStopsAlign );
	}
}




}	// gui
}	// sw
