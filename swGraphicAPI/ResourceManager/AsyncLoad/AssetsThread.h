#pragma once
/**
@file AssetsThread.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Multithreading/QueueMT.h"

#include "AssetLoadRequest.h"
#include "AssetLoadResponse.h"
#include "swGraphicAPI/ResourceManager/nResourceManager.h"

#include <thread>


namespace sw
{

/**@defgroup AsyncLoading Asynchronous Loading
@ingroup AssetsManagement

@copydoc AsyncLoadingPage


@page AsyncLoadingPage Asynchronous Loading
@tableofcontents

@section AsyncLoadIntro Introduction

ResourceManager loads assets synchronously in caller thread or can queue loading request and process them
in internal thread. For managing this internal thread, AssetsThread was created. After asset is already loaded,
AssetsThread calls delegate (@ref AsyncLoadHandler) specified by requestor to return loaded value.

AsyncLoadHandler gets @ref AssetLoadResponse in parameter which contains desired resource, path to file and
IAssetLoadInfo structure info. Requestor is now allowed to do with this structure whatever he wants (for example
he can move path and load info with std::move.

All request are executed in order of pushing to queue. That means that there's guarantee that two calls to async load
from the same thread will result in the same order of loads. There're no guaranties between threads.
*/


/**@brief Class for managing asynchronous assets loading.

@todo Consider supporting multiple priority levels in future.
@todo Consider posibility to provide additional generic structure. Requestor can then identify, wich request was executed.

@ingroup AsyncLoading*/
class AssetsThread
{
private:

	nResourceManager*				m_resourceManager;

	QueueMT< AssetLoadRequest >		m_requests;

	std::thread						m_thread;

protected:
public:
	explicit		AssetsThread		( nResourceManager* resourceManApi );
					~AssetsThread		();

	/**@brief Breaks thread execution by sending end message to queue.*/
	void			StopThread			();

	/**@brief Adds new request to queue.*/
	void			QueueRequest		( AssetLoadRequest&& request );

private:

	void			LoadingThread		();
};



}	// sw


