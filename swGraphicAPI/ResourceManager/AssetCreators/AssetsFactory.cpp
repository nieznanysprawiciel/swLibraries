/**
@file AssetsFactory.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "AssetsFactory.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Buffers/BufferCreator.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/Shaders/ShaderCreator.h"



RTTR_REGISTRATION
{
	rttr::registration::class_< sw::IAssetCreator >( "sw::IAssetCreator" );
}


namespace sw
{


// ================================ //
//
AssetsFactory::AssetsFactory	()
{
	RegisterDefaults();
}


// ================================ //
//
bool			AssetsFactory::RegisterCreator		( IAssetCreatorPtr creator )
{
	TypeID type = creator->GetAssetType();
	for( size_t i = 0; i < m_assetCreators.size(); i++ )
	{
		if( m_assetCreators[ i ]->GetAssetType() == type )
			return false;
	}

	m_assetCreators.push_back( creator );
	return true;
}

// ================================ //
//
void			AssetsFactory::RegisterDefaults		()
{
	RegisterCreator( IAssetCreatorPtr( new BufferCreator() ) );
	m_buffersCreatorIdx = (uint8)m_assetCreators.size() - 1;

	RegisterCreator( IAssetCreatorPtr( new ShaderCreator< VertexShader >() ) );
	m_VSCreatorIdx = (uint8)m_assetCreators.size() - 1;

	RegisterCreator( IAssetCreatorPtr( new ShaderCreator< PixelShader >() ) );
	m_PSCreatorIdx = (uint8)m_assetCreators.size() - 1;

	RegisterCreator( IAssetCreatorPtr( new ShaderCreator< EvaluationShader >() ) );
	m_ESCreatorIdx = (uint8)m_assetCreators.size() - 1;

	RegisterCreator( IAssetCreatorPtr( new ShaderCreator< ComputeShader >() ) );
	m_CSCreatorIdx = (uint8)m_assetCreators.size() - 1;

	RegisterCreator( IAssetCreatorPtr( new ShaderCreator< ControlShader >() ) );
	m_CtrlSCreatorIdx = (uint8)m_assetCreators.size() - 1;

	RegisterCreator( IAssetCreatorPtr( new ShaderCreator< GeometryShader >() ) );
	m_GSCreatorIdx = (uint8)m_assetCreators.size() - 1;

}

// ================================ //
//
Nullable< Resource* >	AssetsFactory::CreateAsset		( const filesystem::Path& assetName, TypeID assetType, IAssetCreateInfo&& createInfo )
{
	IAssetCreator* creator = FindCreator( assetType );

	// We prefere to obtain buffer for cache from resource, but some resources resides on GPU
	// and loading data back is too difficult. This is last moment, where we can take necessary data.
	bool canConvertResourceToRaw = creator->SupportsResourceToRaw();
	if( !canConvertResourceToRaw )
		Cache( creator, createInfo );
	
	auto resource = creator->Create( assetName, std::move( createInfo ) );

	if( canConvertResourceToRaw )
		Cache( creator, resource );	

	return resource;
}

// ================================ //
//
IAssetCreator*			AssetsFactory::FindCreator		( TypeID assetType ) const
{
	for( size_t i = 0; i < m_assetCreators.size(); i++ )
	{
		if( m_assetCreators[ i ]->GetAssetType() == assetType )
			return m_assetCreators[ i ].get();
	}

	return nullptr;
}

// ================================ //
//
void					AssetsFactory::Cache			( IAssetCreator* creator, const IAssetCreateInfo& createInfo )
{
	if( creator->IsCacheable() )
	{
		// Implement me
	}
}

// ================================ //
//
void					AssetsFactory::Cache			( IAssetCreator* creator, Resource* resource )
{
	if( creator->IsCacheable() )
	{
		// Implement me
	}
}

}	// sw

