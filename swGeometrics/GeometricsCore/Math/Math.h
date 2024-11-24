#pragma once
/**
@file SimpleMath.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"

namespace sw
{

/** Source: https://stackoverflow.com/questions/466204/rounding-up-to-next-power-of-2 */
uint32		RoundUpToPowerOfTwo( uint32 v )
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;

	return v;
}

}
