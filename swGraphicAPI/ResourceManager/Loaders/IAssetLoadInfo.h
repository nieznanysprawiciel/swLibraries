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
private:
protected:
public:
	explicit		IAssetLoadInfo		() = default;
	virtual			~IAssetLoadInfo		() = 0 {}


public:

	virtual TypeID		GetAssetType	() const = 0;

};

DEFINE_OPTR_TYPE( IAssetLoadInfo );
DEFINE_PTR_TYPE( IAssetLoadInfo );


}	// sw
