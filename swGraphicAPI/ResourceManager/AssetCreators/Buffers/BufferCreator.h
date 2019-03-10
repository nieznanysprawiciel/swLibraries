#pragma once
/**
@file BufferCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"



namespace sw
{

/**@brief Creates GPU Buffer.
@ingroup AssetsCreators*/
class BufferCreator : public IAssetCreator
{
private:
protected:
public:
	explicit		BufferCreator		() = default;
	virtual			~BufferCreator		() = default;


public:

	virtual Nullable< Resource* >	Create				( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )		override;

	virtual Nullable< Resource* >	LoadFromRaw			( const filesystem::Path& assetName, const BufferRaw& rawData )				override;
	virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual BufferRaw				SaveToRaw			( ResourcePtr< Resource > resource )										override;

	virtual bool					IsCacheable				() const override;
	virtual bool					SupportsResourceToRaw	() const override;
	virtual TypeID					GetAssetType			() const override;

public:

	Nullable< Buffer* >		CreateVertexBuffer			( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount );
	Nullable< Buffer* >		CreateVertexBuffer			( const filesystem::Path& name, const VertexBufferInitData& data );
	Nullable< Buffer* >		CreateIndexBuffer			( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount );
	Nullable< Buffer* >		CreateIndexBuffer			( const filesystem::Path& name, const IndexBufferInitData& data );
	Nullable< Buffer* >		CreateConstantsBuffer		( const filesystem::Path& name, const uint8* buffer, unsigned int size );
	Nullable< Buffer* >		CreateConstantsBuffer		( const filesystem::Path& name, const ConstantBufferInitData& data );

};



}	// sw

