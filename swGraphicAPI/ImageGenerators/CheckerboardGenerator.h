#pragma once
/**
@file CheckerboardGenerator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Buffers/BufferRaw.h"



namespace sw
{


/**@brief Generates 2D checkerboard image.*/
class CheckerboardGenerator
{
private:
public:

	uint16			PixWidth;
	uint16			PixHeight;

	uint32			DarkColor;
	uint32			BrightColor;

	uint16			CheckerSize;

public:

	explicit		CheckerboardGenerator		();
	explicit		CheckerboardGenerator		( uint16 width, uint16 height );
	explicit		CheckerboardGenerator		( uint16 width, uint16 height, uint32 darkColor, uint32 brightColor );
					~CheckerboardGenerator		() = default;


	BufferRaw		Generate					() const;
};





}	// sw



