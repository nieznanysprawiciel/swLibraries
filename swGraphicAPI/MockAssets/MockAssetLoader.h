#pragma once
/**
@file MockAssetLoader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"

#include "MockAsset.h"



namespace sw
{

// ================================ //
//
class MockAssetLoadInfo : public IAssetLoadInfo
{
private:
protected:
public:
	explicit		MockAssetLoadInfo		() = default;
	virtual			~MockAssetLoadInfo		() = default;

public:
	// ================================ //
	//
	TypeID					GetAssetType	() const override { return TypeID::get< MockAsset >(); }
	virtual std::string		ResourceKey		() const override { return ""; }
};




/**@brief MockAsset loader.*/
class MockAssetLoader : public IAssetLoader
{
private:
protected:
public:
	explicit		MockAssetLoader		() = default;
	virtual			~MockAssetLoader	() = default;


	// Inherited via IAssetLoader
	virtual bool				CanLoad			( const AssetPath& filePath, TypeID resourceType ) override;
	virtual LoadingResult		Load			( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory ) override;
	virtual ReturnResult		Prefetch		( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory ) override;

};




}	// sw



