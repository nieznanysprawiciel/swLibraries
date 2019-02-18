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
std::vector< ResourcePtr< Resource > >	ShaderLoader::Load			( const filesystem::Path& filePath, TypeID resourceType, IAssetLoadInfo* assetDesc, RMAsyncLoaderAPI factory )
{
	std::string fileContent = filesystem::File::Load( filePath );

	return std::vector<ResourcePtr<Resource>>();
}

// ================================ //
//
bool											ShaderLoader::Prefetch		( const filesystem::Path& filePath, TypeID resourceType, IAssetLoadInfo* assetDesc, RMAsyncLoaderAPI factory )
{
	return false;
}

}	// sw

