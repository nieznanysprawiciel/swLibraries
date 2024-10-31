#pragma once
/**
@file FreeTypeLoader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"

#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"


namespace sw
{

struct FontLayout;


/**@brief Loads fonts using FreeType Library.
http://freetype.org/freetype2/docs/tutorial/step1.html#section-1

@ingroup Text*/
class FreeTypeLoader : public IAssetLoader
{
protected:
public:
    explicit						FreeTypeLoader    () = default;
    virtual                         ~FreeTypeLoader   () = default;

    virtual bool					CanLoad				( const AssetPath& filePath, TypeID resourceType )															override;
    virtual LoadingResult			Load				( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI context )		override;
    virtual ReturnResult			Prefetch			( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;

public:
    /**@brief Renders Texture Atlas. Modifies FontLayout by adding texture mapping.*/
    Nullable< TexturePtr >          RenderAtlas         ( const LoadPath& filePath, FontLayout& initData, RMLoaderAPI factor );
    BufferTyped< u32 >              RenderAtlasToBuffer ( FontLayout& initData, uint32 width, uint32 height );
};


}	// sw