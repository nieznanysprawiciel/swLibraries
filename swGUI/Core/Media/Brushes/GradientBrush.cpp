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
Size            Align16         ( Size size )
{
    return ( 16 - size % 16 ) % 16;
}



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
	return ExpectedBufferSize( ConstantsSize() );
}

// ================================ //
//
Size						GradientBrush::ExpectedBufferSize	( Size constantsSize ) const
{
	auto neededSize = GradientStopsSize( constantsSize ) + constantsSize;
	neededSize = neededSize + Align16( neededSize );

	return neededSize;
}

// ================================ //
//
Size						GradientBrush::GradientStopsSize	( Size constsSize ) const
{
	auto gradientStopsAlign = Align16( sizeof( GradientStop ) );

	// Size of GradientStops array + size of number of array elements on the begining.
    auto gradientStopsSize = ( sizeof( GradientStop ) + gradientStopsAlign ) * m_gradientStops.size();
	return gradientStopsSize + NumStopsSize( constsSize );
}

// ================================ //
//
Size						GradientBrush::NumStopsSize			( Size constsSize ) const
{
    Size restFromConsts = Align16( constsSize );
    if( restFromConsts == 0)
    {
        // uint32 size + alignement.
        return Align16( sizeof( uint32 ) );
    }
    else
    {
        // uint32 will be in the same register as last variables from constants.
        return restFromConsts;
    }
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

	dataPtr += NumStopsSize( constants.DataSize );

	for( Size i = 0; i < m_gradientStops.size(); i++ )
	{
		auto gradientStopsAlign = Align16( sizeof( GradientStop ) );

		memcpy( dataPtr, &m_gradientStops[ i ], sizeof( GradientStop ) );
		dataPtr += ( sizeof( GradientStop ) + gradientStopsAlign );
	}
}




}	// gui
}	// sw
