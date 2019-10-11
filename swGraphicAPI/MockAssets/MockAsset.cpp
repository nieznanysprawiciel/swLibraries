/**
@file MockAsset.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/MockAssets/stdafx.h"

#include "MockAsset.h"
#include "MockAssetCreator.h"




namespace sw
{



// ================================ //
//
MockAsset::MockAsset		( MockAssetCreator* creator, const AssetPath& name, const std::string& content )
	:	Resource( name )
	,	m_creator( creator )
	,	m_content( content )
{
	m_creator->OnCreateAsset( this );
}

// ================================ //
//
MockAsset::~MockAsset()
{
	m_creator->OnDeleteAsset( this );
}


}	// sw

