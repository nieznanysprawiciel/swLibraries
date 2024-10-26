#pragma once
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//


/// @note You can disable all headers in precompiled header with one macro.
/// All cpp files should be precompiled header independent and explicitly include needed headers.
#ifndef DISABLE_PRECOMPILED_HEADER


#include <cassert>

#include <string>
#include <vector>
#include <map>

#include <DirectXMath.h>

#include "swCommonLib/Common/RTTR.h"

#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/ResourceManager/ResourceManager.h"

#include "swCommonLib/System/File.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"

#include <ft2build.h>
#include FT_FREETYPE_H


#undef min
#undef max
#undef RegisterClass


#endif // !DISABLE_PRECOMPILED_HEADER


