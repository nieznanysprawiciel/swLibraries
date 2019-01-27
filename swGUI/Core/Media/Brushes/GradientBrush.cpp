/**
@file GradientBrush.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "GradientBrush.h"

#include "swCommonLib/Common/Buffers/BufferTyped.h"


#include <algorithm>


namespace sw {
namespace gui
{


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
std::wstring				GradientBrush::ConstantsName		()
{
	auto expSize = ExpectedBufferSize();
	return L"sw::gui::GradientBrush::CB[Size=" + Convert::FromString< std::wstring >( Convert::ToString( expSize ), L"" ) + L"]";
}

// ================================ //
//
std::wstring				GradientBrush::TextureSource		()
{
	// No texture by default.
	return std::wstring();
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
	auto neededSize = ConstantsSize() + GradientStopsSize();
	neededSize = neededSize + neededSize % 16;

	return neededSize;
}

// ================================ //
//
Size						GradientBrush::GradientStopsSize	() const
{
	// Size of GradientStops array + size of number of array elements on the begining.
	return sizeof( GradientStop ) * m_gradientStops.size() + sizeof( uint32 );
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

	dataPtr += sizeof( uint32 );

	memcpy( dataPtr, m_gradientStops.data(), m_gradientStops.size() * sizeof( GradientStop ) );
}




}	// gui
}	// sw
