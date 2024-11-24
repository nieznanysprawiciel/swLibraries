#pragma once
/**
@file IAssetLoadInfo.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Common/TypesDefinitions.h"

namespace sw
{


/**@brief Interface of asset descriptor used to load asset.

@ingroup Loaders*/
class IAssetLoadInfo
{
	RTTR_ENABLE();
private:
protected:
public:
	explicit		IAssetLoadInfo		() = default;
	virtual			~IAssetLoadInfo		() = 0 {}


public:

	/**@brief Gets type of asset to create.*/
	virtual TypeID			GetAssetType		() const = 0;

	/**@brief Computes key which uniquely identifies Resource created from specific file.

	This function can be used to give identitifiers for internal Resources in files, when there
	are multiple Assets to load. Other use case are generated or partially generated Assets, which
	need to be distinguished. As an example we can generate Texture with mipmaps or without them.*/
	virtual std::string		ResourceKey		    () const { return ""; }

};

DEFINE_OPTR_TYPE( IAssetLoadInfo );
DEFINE_PTR_TYPE( IAssetLoadInfo );


}	// sw
