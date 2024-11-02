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

#include "swCommonLib/Common/fmt.h"
#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/System/File.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/Converters/Convert.h"

#include "swCommonLib/Common/Buffers/Image.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"
#include "swCommonLib/Common/Buffers/ImageRegion.h"


#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"

#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"

#include "swGraphicAPI/Assets/TextAsset/Loader/Glyph.h"
#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"

#include <ft2build.h>
#include FT_FREETYPE_H


#undef min
#undef max
#undef RegisterClass


#endif // !DISABLE_PRECOMPILED_HEADER


