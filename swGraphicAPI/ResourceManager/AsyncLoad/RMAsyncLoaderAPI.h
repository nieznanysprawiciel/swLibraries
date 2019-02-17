#pragma once
/**
@file RMAssetsThreadAPI.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/




namespace sw
{

class nResourceManager;



/**@brief ResourceManager API for AssetsThread class.

AssetsThread class should use only this API for loading assets. This class forwards calls
to internal ResourceManager pointer.

@ingroup AsyncLoading*/
class RMAsyncLoaderAPI
{
private:

	nResourceManager*		m_resourceManager;

protected:
public:
	explicit		RMAsyncLoaderAPI		( nResourceManager* manager );
					~RMAsyncLoaderAPI		() = default;

};


}	// sw


