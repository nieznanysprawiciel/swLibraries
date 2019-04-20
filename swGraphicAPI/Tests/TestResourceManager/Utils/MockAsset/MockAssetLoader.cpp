/**
@file MockAssetLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

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
	return filePath.GetFile().GetExtension() == ".mock";
}

// ================================ //
//
LoadingResult		MockAssetLoader::Load				( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	LoadingResult result;

	if( resourceType != TypeID::get< MockAsset >() &&
		resourceType != TypeID::get< Resource >() )
		return "Can't load asset of type [" + resourceType.get_name().to_string() + "].";


	MockAssetCreateInfo createInfo;
	createInfo.Content = filesystem::File::Load( filePath.GetFile() );

	auto res = factory.CreateGenericAsset( filePath, TypeID::get< MockAsset >(), std::move( createInfo ) );
	if( !res.IsValid() )
		return res.GetError();

	return LoadingResult( res.Get() );
}

// ================================ //
//
ReturnResult		MockAssetLoader::Prefetch			( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	return ReturnResult();
}


}	// sw

