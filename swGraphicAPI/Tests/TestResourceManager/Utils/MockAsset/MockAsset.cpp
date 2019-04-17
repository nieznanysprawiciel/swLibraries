#include "MockAsset.h"
/**
@file MockAsset.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "MockAssetCreator.h"




namespace sw
{



// ================================ //
//
MockAsset::MockAsset		( MockAssetCreator* creator, const AssetPath& name )
	:	Resource( name )
	,	m_creator( creator )
	,	m_name( name.String() )
{
	m_creator->OnCreateAsset( this );
}

// ================================ //
//
MockAsset::~MockAsset()
{
	m_creator->OnDeleteAsset( this );
}

// ================================ //
//
std::string				MockAsset::GetResourceName			() const
{
	return m_name;
}

}	// sw

