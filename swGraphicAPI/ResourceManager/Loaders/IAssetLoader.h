#pragma once
/**
@file IAssetLoader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/Resources/ResourcePtr.h"
#include "swGraphicAPI/Resources/ResourceObject.h"

#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/Loaders/LoadingResult.h"
#include "swGraphicAPI/ResourceManager/Loaders/RMLoaderAPI.h"
#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"

#include <vector>


namespace sw
{


/**@defgroup Loaders
@brief Classes for loading resources from different files formats.
@ingroup AssetsManagement

@copydoc WritingLoaders
*/

/**@page WritingLoaders Developing loaders
@tableofcontents

@section LoadersOverview Loaders Overview

Loaders are abstraction layer between different file formats and Assets used in engine.
When @ref ResourceManager gets request to load asset, it finds proper loader and passes this task to it.

Since @ref ResourceManager supports asynchronous loading, Loader shouldn't depend on some static internal state, while loading data.

@section InheritingIAssetLoader Inheriting IAssetLoader

To write your own file loader you should implement @ref IAssetLoader interface.

@subsection CanLoadFunction CanLoad function

@copydoc IAssetLoader::CanLoad

@subsection LoadFunction Load function

@copydoc IAssetLoader::Load
*/




/**@brief Base class for resource and assets loaders.
@ingroup Loaders*/
class IAssetLoader
{
private:
protected:
public:
	explicit		IAssetLoader	() = default;
	virtual			~IAssetLoader	() = 0 {}


	/**@brief Override this function checks if this loader can load specified file.

	Override this function checks if this loader can load specified file.
	@param[in] filePath
	From file path argument this function should check only file extension. There's no deep check needed, since this function will be called
	multiple times while searching for loaders and this could hurt performance.
	
	@param[in] resourceType Different files can contain multiple assets of multiple types. You should check this argument and confirm, that this asset
	type is supported by this loader.*/
	virtual bool												CanLoad		( const AssetPath& filePath, TypeID resourceType ) = 0;
	
	/**@brief Function loads asset.
	
	Function for loading assets. Loader should create all assets internally, by using AssetFactoryAPI from parameter.
	AssetFactoryAPI adds all created assets to ResourceManager.

	Frequently asset Loader must create multiple helper assets before creating main asset. All these assets should be placed
	in result vector. Main asset should take 0 index of this vector and should have the same name as passed in filePath parameter and type
	described by resourceType.
	This is important when someone wants to load for example mesh and provides file path to ResourceManager. After asset is loaded, someone must
	choose which from asset vector is desired mesh (one file can have multiple meshes). If it's not explicitly specified after :: in file path parameter,
	it's up to Loader implementation to decide, which asset is the most important and give him the same name as whole file.

	@note There's nothing bad when multiple resources have the same name (for example name of file, from which they were created),
	as long as they have different types.

	@param[in] filePath Path to asset file. Note that this path can contain after :: name of asset. Implementation should choose this asset as main asset.
	@param[in] resourceType Type of asset to load. Each loader can load multiple assets type, because loader is connected rather to file type
	then to asset.
	@param[in] assetDesc Asset descriptor has all info needed to create and process asset internally.
	@param[in] factory Pointer to interface for creating assets.
	*/
	virtual LoadingResult										Load		( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory ) = 0;

	/**@brief Function used to prefetch and cache asset.
	
	Loader shouldn't create this asset. Instead it should call asset creation functiond from asset manager with
	flag indicating, that it should be cached. Note that this should apply to all nested assets too.*/
	virtual ReturnResult										Prefetch	( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory ) = 0;
};

DEFINE_OPTR_TYPE( IAssetLoader );


}	// sw

