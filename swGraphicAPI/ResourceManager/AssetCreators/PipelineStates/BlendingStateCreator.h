#pragma once
/**
@file BlendingStateCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"




namespace sw
{

/**@brief Creates blending state for graphic pipeline.
@ingroup AssetsCreators*/
class BlendingStateCreator : public IAssetCreator
{
private:
protected:
public:
	explicit		BlendingStateCreator		() = default;
	virtual			~BlendingStateCreator		() = default;


public:

	virtual Nullable< Resource* >	Create				( const AssetPath& assetName, IAssetCreateInfo&& createInfo )				override;

	virtual Nullable< Resource* >	LoadFromRaw			( const AssetPath& assetName, const BufferRaw& rawData )					override;
	virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual BufferRaw				SaveToRaw			( ResourcePtr< Resource > resource )										override;

	virtual bool					IsCacheable				() const override;
	virtual bool					SupportsResourceToRaw	() const override;
	virtual TypeID					GetAssetType			() const override;


};




}	// sw


