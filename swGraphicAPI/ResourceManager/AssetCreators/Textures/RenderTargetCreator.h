#pragma once
/**
@file RenderTargetCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"


namespace sw
{



/**@brief Creates RenderTarget.

@note RenderTargetCreator can't add color, depth and stencil textures to ResourceManager.
We need to load render targets using Loader to add them.

@ingroup AssetsCreators*/
class RenderTargetCreator : public IAssetCreator
{
private:
protected:
public:
	explicit		RenderTargetCreator		() = default;
	virtual			~RenderTargetCreator		() = default;


public:

	virtual Nullable< Resource* >	Create				( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )		override;

	virtual Nullable< Resource* >	LoadFromRaw			( const filesystem::Path& assetName, const BufferRaw& rawData )				override;
	virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual BufferRaw				SaveToRaw			( ResourcePtr< Resource > resource )										override;

	virtual bool					IsCacheable				() const override;
	virtual bool					SupportsResourceToRaw	() const override;
	virtual TypeID					GetAssetType			() const override;

};



}	// sw





