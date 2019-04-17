/**
@file ShaderLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "ShaderLoader.h"

#include "swCommonLib/System/File.h"


namespace sw
{

// ================================ //
//
bool											ShaderLoader::CanLoad		( const AssetPath& filePath, TypeID resourceType )
{
	return false;
}

// ================================ //
//
LoadingResult									ShaderLoader::Load			( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	std::string fileContent = filesystem::File::Load( filePath.GetFile() );

	return LoadingResult();
}

// ================================ //
//
ReturnResult									ShaderLoader::Prefetch		( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	return Result::Error;
}

}	// sw

