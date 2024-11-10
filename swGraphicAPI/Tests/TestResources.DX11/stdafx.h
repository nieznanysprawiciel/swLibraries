/**
@file stdafx.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Buffers/BufferTyped.h"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"
#include "swCommonLib/System/File.h"
#include "swGraphicAPI/MockAssets/Utils.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/MockAssets/GraphicAPI.h"

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"


#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Textures/TextureCreator.h"
#include "swGraphicAPI/Resources/Textures/TextureInitData.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/PipelineStates/RasterizerStateCreator.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/AssetsFactory.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/Shaders/LayoutCreator.h"
#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/Buffers/BufferCreator.h"
#include "swGraphicAPI/Resources/Buffers/BufferInitData.h"
#include "swGraphicAPI/ResourceManager/Loaders/RenderTargetLoader.h"

#include "swGraphicAPI/Resources/Shaders/Exceptions/CompilationException.h"
#include "swGraphicAPI/ImageGenerators/CheckerboardGenerator.h"

