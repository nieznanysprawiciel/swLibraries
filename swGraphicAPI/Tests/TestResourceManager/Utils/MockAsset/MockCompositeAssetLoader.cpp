/**
@file MockAssetLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "MockCompositeAssetLoader.h"
#include "MockCompositeAsset.h"
#include "MockCompositeAssetCreator.h"
#include "MockAssetLoader.h"

#include "swCommonLib/System/File.h"
#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"

#include "swGraphicAPI/ResourceManager/Loaders/Tools/LoadingContext.h"


namespace sw
{

// ================================ //
//
bool				MockCompositeAssetLoader::CanLoad			( const AssetPath& filePath, TypeID resourceType )
{
	return resourceType == TypeID::get< MockCompositeAsset >();
}

// ================================ //
//
Nullable< MockAssetPtr >					LoadSubAsset		( const AssetPath& assetName, LoadingContext& context )
{
	auto& factory = context.Factory;
	MockAssetLoadInfo info;

	return factory.Load< MockAsset >( assetName, &info );
}

// ================================ //
//
Nullable< MockCompositeAssetPtr	>			LoadComposite		( const AssetPath& assetName, const MockCompositeAssetLoadInfo* compositeDesc, LoadingContext& context )
{
	ErrorsCollector collector;

	std::vector< MockCompositeAssetPtr >	compositeAssets;
	std::vector< MockAssetPtr >				subAssets;

	uint32 idx = 0;

	for( auto& nested : compositeDesc->NestedComposites )
	{
		AssetPath name( assetName.GetFile(), assetName.GetInternalPath() / Convert::ToString( idx ) );

		auto result = LoadComposite( name, nested.get(), context );
		if( collector.Success( result ) )
		{
			compositeAssets.push_back( result.Get() );
			context.AssetsCollection.push_back( result.Get().Ptr() );
		}

		idx++;
	}

	for( auto& subasset : compositeDesc->SubAssets )
	{
		auto result = LoadSubAsset( subasset, context );
		if( collector.Success( result ) )
		{
			subAssets.push_back( result.Get() );
			context.AssetsCollection.push_back( result.Get().Ptr() );
		}
	}

	MockCompositeAssetCreateInfo createInfo;
	createInfo.SubAssets			= std::move( subAssets );
	createInfo.CompositeSubAssets	= std::move( compositeAssets );

	auto result = context.Factory.CreateGenericAsset( assetName, TypeID::get< MockCompositeAsset >(), std::move( createInfo ) );
	if( collector.Success( result ) )
	{
		context.Warnings.Add( collector );
		return MockCompositeAssetPtr( static_cast< MockCompositeAsset* >( result.Get().Ptr() ) );
	}

	return collector.Get().GetError();
}


// ================================ //
//
LoadingResult		MockCompositeAssetLoader::Load				( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	LoadingResult loadingResult;

	if( resourceType != TypeID::get< MockCompositeAsset >() &&
		resourceType != TypeID::get< Resource >() )
		return "Can't load asset of type [" + resourceType.get_name().to_string() + "].";

	ErrorsCollector warnings;
	LoadingContext context( factory );

	auto typedDesc = static_cast< const MockCompositeAssetLoadInfo* >( assetDesc );
	auto result = LoadComposite( filePath, typedDesc, context );
	
	if( !result.IsValid() )
		return { result.GetError(), context.Warnings };

	// Asset that was requested as filePath parameter, should be on the first place of the array.
	context.AssetsCollection.insert( context.AssetsCollection.begin(), result.Get().Ptr() );

	return { std::move( context.AssetsCollection ), context.Warnings.GetException() };
}

// ================================ //
//
ReturnResult		MockCompositeAssetLoader::Prefetch			( const AssetPath & filePath, TypeID resourceType, const IAssetLoadInfo * assetDesc, RMLoaderAPI factory )
{
	return ReturnResult();
}

//====================================================================================//
//				MockCompositeAssetLoadInfo
//====================================================================================//

// ================================ //
//
MockCompositeAssetLoadInfo::MockCompositeAssetLoadInfo					( std::vector< MockCompositeAssetLoadInfoPtr > nested, std::vector< AssetPath > subAssets )
	:	NestedComposites( std::move( nested ) )
	,	SubAssets( std::move( subAssets ) )
{}

// ================================ //
//
MockCompositeAssetLoadInfoPtr		MockCompositeAssetLoadInfo::Create	( std::vector< MockCompositeAssetLoadInfoPtr > nested, std::vector< AssetPath > subAssets )
{
	return std::make_shared< MockCompositeAssetLoadInfo >( std::move( nested ), std::move( subAssets ) );
}

}	// sw


