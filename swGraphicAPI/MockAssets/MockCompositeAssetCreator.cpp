/**
@file MockCompositeAssetCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/MockAssets/stdafx.h"


#include "MockCompositeAssetCreator.h"

#include "MockCompositeAsset.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"




namespace sw
{

// ================================ //
//
Nullable< Resource* >		MockCompositeAssetCreator::Create			( const AssetPath& assetName, IAssetCreateInfo&& createInfo )
{
	if( createInfo.get_type() == TypeID::get< MockCompositeAssetCreateInfo >() )
	{
		auto& typedInfo = static_cast< MockCompositeAssetCreateInfo& >( createInfo );
		return new MockCompositeAsset( assetName, typedInfo.SubAssets, typedInfo.CompositeSubAssets );
	}

	return "Wrong IAssetCreateInfo of type [" + createInfo.get_type().get_name().to_string() + "].";
}

// ================================ //
//
Nullable< Resource* >		MockCompositeAssetCreator::LoadFromRaw		( const AssetPath& assetName, const BufferRaw& rawData )
{
	assert( !"InputLayout is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw					MockCompositeAssetCreator::SaveToRaw		( const IAssetCreateInfo& createInfo )
{
	assert( !"InputLayout is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					MockCompositeAssetCreator::SaveToRaw		( ResourcePtr< Resource > resource )
{
	assert( !"InputLayout is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						MockCompositeAssetCreator::IsCacheable		() const
{
	return false;
}

// ================================ //
//
bool						MockCompositeAssetCreator::SupportsResourceToRaw() const
{
	return false;
}

// ================================ //
//
TypeID						MockCompositeAssetCreator::GetAssetType			() const
{
	return TypeID::get< MockCompositeAsset >();
}


// ================================ //
//
MockCompositeAssetCreatorPtr	MockCompositeAssetCreator::CreateCreator	()
{
	return std::make_shared< MockCompositeAssetCreator >();
}



}	// sw






