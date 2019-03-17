#pragma once
/**
@file ResourceManagerException.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Exceptions/Exception.h"
#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/System/Path.h"


namespace sw
{

/**@brief Exceptions tells that two types cannot be bound.
@ingroup BindingExceptions*/
class ResourceManagerException : public RuntimeException
{
private:
protected:

	filesystem::Path		m_resourceName;
	TypeID					m_resourceType;

public:
	explicit		ResourceManagerException	( const std::string& error, const filesystem::Path& name, TypeID assetType );
	virtual			~ResourceManagerException	() = default;

	std::string		ErrorMessage				() const override;

private:

	std::string		ResourceManagerHeader		() const;
	std::string		ResourceInfo				() const;
};


}	// sw


