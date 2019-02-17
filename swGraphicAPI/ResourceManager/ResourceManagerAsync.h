#pragma once
/**
@file ResourceManagerAsync.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "nResourceManager.h"
#include "AsyncLoad/AssetsThread.h"



namespace sw
{


/**@brief ResourceManager with asynchronous loading functionality.

Internall implementation uses ResourceManager to load all assets. This class gives only abstraction layer
which loads all assets in separate threads and manages returning result.*/
class ResourceManagerAsync
{
private:

	nResourceManager*			m_resourceManager;		///< Pointer to synchronous resource manager.
	AssetsThread				m_asyncThread;			///< Thread used for asynchronous loading.

protected:
public:
	explicit		ResourceManagerAsync		( nResourceManager* resourceManager );
	virtual			~ResourceManagerAsync		() = default;

};



}	// sw

