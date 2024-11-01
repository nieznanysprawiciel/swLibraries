#pragma once
/**
@file MockCompositeAssetCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"
#include "MockAsset.h"



namespace sw
{


class MockAsset;
class MockCompositeAsset;
class MockCompositeAssetCreator;
DEFINE_RESOURCE_PTR_TYPE( MockCompositeAsset );
DEFINE_PTR_TYPE( MockCompositeAssetCreator );


/**@brief
@ingroup Mocks*/
struct MockCompositeAssetCreateInfo : public IAssetCreateInfo
{
	RTTR_ENABLE( IAssetCreateInfo );
public:

	std::vector< MockAssetPtr >					SubAssets;
	std::vector< MockCompositeAssetPtr >		CompositeSubAssets;

public:
	virtual TypeID					GetAssetType	() const { return TypeID::get< MockCompositeAsset >(); }
	virtual std::string				ResourceKey		() const override { return ""; }
};


/**@brief Creates MockAsset.
@ingroup Mocks*/
class MockCompositeAssetCreator : public IAssetCreator
{
private:
protected:
public:
	explicit		MockCompositeAssetCreator		() = default;
	virtual			~MockCompositeAssetCreator		() = default;

public:

	virtual Nullable< Resource* >	Create				( const AssetPath& assetName, IAssetCreateInfo&& createInfo )				override;

	virtual Nullable< Resource* >	LoadFromRaw			( const AssetPath& assetName, const BufferRaw& rawData )					override;
	virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual BufferRaw				SaveToRaw			( ResourcePtr< Resource > resource )										override;

	virtual bool					IsCacheable				() const override;
	virtual bool					SupportsResourceToRaw	() const override;
	virtual TypeID					GetAssetType			() const override;

public:

	static MockCompositeAssetCreatorPtr		CreateCreator	();

};





}	// sw


