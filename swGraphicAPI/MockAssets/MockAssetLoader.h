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
	TypeID		MockAssetLoadInfo::GetAssetType	() const override { return TypeID::get< MockAsset >(); }
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
	virtual LoadingResult		Load			( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory ) override;
	virtual ReturnResult		Prefetch		( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory ) override;

};




}	// sw



