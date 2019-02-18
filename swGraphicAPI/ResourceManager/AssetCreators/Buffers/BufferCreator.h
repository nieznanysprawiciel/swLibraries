#pragma once
/**
@file BufferCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"



namespace sw
{

/**@brief */
class BufferCreator : public IAssetCreator
{
private:
protected:
public:
	explicit		BufferCreator		() = default;
	virtual			~BufferCreator		() = default;


public:

	virtual ResourceObject*			Create				( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )		override;

	virtual ResourceObject*			LoadFromRaw			( const filesystem::Path& assetName, const BufferRaw& rawData )				override;
	virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual BufferRaw				SaveToRaw			( ResourcePtr< ResourceObject > resource )									override;

	virtual bool					SupportsResourceToRaw	() override;
	virtual TypeID					GetAssetType			() override;

public:

	ResourcePtr< BufferObject >		CreateVertexBuffer			( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< BufferObject >		CreateVertexBuffer			( const filesystem::Path& name, const VertexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const filesystem::Path& name, const IndexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const filesystem::Path& name, const uint8* buffer, unsigned int size );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const filesystem::Path& name, const ConstantBufferInitData& data );

};



}	// sw

