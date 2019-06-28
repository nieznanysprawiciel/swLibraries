#pragma once
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//


/// @note You can disable all headers in precompiled header with one macro.
/// All cpp files should be precompiled header independet and explicitly include needed headers.
#ifndef DISABLE_PRECOMPILED_HEADER


#include <cassert>

#include <string>
#include <vector>
#include <map>

#include <DirectXMath.h>

#include "swCommonLib/Common/RTTR.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/ResourceManager/nResourceManager.h"
#include "swGraphicAPI/Resources/ResourcesFactory.h"
#include "swGraphicAPI/Resources/SwapChain.h"

#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"


#undef min
#undef max
#undef RegisterClass


#endif // !DISABLE_PRECOMPILED_HEADER


