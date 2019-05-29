/**
@file LoaderAPI.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "swGraphicAPI/ResourceManager/nResourceManager.h"

#include "RMLoaderAPI.h"


namespace sw
{

// ================================ //
//
RMLoaderAPI::RMLoaderAPI		( nResourceManager* manager )
	:	m_resourceManager( manager )
{}

// ================================ //
//
sw::Nullable< ResourcePointer >		RMLoaderAPI::LoadGeneric				( const AssetPath& assetName, const IAssetLoadInfo* desc, TypeID type )
{
	return m_resourceManager->LoadGeneric( assetName, desc, type );
}

// ================================ //
//
Nullable< ResourcePointer >			RMLoaderAPI::CreateGenericAsset			( const AssetPath& name, TypeID assetType, IAssetCreateInfo&& createInfo )
{
	return m_resourceManager->CreateGenericAsset( name, assetType, std::move( createInfo ) );
}

}	// sw

