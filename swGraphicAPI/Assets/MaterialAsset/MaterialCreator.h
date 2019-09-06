#pragma once
/**
@file MaterialCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"

#include "MaterialAsset.h"


namespace sw
{

class MaterialCreator;
DEFINE_PTR_TYPE( MaterialCreator );



/**@brief Creates @ref MaterialAsset.
@ingroup AssetsCreators*/
class MaterialCreator : public IAssetCreator
{
private:
protected:
public:
    explicit		MaterialCreator		() = default;
    virtual			~MaterialCreator		() = default;


public:

    virtual Nullable< Resource* >	Create				( const AssetPath& assetName, IAssetCreateInfo&& createInfo )				override;

    virtual Nullable< Resource* >	LoadFromRaw			( const AssetPath& assetName, const BufferRaw& rawData )					override;
    virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
    virtual BufferRaw				SaveToRaw			( ResourcePtr< Resource > resource )										override;

    virtual bool					IsCacheable				() const override;
    virtual bool					SupportsResourceToRaw	() const override;
    virtual TypeID					GetAssetType			() const override;

public:

    static MaterialCreatorPtr       CreateCreator           ();
};




}	// sw

