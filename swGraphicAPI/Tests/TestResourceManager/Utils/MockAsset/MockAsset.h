#pragma once
/**
@file MockAsset.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Resources/ResourceObject.h"



namespace sw
{

class MockAssetCreator;


/**@brief Mocks asset.*/
class MockAsset : public Resource
{
private:

	MockAssetCreator*		m_creator;		///< Remembers creator to remove reference after deletion.
	std::string				m_name;

protected:
public:
	explicit		MockAsset		( MockAssetCreator* creator, const AssetPath& name );
	virtual			~MockAsset		();

public:


	// Inherited via Resource
	virtual std::string				GetResourceName		() const override;

};



}	// sw



