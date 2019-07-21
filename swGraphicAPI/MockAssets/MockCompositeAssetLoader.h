#pragma once
/**
@file MockCompositeAssetLoader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"

#include "MockCompositeAsset.h"



namespace sw
{

class MockCompositeAssetLoadInfo;
DEFINE_PTR_TYPE( MockCompositeAssetLoadInfo );


// ================================ //
//
class MockCompositeAssetLoadInfo : public IAssetLoadInfo
{
public:

	std::vector< MockCompositeAssetLoadInfoPtr >		NestedComposites;
	std::vector< AssetPath >							SubAssets;

protected:
public:
	explicit		MockCompositeAssetLoadInfo		( std::vector< MockCompositeAssetLoadInfoPtr > nested, std::vector< AssetPath > subAssets );
	virtual			~MockCompositeAssetLoadInfo		() = default;

public:
	// ================================ //
	//
	TypeID									GetAssetType	() const override { return TypeID::get< MockCompositeAsset >(); }


public:

	static MockCompositeAssetLoadInfoPtr	Create			( std::vector< MockCompositeAssetLoadInfoPtr > nested, std::vector< AssetPath > subAssets );
};




/**@brief MockAsset loader.*/
class MockCompositeAssetLoader : public IAssetLoader
{
private:
protected:
public:
	explicit		MockCompositeAssetLoader		() = default;
	virtual			~MockCompositeAssetLoader		() = default;


	// Inherited via IAssetLoader
	virtual bool				CanLoad			( const AssetPath& filePath, TypeID resourceType ) override;
	virtual LoadingResult		Load			( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory ) override;
	virtual ReturnResult		Prefetch		( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory ) override;

};




}	// sw

