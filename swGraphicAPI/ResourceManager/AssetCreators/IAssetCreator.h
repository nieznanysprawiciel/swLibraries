#pragma once
/**
@file IAssetCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/System/Path.h"
#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Common/Buffers/BufferRaw.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/ResourceObject.h"
#include "swGraphicAPI/Resources/ResourcePtr.h"

#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"

#include "IAssetCreateInfo.h"


namespace sw
{

/**@defgroup AssetsCreators Assets Creators
@copydetails IAssetCreator
@ingroup AssetsManagement*/



/**@brief Interface for assets creator.

Each asset type should have associated creator class, which implements creation function.
This allows user to create generic assets. AssetCreator can be registered in AssetsFactory.

Derived implementation should implement functions for typed IAssetCreateInfo descriptors.

Second purpose of this class is ability to write asset in raw data format to cache.

@todo Change Cache data generation api. During creation we should return created Resource
and data for cache in the most processed form to avoid recomputation after loading from cache.

@ingroup AssetsManagement
@ingroup AssetsCreators*/
class IAssetCreator
{
private:
protected:
public:
	explicit		IAssetCreator		() = default;
	virtual			~IAssetCreator		() = 0 {};

	/**@brief Main generic function for assets creation.
	Implementation is allowed to move content of createInfo parameter.*/
	virtual	Nullable< Resource* >	Create			( const AssetPath& assetName, IAssetCreateInfo&& createInfo )				= 0;

	/**@brief Loads Asset from raw data format.
	This function is used to read data from cache.*/
	virtual Nullable< Resource* >	LoadFromRaw		( const AssetPath& assetName, const BufferRaw& rawData )					= 0;

	/**@brief Creates raw data format MemoryChunk.
	This function is used to create data that will be written to cache.*/
	virtual BufferRaw				SaveToRaw		( const IAssetCreateInfo& createInfo )										= 0;

	/**@brief Saves resource in raw format.
	Note: Not all resources must support this conversion. Many of them stores their data on GPU and shouldn't try
	to read it.*/
	virtual BufferRaw				SaveToRaw		( ResourcePtr< Resource > resource )										= 0;

	/**@brief Checks if asset should be cached.
	If Asset is cacheable, creator must implement IAssetCreator::LoadFromRaw and of IAssetCreator::SaveToRaw functions.*/
	virtual bool					IsCacheable		() const																	= 0;

	/**@brief You can check if this AssetCreator supports SaveToRaw function with resources in parameters. If
	not, this class must implement SaveToRaw with IAssetCreateInfo in parameter.*/
	virtual bool					SupportsResourceToRaw		() const														= 0;

	/**@brief Gets type of asset which this creator creates.*/
	virtual TypeID					GetAssetType	() const																	= 0;
};

DEFINE_PTR_TYPE( IAssetCreator );


}	// sw

