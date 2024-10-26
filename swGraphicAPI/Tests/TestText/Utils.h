#pragma once
/**
@file Utils.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"

#include "swGraphicAPI/Assets/TextAsset/Loader/FontAssetCreator.h"
#include "swGraphicAPI/Assets/TextAsset/Loader/FontLoader.h"
#include "swGraphicAPI/MockAssets/Utils.h"

using namespace sw;

// ================================ //
//
inline std::unique_ptr< ResourceManager >			CreateResourceManagerWithFonts	()
{
    auto rm = CreateResourceManagerWithMocksAndDefaults();

    rm->RegisterAssetCreator( FontCreator::CreateCreator() );
    rm->RegisterLoader( std::make_shared< FreeTypeLoader >() );

    auto pm = rm->GetPathsManager();
    pm->RegisterAlias( "$(FontsAssets)", "$(TestAssets)/fonts/" );

    return std::move( rm );
}
