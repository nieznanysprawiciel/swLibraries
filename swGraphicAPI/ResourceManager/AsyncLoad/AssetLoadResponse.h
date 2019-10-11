#pragma once
/**
@file AssetLoadResponse.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Exception.h"

#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"

#include "swGraphicAPI/Resources/ResourceObject.h"
#include "swGraphicAPI/Resources/ResourcePtr.h"


namespace sw
{

/**@brief This structure is send after asset is loaded.

@ingroup AsyncLoading*/
struct AssetLoadResponse
{
	ResourcePointer						Resource;
	AssetPath							FilePath;		///< Path of loaded asset, the same that was used to call async request.
	IAssetLoadInfoPtr					LoadInfo;		///< Structure sent to load asset. Can be nullptr.
};

/**@brief Delegate to invoke after asset is loaded.
@ingroup AsyncLoading*/
//typedef fastdelegate::FastDelegate1< AssetLoadResponse& > LoadingSuccessHandler;
typedef std::function< void( AssetLoadResponse& ) > LoadingSuccessHandler;

/**@brief Delegate to invoke after asset laoding failed.
@ingroup AsyncLoading*/
typedef std::function< void( AssetLoadResponse&, ExceptionPtr ) > LoadingFailedHandler;

}	// sw


