#pragma once
/**
@file FontCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"


namespace sw
{

class FontCreator;
DEFINE_PTR_TYPE( FontCreator );



/**@brief Creates @ref FontAsset.
@ingroup AssetsCreators*/
class FontCreator : public IAssetCreator
{
private:
protected:
public:
    explicit		FontCreator() = default;
    virtual			~FontCreator() = default;


public:

    virtual Nullable< Resource* >	Create          ( const AssetPath& assetName, IAssetCreateInfo&& createInfo ) override;

    virtual Nullable< Resource* >	LoadFromRaw     ( const AssetPath& assetName, const BufferRaw& rawData ) override;
    virtual BufferRaw				SaveToRaw       ( const IAssetCreateInfo& createInfo ) override;
    virtual BufferRaw				SaveToRaw       ( ResourcePtr< Resource > resource ) override;

    virtual bool					IsCacheable     () const override;
    virtual bool					SupportsResourceToRaw   () const override;
    virtual TypeID					GetAssetType    () const override;

public:

    static FontCreatorPtr           CreateCreator();
};

}	// sw

