#pragma once
/**
@file LoadingContext.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/Loaders/LoadingResult.h"

#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"



namespace sw
{


/**@brief Helper class which can be used to pass useful parameters to functions.

Note that IAssetLoader can't store variables in class members, since there's
only one loader per application that can be used by multiple threads.
This class helps to pass parameters to loading functions.

@ingroup Loaders*/
class LoadingContext
{
public:

	RMLoaderAPI			Factory;
	ErrorsCollector		Warnings;
	AssetsVec			AssetsCollection;

protected:
public:
	explicit		LoadingContext		( RMLoaderAPI rm );
					~LoadingContext		() = default;

public:

	template< typename AssetType >
	void			CollectAsset		( ResourcePtr< AssetType > asset );

};


//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
LoadingContext::LoadingContext		( RMLoaderAPI rm )
	:	Factory( rm )
{}


}	// sw



