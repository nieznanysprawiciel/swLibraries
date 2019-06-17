/**
@file ShaderLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "ShaderLoader.h"

#include "swGraphicAPI/Resources/Shaders/Shaders.h"
#include "swGraphicAPI/Resources/Shaders/ShaderInitData.h"

#include "swCommonLib/Common/Exceptions/Common/FileNotFoundException.h"
#include "swCommonLib/System/File.h"

#include <algorithm>


namespace sw
{

// ================================ //
//
bool											ShaderLoader::CanLoad		( const AssetPath& filePath, TypeID resourceType )
{
	std::string allowedExtensions[] =
	{
		".vert",
		".tesc",
		".tese",
		".geom",
		".frag",
		".comp",

		".vsh",
		".psh",
		".gsh",
		".csh"
	};

	auto extension = filePath.GetFile().GetExtension();

	if( std::find( std::begin( allowedExtensions ), std::end( allowedExtensions ), extension ) == std::end( allowedExtensions ) )
		return false;

	TypeID allowedTypes[] =
	{
		TypeID::get< VertexShader >(),
		TypeID::get< PixelShader >(),
		TypeID::get< GeometryShader >(),
		TypeID::get< ControlShader >(),
		TypeID::get< EvaluationShader >(),
		TypeID::get< ComputeShader >(),
		// Note that we don't support loading of all shaders from file, because we can't find out
		// all symbols that can be treated as entrypoint to shader.
		// TypeID::get< Resource >(),
	};

	if( std::find( std::begin( allowedTypes ), std::end( allowedTypes ), resourceType ) == std::end( allowedTypes ) )
		return false;

	return true;
}

// ================================ //
//
LoadingResult									ShaderLoader::Load			( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	if( filePath.GetFile().Exists() )
	{
		std::string fileContent = filesystem::File::Load( filePath.GetFile() );

		ShaderCodeInitData init( ShaderInitData::GetFromTypeID( resourceType ), std::move( fileContent ) );

		// We don't use GetCachedGeneric here because it's not nested asset and ResourceManager
		// checks cache first.
		auto resourceNullable = factory.CreateGenericAsset( filePath, resourceType, std::move( init ) );
		if( resourceNullable.IsValid() )
			return { resourceNullable.Get() };
		else
			return { resourceNullable.GetError() };
	}
	else
	{
		return { std::make_shared< FileNotFoundException >( filePath.GetFile() ) };
	}
}

// ================================ //
//
ReturnResult									ShaderLoader::Prefetch		( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	return Result::Error;
}

}	// sw

