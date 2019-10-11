/**
@file MockAssetLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/MockAssets/stdafx.h"

#include "MockAssetLoader.h"
#include "MockAsset.h"
#include "MockAssetCreator.h"

#include "swCommonLib/System/File.h"


namespace sw
{

// ================================ //
//
bool				MockAssetLoader::CanLoad			( const AssetPath& filePath, TypeID resourceType )
{
	return filePath.GetFile().GetExtension() == ".mock" &&
		  ( TypeID::get< MockAsset >() == resourceType ||
			TypeID::get< Resource >() == resourceType );
}

// ================================ //
//
LoadingResult		MockAssetLoader::Load				( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	LoadingResult result;

	if( resourceType != TypeID::get< MockAsset >() &&
		resourceType != TypeID::get< Resource >() )
		return "Can't load asset of type [" + resourceType.get_name().to_string() + "].";


	MockAssetCreateInfo createInfo;
	
	if( filePath.GetFile().Exists() )
	{
		createInfo.Content = filesystem::File::Load( filePath.GetFile() );

		auto res = factory.CreateGenericAsset( filePath.GetOriginalPath(), TypeID::get< MockAsset >(), std::move( createInfo ) );
		if( !res.IsValid() )
			return res.GetError();

		return LoadingResult( res.Get() );
	}
	else
	{
		return "File [" + filePath.GetFile().String() + "] doesn't exist.";
	}
}

// ================================ //
//
ReturnResult		MockAssetLoader::Prefetch			( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	return ReturnResult();
}


}	// sw


