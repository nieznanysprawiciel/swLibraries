#pragma once
/**
@file LayoutCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"


namespace sw
{



/**@brief Creator for input layout.
@ingroup AssetsCreators*/
class LayoutCreator : public IAssetCreator
{
private:
protected:
public:
	explicit		LayoutCreator		() = default;
	virtual			~LayoutCreator		() = default;

public:

	virtual Nullable< Resource* >	Create				( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )		override;

	virtual Nullable< Resource* >	LoadFromRaw			( const filesystem::Path& assetName, const BufferRaw& rawData )				override;
	virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual BufferRaw				SaveToRaw			( ResourcePtr< Resource > resource )										override;

	virtual bool					IsCacheable				() const override;
	virtual bool					SupportsResourceToRaw	() const override;
	virtual TypeID					GetAssetType			() const override;

public:

};



}	// sw
