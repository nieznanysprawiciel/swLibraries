#pragma once
/**
@file Utils.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/nResourceManager.h"


#include "swGraphicAPI/Tests/TestResourceManager/Utils/MockAsset/MockAssetCreator.h"
#include "swGraphicAPI/Tests/TestResourceManager/Utils/MockAsset/MockAsset.h"
#include "swGraphicAPI/Tests/TestResourceManager/Utils/MockAsset/MockAssetLoader.h"



namespace sw
{

// ================================ //
//
std::unique_ptr< nResourceManager >		CreateResourceManagerWithMocks	()
{
	auto creator = MockAssetCreator::CreateCreator();		// Creator must live longer then ResourceManager since it tracks references of created assets.
	auto loader = std::make_shared< MockAssetLoader >();

	std::unique_ptr< nResourceManager > rm = std::make_unique< nResourceManager >();
	rm->RegisterAssetCreator( creator );
	rm->RegisterLoader( loader );

	return std::move( rm );
}


}	// sw


