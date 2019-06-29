/**
@file MockCompositeAsset.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/MockAssets/stdafx.h"


#include "MockCompositeAsset.h"






namespace sw
{

// ================================ //
//
MockCompositeAsset::MockCompositeAsset		( const AssetPath& name, std::vector< MockAssetPtr > subAssets, std::vector< MockCompositeAssetPtr > composites )
	:	Resource( name )
	,	m_subAssets( std::move( subAssets ) )
	,	m_compositeSubAssets( std::move( composites ) )
{}

// ================================ //
//
MockCompositeAsset::~MockCompositeAsset()
{}

}	// sw


