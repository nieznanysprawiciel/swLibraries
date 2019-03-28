/**
@file MockAssetCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "MockAssetCreator.h"

#include "MockAsset.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"




namespace sw
{

// ================================ //
//
Nullable< Resource* >		MockAssetCreator::Create			( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )
{
	return new MockAsset( this, assetName.String() );
}

// ================================ //
//
Nullable< Resource* >		MockAssetCreator::LoadFromRaw		( const filesystem::Path& assetName, const BufferRaw& rawData )
{
	assert( !"InputLayout is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw					MockAssetCreator::SaveToRaw		( const IAssetCreateInfo& createInfo )
{
	assert( !"InputLayout is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					MockAssetCreator::SaveToRaw		( ResourcePtr< Resource > resource )
{
	assert( !"InputLayout is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						MockAssetCreator::IsCacheable		() const
{
	return false;
}

// ================================ //
//
bool						MockAssetCreator::SupportsResourceToRaw() const
{
	return false;
}

// ================================ //
//
TypeID						MockAssetCreator::GetAssetType			() const
{
	return TypeID::get< MockAsset >();
}

// ================================ //
//
void						MockAssetCreator::OnDeleteAsset			( MockAsset* asset )
{
	auto iter = std::find( m_livingAssets.begin(), m_livingAssets.end(), asset );
	m_livingAssets.erase( iter );
}

// ================================ //
//
void						MockAssetCreator::OnCreateAsset			( MockAsset* asset )
{
	m_livingAssets.push_back( asset );
}

// ================================ //
//
MockAssetCreatorPtr			MockAssetCreator::CreateCreator			()
{
	return std::make_shared< MockAssetCreator >();
}



}	// sw



