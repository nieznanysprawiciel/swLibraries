#pragma once
/**
@file ShaderLoader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/IAssetLoader.h"


namespace sw
{

/**@brief Loads shader from file.

This class only loads content of file. There's nothing magical or interesting here.*/
class ShaderLoader : public IAssetLoader
{
private:
protected:
public:
	explicit		ShaderLoader		() = default;
	virtual			~ShaderLoader		() = default;


	virtual bool											CanLoad			( const filesystem::Path& filePath, TypeID resourceType )																override;
	virtual LoadingResult									Load			( const filesystem::Path& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMAsyncLoaderAPI factory )	override;
	virtual ReturnResult									Prefetch		( const filesystem::Path& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMAsyncLoaderAPI factory )	override;

};



}	// sw

