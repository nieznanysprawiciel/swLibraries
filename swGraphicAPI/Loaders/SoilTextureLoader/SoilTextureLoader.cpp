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
#include "swGraphicAPI/ResourceManager/Loaders/Tools/CanLoad.h"

#include "swCommonLib/Common/Exceptions/Common/FileNotFoundException.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"
#include "swCommonLib/Common/Converters.h"

#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "SOIL/stb_image.h"
#include "SOIL/stb_image_write.h"


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
bool											SoilTextureLoader::CanLoad				( const AssetPath& filePath, TypeID resourceType )
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

	TypeID allowedTypes[] =
	{
		TypeID::get< Texture >(),
		TypeID::get< Resource >()
	};

	return DefaultCanLoad( filePath, resourceType, allowedExtensions, allowedTypes );
}

// ================================ //
//
ReturnResult									SoilTextureLoader::ValidateParameters	( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc )
{
	if( assetDesc->get_type() != TypeID::get< TextureLoadInfo >() )
		return LoaderException::Create( "SoilTextureLoader", "Unsupported descriptor type [ " + assetDesc->get_type().get_name().to_string() + " ].", filePath, resourceType );

	auto loadInfo = static_cast< const TextureLoadInfo* >( assetDesc );
	
	// In future we could force expected number of channels.
	if( loadInfo->Processing.ForceFormat )
		return LoaderException::Create( "SoilTextureLoader", "ForceFormat option is not supported.", filePath, resourceType );

	return Success::True;
}


// ================================ //
//
LoadingResult									SoilTextureLoader::Load					( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	if( filePath.GetFile().Exists() )
	{
		// Validate assetDesc parameters, if this loader can handle them.
		auto validation = ValidateParameters( filePath, resourceType, assetDesc );

		if( !validation.IsValid() )
			return { validation.GetError() };

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
		texInfo.MipMaps = loadInfo->MipMaps;
		texInfo.TextureUsage = loadInfo->TextureUsage;

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

		// Create texture asset.
		auto result = factory.CreateGenericAsset( filePath.GetOriginalPath(), resourceType, std::move( texInfo ) );

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
ReturnResult									SoilTextureLoader::Prefetch				( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	return Success::False;
}

// ================================ //
//
ReturnResult									SoilTextureLoader::Save					( const filesystem::Path& filePath, const Image< u32 >& image )
{
	if( image.GetChannels() != 4 )
		return ReturnResult( fmt::format( "Saving images with {} channels isn't supported", image.GetChannels() ) );

    Size expectedSize = image.GetWidth() * image.GetHeight() * image.GetChannels();
    if( image.GetSize() != expectedSize )
        return ReturnResult( fmt::format( "Buffer size: {} doesn't match expected image width = {}, height = {}", expectedSize, image.GetWidth(), image.GetHeight() ) );

	int save_result = stbi_write_png
	(
		filePath.String().c_str(),
		image.GetWidth(), image.GetHeight(), image.GetChannels(),
		image.GetRawData(), 0
	);

    if( save_result != 0 )
		return ReturnResult( fmt::format( "Failed to save texture to file: {}", filePath.String() ) );
	return Success::True;
}



}	// sw

