/**
@file CheckerboardGenerator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "CheckerboardGenerator.h"

#include "swCommonLib/Common/Buffers/BufferTyped.h"



namespace sw
{

// ================================ //
//
CheckerboardGenerator::CheckerboardGenerator					()
	:	PixWidth( 8 )
	,	PixHeight( 8 )
	,	DarkColor( 0xFF000000 )
	,	BrightColor( 0xFFFFFFFF )
	,	CheckerSize( 1 )
{}


// ================================ //
//
CheckerboardGenerator::CheckerboardGenerator					( uint16 width, uint16 height )
	:	PixWidth( width )
	,	PixHeight( height )
	,	DarkColor( 0xFF000000 )
	,	BrightColor( 0xFFFFFFFF )
	,	CheckerSize( 1 )
{}

// ================================ //
//
CheckerboardGenerator::CheckerboardGenerator					( uint16 width, uint16 height, uint32 darkColor, uint32 brightColor )
	:	PixWidth( width )
	,	PixHeight( height )
	,	DarkColor( darkColor )
	,	BrightColor( brightColor )
	,	CheckerSize( 1 )
{}

// ================================ //
//
BufferRaw				CheckerboardGenerator::Generate			() const
{
	auto numPixels = PixWidth * PixHeight;

	BufferTyped< uint32 > buffer( numPixels );

	Size pixel = 0;
	for( Size y = 0; y < PixHeight; ++y )
	{
		for( Size x = 0; x < PixWidth; x++ )
		{
			bool xParity = ( x / CheckerSize ) % 2 > 0;
			bool yParity = ( y / CheckerSize ) % 2 > 0;
			bool isDark = xParity ^ yParity;

			uint32 color = isDark ? DarkColor : BrightColor;
			buffer[ pixel ] = color;

			pixel++;
		}
	}

	return buffer.MoveToRawBuffer();
}

}	// sw

