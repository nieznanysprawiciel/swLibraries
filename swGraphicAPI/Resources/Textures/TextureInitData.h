#pragma once
/**
@file TextureInitData.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"
#include "swCommonLib/Common/Buffers/BufferRaw.h"
#include "swGraphicAPI/Resources/Textures/Texture.h"


namespace sw
{


class Texture;


/**@brief Texture descriptor.

@ingroup Textures*/
struct TextureInitData : public sw::IAssetCreateInfo
{
private:
	RTTR_ENABLE( sw::IAssetCreateInfo );
public:

	BufferRaw			Data;
	
	uint32				Width;						///< Texture width in pixels.
	uint32				Height;						///< Texture height in pixels.
	uint16				ArraySize;					///< Size of array.
	bool				IsCubeMap : 1;				///< True if texture is cube map.
	TextureType			TextureType;				///< Texture type (number of dimensions, multsampling). Only 2-dimensional textures are spoprted now (can be array).
	ResourceFormat		Format;						///< Texture format.
	MipMapsInfo			MipMaps;					///< Mipmaps generation information.
	TextureUsageInfo	TextureUsage;

// ================================ //
//
	explicit		TextureInitData( BufferRaw&& buffer )
		:	Data( std::move( buffer ) )
	{
		ArraySize = 1;
		TextureUsage.CPURead = false;
		TextureUsage.CPUWrite = false;
		TextureUsage.AllowShareResource = false;
		IsCubeMap = false;
		MipMaps.GenerateMipMaps = false;
		TextureUsage.Usage = ResourceUsage::Default;
		MipMaps.Filter = MipMapFilter::Unknown;
		MipMaps.CutOffMipMaps = 0;
		TextureType = TextureType::Texture2D;
		Format = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;
	}
	
	// ================================ //
	//
	uint16				NumMipMapLevels	() const
	{
		// If there's only original texture, we return only 1 mipmap what means that there's only
		// original texture.
		if( !MipMaps.GenerateMipMaps )
			return 1;

		auto size = std::max( Width, Height );
		auto levels = 1 + (uint32)std::floor( std::log2( size ) );
		return levels - MipMaps.CutOffMipMaps;
	}

public:
	virtual TypeID		GetAssetType	() const override { return TypeID::get< Texture >(); }
};



}	// sw

