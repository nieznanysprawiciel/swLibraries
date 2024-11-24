#pragma once
/**
@file SoilTextureLoader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Buffers/ImageRegion.h"
#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"


namespace sw
{


/**@brief Loades textures using SOIL library.
@ingroup Loaders
@ingroup TexturesLoaders*/
class SoilTextureLoader : public IAssetLoader
{
private:
public:

	explicit		SoilTextureLoader		() = default;
	virtual			~SoilTextureLoader		() = default;


	virtual bool					CanLoad				( const AssetPath& filePath, TypeID resourceType )															override;
	virtual LoadingResult			Load				( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;
	virtual ReturnResult			Prefetch			( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;

	static ReturnResult				Save				( const fs::Path& filePath, const Image< u32 >& image );

public:

	ReturnResult					ValidateParameters	( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc );
};

}	// sw
