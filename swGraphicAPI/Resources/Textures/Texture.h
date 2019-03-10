#pragma once
/**
@file Texture.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swCommonLib/Common/ObjectDeleter.h"
#include "swCommonLib/System/Path.h"
#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/MemoryChunk.h"

#include "swGraphicAPI/Resources/ResourcePtr.h"
#include "swGraphicAPI/Resources/ResourceObject.h"
#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"


//----------------------------------------------------------------------------------------------//
//								Texture															//
//----------------------------------------------------------------------------------------------//


namespace sw
{

/**@defgroup Textures Textures
@ingroup Resources*/




/**@brief Textures filtering modes.

Filtering types used to create mipmaps.
@ingroup Textures*/
enum class MipMapFilter : short
{
	Box = 0,		///<
	Tent,			///< 
	Bell,			///<
	bSpline,		///<
	Mitchell,		///<
	Lanczos3,		///<
	Blackman,		///<
	Lanczos4,		///<
	Lanczos6,		///<
	Lanczos12,		///<
	Kaiser,			///<
	Gaussian,		///<
	Catmullrom,		///<
	QuadraticInterpolation,		///<
	QuadraticAproximation,		///<
	QuadraticMix,				///<

	Unknown						///<
};


/**@brief Texture descriptor.

@ingroup Textures*/
struct TextureInfo
{
	uint32				TextureWidth;				///< Texture width in pixels.
	uint32				TextureHeight;				///< Texture height in pixels.
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

	uint32				MemorySize;					///< Texture size in memory.
	filesystem::Path	FilePath;					///< Texture path or name.

// ================================ //
//
	explicit		TextureInfo()
	{
		ArraySize = 1;
		CPURead = false;
		CPUWrite = false;
		AllowShareResource = false;
		IsCubeMap = false;
		GenerateMipMaps = false;
		Usage = ResourceUsage::RESOURCE_USAGE_DEFAULT;
		MipMapFilter = MipMapFilter::Unknown;
		MipMapLevels = 1;
		CutOffMipMaps = 0;
		TextureType = TextureType::TEXTURE_TYPE_TEXTURE2D;
		MemorySize = 0;
	}

private:
	RTTR_REGISTRATION_FRIEND;

	int		GetWidth		() { return TextureWidth; }
	int		GetHeight		() { return TextureHeight; }
	int		GetArraySize	() { return ArraySize; }
	bool	IsCPUReadable	() { return CPURead; }
	bool	IsCPUWriteable	() { return CPUWrite; }
	bool	IsSharedResource() { return AllowShareResource; }
	bool	IsCubeMapTex	() { return IsCubeMap; }
	bool	GenMipMaps		() { return GenerateMipMaps; }
	int		GetMipLevels	() { return MipMapLevels; }

	std::string		GetPath	() { return FilePath.String(); }
};





/** @brief Base class for textures.
@ingroup Textures
@ingroup Resources
@ingroup GraphicAPI

This class is platform independent. Inherit it while implementing chosen graphic API.*/
class Texture : public Resource
{
	RTTR_ENABLE( Resource );
	friend ObjectDeleter<Texture>;
private:
protected:
	/// ¯eby unikn¹æ pomy³ki, obiekt mo¿e byœ kasowany tylko przez AssetsManager. Zapewnia to ObjectDeleter.
	virtual ~Texture() = default;
public:
	Texture() : Resource( 0 ) {}

	virtual const filesystem::Path&		GetFilePath		() const = 0;		///< Returns name of file, from which this object was created.

	/**@brief Updates texture data on graphic card.
	Note that size of dataPtr memory must large be enough to fill requested miplevel and array idx.
	You can always check @ref GetDescriptor function to get desired info.

	@todo Do something with this when rendering will use event queues.*/
	virtual bool						UpdateData		( uint8* dataPtr, uint16 mipLevel, uint16 arrayIdx ) = 0;

	/**@brief Copies texture data from graphic card to memory chunk.*/
	virtual MemoryChunk					CopyData		() const = 0;
	virtual const TextureInfo&			GetDescriptor	() const = 0;		///< Gets texture descriptor.

	virtual std::string					GetResourceName	() const override { return GetFilePath().String(); }

	inline bool operator==( Texture& object );
	inline bool operator==( const std::wstring& file_name );
};

}	// sw
