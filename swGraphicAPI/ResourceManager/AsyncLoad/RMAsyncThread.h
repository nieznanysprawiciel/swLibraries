#pragma once
/**
@file RMAsyncThread.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "AssetsThread.h"


namespace sw
{

class ResourceManager;



/**@brief ResourceManager asynchornous API.

RMAsyncThread class initializes asynchornous assets loading thread and
exposes api for loading assets.

@ingroup AsyncLoading*/
class RMAsyncThread
{
private:

	ResourceManager*		m_resourceManager;
	AssetsThread			m_assetsThread;

protected:
public:
	explicit		RMAsyncThread		( ResourceManager* manager );
					~RMAsyncThread		() = default;

public:

	/**@brief Asynchronous call to LoadGeneric.*/
	void			LoadGenericAsync	( AssetPath assetName,
										  IAssetLoadInfoPtr desc,
										  TypeID type,
										  LoadingSuccessHandler onSuccess,
										  LoadingFailedHandler onFailed );

};


}	// sw


