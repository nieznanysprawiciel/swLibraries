#pragma once
/**
@file MeshResources.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.

@brief This file contains includes for low level API dependent Resources.
*/



#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/Resources/ResourceObject.h"
#include "swGraphicAPI/Resources/Shaders/IShader.h"
#include "swGraphicAPI/Resources/Buffers/Buffer.h"
#include "swGraphicAPI/Resources/Textures/RenderTarget.h"
#include "swGraphicAPI/Resources/Shaders/IShaderInputLayout.h"
#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/Resources/ResourcePtr.h"


#include "swGraphicAPI/Resources/Shaders/Shaders.h"
#include "swGraphicAPI/Resources/Shaders/InputLayout.h"
#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"

#include "swGraphicAPI/Resources/Textures/Texture.h"

#include "swGraphicAPI/Resources/PipelineStates/BlendingState.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"

#include <DirectXMath.h>




/**@defgroup Resources Resources
@ingroup ResourcesManagment
@ingroup GraphicAPI
@brief Low level resources that depend on graphic API.

Resources are strongly dependent from platform and graphic API used. This library gives you
abstraction layer over platform specific things. All graphic APIs are encapsulated in common
interfaces. Dependent libraries use only base classes. To create Resources @ref ResourcesFactory
class is used.

Resources can be shared by many objects. ResourceManager class is created to manage them and release
them when necessary. in future this class will be responsible for caching.

Note that Resources from this library are tightly related to device Resources. Except low level
Resources developer can define his own hiher level Assets, that are managed by @ref ResourceManager too.*/



namespace sw
{




typedef uint16 Index16;
typedef uint32 Index32;
typedef uint8 Index8;



}	// sw

