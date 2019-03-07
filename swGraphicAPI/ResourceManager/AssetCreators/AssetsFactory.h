#pragma once
/**
@file AssetsFactory.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "IAssetCreator.h"

#include "swGraphicAPI/Resources/MeshResources.h"


#include <vector>


class BufferObject;


namespace sw
{

class IAssetCache;


/**@brief Assets factory.
@ingroup AssetsManagement*/
class AssetsFactory
{
private:
protected:

	uint8				m_buffersCreatorIdx;
	uint8				m_VSCreatorIdx;
	uint8				m_PSCreatorIdx;
	uint8				m_ESCreatorIdx;
	uint8				m_CSCreatorIdx;
	uint8				m_CtrlSCreatorIdx;
	uint8				m_GSCreatorIdx;
	uint8				m_layoutCreator;
	uint8				m_blendingStateCreator;
	uint8				m_rasterizerStateCreator;

	std::vector< IAssetCreatorPtr >		m_assetCreators;

public:
	explicit		AssetsFactory		();
					~AssetsFactory		() = default;

	/**@brief Function for generic asset creation.
	Internal implementation can steal content of IAssetCreateInfo.*/
	Nullable< Resource* >	CreateAsset		( const filesystem::Path& assetName, TypeID assetType, IAssetCreateInfo&& createInfo );

	/**@brief Registers asset creator.
	Can't register creator when it existed.
	@note This function is not thread safe.*/
	bool					RegisterCreator	( IAssetCreatorPtr creator );

	/**@brief Registers built in creators.*/
	void					RegisterDefaults();


public:

	ResourcePtr< BufferObject >		CreateVertexBuffer			( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< BufferObject >		CreateVertexBuffer			( const filesystem::Path& name, const VertexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const filesystem::Path& name, const IndexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const filesystem::Path& name, const uint8* buffer, unsigned int size );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const filesystem::Path& name, const ConstantBufferInitData& data );


private:

	IAssetCreator*			FindCreator				( TypeID assetType) const;

	void					Cache					( IAssetCreator* creator, const IAssetCreateInfo& createInfo );
	void					Cache					( IAssetCreator* creator, Resource* resource );
};


DEFINE_OPTR_TYPE( AssetsFactory );

}	// sw
