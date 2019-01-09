#pragma once
/**
@file RenderingParams.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGUI/Core/System/CommonTypes/CommonTypes.h"


namespace sw {
namespace gui
{


// ================================ //
//
struct RenderingParams
{
	Position		ParentOffset;		///< Control offset relative to parent.

};

// ================================ //
//
struct RenderingSystemParams
{
	Size2D			ViewportSize;
};

}	// gui
}	// sw
