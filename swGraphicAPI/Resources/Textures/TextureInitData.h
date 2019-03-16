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
	bool				CPURead : 1;				///< Allows to read texture by CPU.
	bool				CPUWrite : 1;				///< Allows to write texture by CPU.
	bool				AllowShareResource : 1;		///< Can share resource between multiple graphic APIs.
	bool				IsCubeMap : 1;				///< True if texture is cube map.
	bool				GenerateMipMaps : 1;		///< Will automatically generates mipmpas.
	TextureType			TextureType;				///< Texture type (number of dimensions, multsampling). Only 2-dimensional textures are spoprted now (can be array).
	ResourceUsage		Usage;						///< Texture usage type. Influences how texture will be placed in GPU memory.
	ResourceFormat		Format;						///< Texture format.
	MipMapFilter		MipMapFilter;				///< Filtering used to generate mipmaps. Valid only if GenerateMipMaps is set to true.
	uint16				MipMapLevels;				///< Number of mipmaps levels. 1 means only original texture.
	uint16				CutOffMipMaps;				///< Removes number of mipmaps levels. Useful when we don't need full resolution of mipmaps (for example using dynamic LoD).
													///< Set value to 1 if you want to replace original texture with first mipmap.

// ================================ //
//
	explicit		TextureInitData( BufferRaw&& buffer )
		:	Data( std::move( buffer ) )
	{
		ArraySize = 1;
		CPURead = false;
		CPUWrite = false;
		AllowShareResource = false;
		IsCubeMap = false;
		GenerateMipMaps = false;
		Usage = ResourceUsage::Default;
		MipMapFilter = MipMapFilter::Unknown;
		MipMapLevels = 1;
		CutOffMipMaps = 0;
		TextureType = TextureType::Texture2D;
		Format = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;
	}
		

public:
	virtual TypeID		GetAssetType	() const override { return TypeID::get< Texture >(); }
};



}	// sw

