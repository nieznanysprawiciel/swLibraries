#pragma once
/**
@file Utils.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/ResourceManager.h"


#include "swGraphicAPI/MockAssets/MockAssetCreator.h"
#include "swGraphicAPI/MockAssets/MockAsset.h"
#include "swGraphicAPI/MockAssets/MockAssetLoader.h"
#include "swGraphicAPI/MockAssets/MockCompositeAsset.h"
#include "swGraphicAPI/MockAssets/MockCompositeAssetCreator.h"
#include "swGraphicAPI/MockAssets/MockCompositeAssetLoader.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/Shaders/ShaderCreator.h"
#include "swGraphicAPI/ResourceManager/Loaders/ShaderLoader.h"
#include "swGraphicAPI/ResourceManager/Loaders/RenderTargetLoader.h"
#include "swGraphicAPI/Loaders/SoilTextureLoader/SoilTextureLoader.h"

#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


namespace sw
{

// ================================ //
//
inline std::unique_ptr< ResourceManager >			CreateResourceManagerWithMocks				()
{
	std::unique_ptr< ResourceManager > rm = std::make_unique< ResourceManager >();

	auto pm = rm->GetPathsManager();
	pm->RegisterAlias( "$(TestAssets)", "." );
	pm->RegisterAlias( "$(MocksDir)", "$(TestAssets)/mock/" );
    pm->RegisterAlias( "$(TestWorkingDir)", "Working-Dir" );

	{
		auto creator = MockAssetCreator::CreateCreator();		// Creator must live longer then ResourceManager since it tracks references of created assets.
		auto loader = std::make_shared< MockAssetLoader >();

		rm->RegisterAssetCreator( creator );
		rm->RegisterLoader( loader );
	}

	{
		auto creator = MockCompositeAssetCreator::CreateCreator();
		auto loader = std::make_shared< MockCompositeAssetLoader >();

		rm->RegisterAssetCreator( creator );
		rm->RegisterLoader( loader );
	}

	return std::move( rm );
}

// ================================ //
//
inline std::unique_ptr< ResourceManager >			CreateResourceManagerWithMocksAndDefaults	()
{
	auto rm = CreateResourceManagerWithMocks();

	{
		auto loader = std::make_shared< ShaderLoader >();
		rm->RegisterLoader( loader );
	}

	{
		auto loader = std::make_shared< RenderTargetLoader >();
		rm->RegisterLoader( loader );
	}

	return std::move( rm );
}

// ================================ //
//
inline std::unique_ptr< ResourceManager >			CreateRMWithDefaultsMocksSoil				()
{
	auto rm = CreateResourceManagerWithMocksAndDefaults();

	{
		auto loader = std::make_shared< SoilTextureLoader >();
		rm->RegisterLoader( loader );
	}

	return std::move( rm );
}


}	// sw



