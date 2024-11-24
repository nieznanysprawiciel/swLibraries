#pragma once
/**
@file TextureCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"



namespace sw
{

/**@brief Adds existing texture.
Hack for RenderTargets textures.*/
struct TextureExistingInitInfo : public sw::IAssetCreateInfo
{
private:
	RTTR_ENABLE( sw::IAssetCreateInfo );
public:

	TexturePtr			Tex;

public:
	virtual TypeID			GetAssetType	() const override { return TypeID::get< Texture >(); }
	virtual std::string		ResourceKey		() const override { return ""; }
};



/**@brief Creates texture and generates mipmaps.

@todo Implement Texture creation with already generated mipmaps. Add new IAssetCreateInfo
structure.

@ingroup AssetsCreators*/
class TextureCreator : public IAssetCreator
{
private:
protected:
public:
	explicit		TextureCreator		() = default;
	virtual			~TextureCreator		() = default;


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


