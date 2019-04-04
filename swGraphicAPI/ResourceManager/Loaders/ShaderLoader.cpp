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
bool											ShaderLoader::CanLoad		( const filesystem::Path& filePath, TypeID resourceType )
{
	return false;
}

// ================================ //
//
LoadingResult									ShaderLoader::Load			( const filesystem::Path& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMAsyncLoaderAPI factory )
{
	std::string fileContent = filesystem::File::Load( filePath );

	return LoadingResult();
}

// ================================ //
//
ReturnResult									ShaderLoader::Prefetch		( const filesystem::Path& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMAsyncLoaderAPI factory )
{
	return Result::Error;
}

}	// sw

