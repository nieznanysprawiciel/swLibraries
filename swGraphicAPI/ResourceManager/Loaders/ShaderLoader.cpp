/**
@file ShaderLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "ShaderLoader.h"

#include "swGraphicAPI/Resources/Shaders/Shaders.h"

#include "swCommonLib/Common/Exceptions/Common/FileNotFoundException.h"
#include "swCommonLib/System/File.h"

#include <algorithm>


namespace sw
{

// ================================ //
//
bool											ShaderLoader::CanLoad		( const AssetPath& filePath, TypeID resourceType )
{
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
		// TypeID::get< Resoruce >(),
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

