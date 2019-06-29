#pragma once
/**
@file TextureLoadInfo.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/Resources/Textures/TextureInitData.h"


namespace sw
{

/**@defgroup TexturesLoaders Textures Loaders
@ingroup Loaders*/




/**@brief Describes how Loader should process source texture data.
@ingroup TexturesLoaders*/
struct TextureProcessingInfo
{
	bool				ForceFormat;				///< Loader should generate texture in TargetFormat no matter what it loaded.
	ResourceFormat		TargetFormat;


	// ================================ //
	//
	TextureProcessingInfo()
		:	ForceFormat( false )
		,	TargetFormat( ResourceFormat::RESOURCE_FORMAT_UNKNOWN )
	{}
};




/**@brief Descriptor informs loader how to load Texture.
@ingroup TexturesLoaders*/
class TextureLoadInfo : public IAssetLoadInfo
{
public:

	MipMapsInfo					MipMaps;
	TextureUsageInfo			TextureUsage;
	TextureProcessingInfo		Processing;

public:
	explicit		TextureLoadInfo		() = default;
	virtual			~TextureLoadInfo	() = default;

public:

	
	virtual TypeID	GetAssetType		() const		{ return TypeID::get< Texture >(); }

};




}	// sw



