#pragma once
/**
@file MockAssetCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"

#include <string>


namespace sw
{

class MockAsset;
class MockAssetCreator;
DEFINE_PTR_TYPE( MockAssetCreator );


/**@brief 
@ingroup Mocks*/
struct MockAssetCreateInfo : public IAssetCreateInfo
{
	RTTR_ENABLE( IAssetCreateInfo );
public:

	std::string			Content;

public:
	virtual TypeID					GetAssetType	() const { return TypeID::get< MockAsset >(); }
};


/**@brief Creates MockAsset.
@ingroup Mocks*/
class MockAssetCreator : public IAssetCreator
{
private:

	std::vector< MockAsset* >		m_livingAssets;

protected:
public:
	explicit		MockAssetCreator		() = default;
	virtual			~MockAssetCreator		() = default;

public:

	virtual Nullable< Resource* >	Create				( const AssetPath& assetName, IAssetCreateInfo&& createInfo )				override;

	virtual Nullable< Resource* >	LoadFromRaw			( const AssetPath& assetName, const BufferRaw& rawData )					override;
	virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual BufferRaw				SaveToRaw			( ResourcePtr< Resource > resource )										override;

	virtual bool					IsCacheable				() const override;
	virtual bool					SupportsResourceToRaw	() const override;
	virtual TypeID					GetAssetType			() const override;

public:

	void							OnDeleteAsset			( MockAsset* asset );
	void							OnCreateAsset			( MockAsset* asset );

	Size							CountLivingAssets		() const							{ return m_livingAssets.size(); }

public:

	static MockAssetCreatorPtr		CreateCreator			();

};



}	// sw



