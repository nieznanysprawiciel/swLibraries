#pragma once
/**
@file RMLoaderAPI.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"

#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"


namespace sw
{


class ResourceManager;



/**@brief ResourceManager API for @ref Loaders internal usage.

Loaders should use only synchronous functions. This API gives acces only
to those functions that won't cause deadlocks.

@todo Consider adding path of loaded asset to constructor. This way we could block
loading, that could cause deadlocks. (For example: Someone calls LoadGeneric on asset
that resides in file that is currenly loaded by loader).

@ingroup Loaders*/
class RMLoaderAPI : protected ResourceManagerAPI
{
protected:
public:

    explicit		RMLoaderAPI			( ResourceManager* manager )
        : ResourceManagerAPI( manager )
    {}
	
                    ~RMLoaderAPI		() = default;

public:

    using ResourceManagerAPI::GetGeneric;
    using ResourceManagerAPI::GetCachedGeneric;
    using ResourceManagerAPI::LoadGeneric;
    using ResourceManagerAPI::Load;
    using ResourceManagerAPI::GetCached;
    using ResourceManagerAPI::CreateGenericAsset;
    using ResourceManagerAPI::CreateAsset;

    using ResourceManagerAPI::LoadTexture;

    using ResourceManagerAPI::CreateConstantsBuffer;

    using ResourceManagerAPI::LoadVertexShader;
    using ResourceManagerAPI::LoadPixelShader;
    using ResourceManagerAPI::LoadGeometryShader;
    using ResourceManagerAPI::LoadControlShader;
    using ResourceManagerAPI::LoadEvaluationShader;
    using ResourceManagerAPI::LoadComputeShader;
    using ResourceManagerAPI::LoadShader;

    using ResourceManagerAPI::GetPathsManager;
};



}	// sw



