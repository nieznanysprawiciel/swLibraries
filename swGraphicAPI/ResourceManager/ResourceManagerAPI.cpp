/**
@file ResourceManagerAPI.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "ResourceManagerAPI.h"

#include "swGraphicAPI/ResourceManager/nResourceManager.h"


namespace sw
{

// ================================ //
//
ResourceManagerAPI::ResourceManagerAPI( nResourceManager* resourceManager )
	:	m_resourceManager( resourceManager )
{}

// ================================ //
//
sw::Nullable< ResourcePointer >		ResourceManagerAPI::LoadGeneric				( const AssetPath& assetName, const IAssetLoadInfo* desc, TypeID type )
{
    return m_resourceManager->LoadGeneric( assetName, desc, type );
}

// ================================ //
//
Nullable< ResourcePointer >			ResourceManagerAPI::CreateGenericAsset			( const AssetPath& name, TypeID assetType, IAssetCreateInfo&& createInfo )
{
    return m_resourceManager->CreateGenericAsset( name, assetType, std::move( createInfo ) );
}


}	// sw

