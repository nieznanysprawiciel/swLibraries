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
	std::string				m_content;

protected:
public:
	explicit		MockAsset		( MockAssetCreator* creator, const AssetPath& name, const std::string& content );
	virtual			~MockAsset		();

public:

	std::string		GetContent		() const { return m_content; }

};
DEFINE_RESOURCE_PTR_TYPE( MockAsset )


}	// sw



