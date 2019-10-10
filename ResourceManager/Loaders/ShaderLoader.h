#pragma once
/**
@file ShaderLoader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"


namespace sw
{

/**@brief Loads shader from file.

This class only loads content of file. There's nothing magical or interesting here.
@ingroup Loaders*/
class ShaderLoader : public IAssetLoader
{
private:
protected:
public:
	explicit		ShaderLoader		() = default;
	virtual			~ShaderLoader		() = default;


	virtual bool											CanLoad			( const AssetPath& filePath, TypeID resourceType )															override;
	virtual LoadingResult									Load			( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;
	virtual ReturnResult									Prefetch		( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;

};



}	// sw

