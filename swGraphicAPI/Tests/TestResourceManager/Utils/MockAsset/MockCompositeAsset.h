#pragma once
/**
@file MockCompositeAsset.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swGraphicAPI/Resources/ResourceObject.h"

#include "MockAsset.h"

#include <vector>




namespace sw
{

class MockCompositeAsset;
DEFINE_RESOURCE_PTR_TYPE( MockCompositeAsset );


/**@brief Mock Asset with dependent MockAssets.*/
class MockCompositeAsset : public Resource
{
private:

	std::vector< MockAssetPtr >					m_subAssets;
	std::vector< MockCompositeAssetPtr >		m_compositeSubAssets;

public:
	explicit			MockCompositeAsset	( const AssetPath& name, std::vector< MockAssetPtr > subAssets, std::vector< MockCompositeAssetPtr > composites );
	virtual				~MockCompositeAsset	();


public:

	std::vector< MockAssetPtr >				GetSubAssets			() const { return m_subAssets; }
	std::vector< MockCompositeAssetPtr >	GetCompositeSubAssets	() const { return m_compositeSubAssets; }
};

}	// sw


