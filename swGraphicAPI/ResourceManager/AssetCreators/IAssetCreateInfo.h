#pragma once
/**
@file IAssetsCreateInfo.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/RTTR.h"

namespace sw
{

class RMLoaderAPI;
class ResourceManagerAPI;



/**@brief Base class for generic assets creation.

Generally all structure used to create assets should inherit from this interface even if generic
creation is not necessary.

@ingroup AssetsManagement
@ingroup AssetsCreators*/
class IAssetCreateInfo
{
	RTTR_ENABLE();
private:
protected:
public:
	explicit		IAssetCreateInfo	() = default;
	virtual			~IAssetCreateInfo	() = default;

	/**@brief Gets type of asset to create.*/
	virtual TypeID					GetAssetType	    () const		= 0;

	/**@brief Computes key which uniquely identifies Resource created from specific file.
	
	This function can be used to give identitifiers for internal Resources in files, when there
	are multiple Assets to load. Other use case are generated or partially generated Assets, which
	need to be distinguished. As an example we can generate Texture with mipmaps or without them.*/
	virtual std::string				ResourceKey		    () const		= 0;
};


}	// sw


