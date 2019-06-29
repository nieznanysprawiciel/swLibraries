/**
@file SoilTextureLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Loaders/SoilTextureLoader/stdafx.h"


#include "SoilTextureLoader.h"

#include "swGraphicAPI/Resources/Textures/TextureInitData.h"
#include "swGraphicAPI/ResourceManager/Loaders/TextureLoadInfo.h"
#include "swGraphicAPI/ResourceManager/Exceptions/LoaderException.h"

#include "swCommonLib/Common/Exceptions/Common/FileNotFoundException.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"
#include "swCommonLib/Common/Converters.h"

#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "SOIL/stb_image.h"


namespace sw
{


// ================================ //
//
struct SoilAllocator
{
	uint8*		allocate		( Size numElements );
	void		deallocate		( uint8* data, Size numElements );
};

// ================================ //
//
uint8*			SoilAllocator::allocate			( Size numElements )
{
	return static_cast< uint8* >( stbi__malloc( numElements ) );
}

// ================================ //
//
void			SoilAllocator::deallocate		( uint8* data, Size numElements )
{
	stbi_image_free( data );
}




// ================================ //
//
bool											SoilTextureLoader::CanLoad		( const AssetPath& filePath, TypeID resourceType )
{
	std::string allowedExtensions[] =
	{
		".png",
		".jpeg",
		".jpg",
		".bmp",
		".tga",
		".gif",
		".hdr",
		".psd",
		".dds",
	};

	// Get extension in lowercase. Note that we deal with multibytes character and something can be wrong with this.
	auto extension = filePath.GetFile().GetExtension();
	std::transform( extension.begin(), extension.end(), extension.begin(), ::tolower );

	if( std::find( std::begin( allowedExtensions ), std::end( allowedExtensions ), extension ) == std::end( allowedExtensions ) )
		return false;

	TypeID allowedTypes[] =
	{
		TypeID::get< Texture >(),
		TypeID::get< Resource >()
	};

	if( std::find( std::begin( allowedTypes ), std::end( allowedTypes ), resourceType ) == std::end( allowedTypes ) )
		return false;

	return true;
}


// ================================ //
//
LoadingResult									SoilTextureLoader::Load			( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	if( filePath.GetFile().Exists() )
	{
		auto loadInfo = static_cast< const TextureLoadInfo* >( assetDesc );

		int height = 0;
		int width = 0;
		int channels = 0;
		int realChannels = 0;

		// Check file metadata. This can fail, but we ignore it. We handle fails after calling stbi_load.
		stbi_info( filePath.GetFile().String().c_str(), &width, &height, &channels );

		// Force alpha channel if image has 3 channels. We don't support 3-components
		// images, because DirectX don't support this format.
		if( channels == 3 )
			channels = 4;

		uint8* data = stbi_load( filePath.GetFile().String().c_str(), &width, &height, &realChannels, channels );

		if( data == nullptr )
			return { LoaderException::Create( "SoilTextureLoader", stbi_failure_reason(), filePath, resourceType ) };

		Size memSize = height * width * channels;
		auto texBuffer = BufferTyped< uint8, SoilAllocator >::StealMemory( std::move( data ), memSize );

		TextureInitData texInfo( texBuffer.MoveToRawBuffer() );
		texInfo.Width = width;
		texInfo.Height = height;

		if( realChannels == 1 )
			texInfo.Format = ResourceFormat::RESOURCE_FORMAT_R8_UNORM;
		else if( realChannels == 2 )
			texInfo.Format = ResourceFormat::RESOURCE_FORMAT_R8G8_UNORM;
		else if( realChannels == 3 )
			texInfo.Format = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;
		else if( realChannels == 4 )
			texInfo.Format = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;
		else
			return { LoaderException::Create( "SoilTextureLoader", "Unexpected number of color channels " + Convert::ToString( realChannels ), filePath, resourceType ) };


		texInfo.MipMaps = loadInfo->MipMaps;
		texInfo.TextureUsage = loadInfo->TextureUsage;

		auto result = factory.CreateGenericAsset( filePath, resourceType, std::move( texInfo ) );

		if( result.IsValid() )
			return { result.Get() };
		else
			return { result.GetError() };
	}
	else
	{
		return { std::make_shared< FileNotFoundException >( filePath.GetFile() ) };
	}
}

// ================================ //
//
ReturnResult									SoilTextureLoader::Prefetch		( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	return Result::Error;
}



}	// sw

