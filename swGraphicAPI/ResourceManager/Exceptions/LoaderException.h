#pragma once
/**
@file LoaderException.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Exceptions/Exception.h"
#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"
#include "swGraphicAPI/ResourceManager/PathTranslators/LoadPath.h"


namespace sw
{

class LoaderException;
DEFINE_PTR_TYPE( LoaderException );


/**@brief Base exception for Loaders error.
@ingroup Loaders*/
class LoaderException : public RuntimeException
{
	RTTR_ENABLE( RuntimeException );
private:
protected:

	LoadPath				m_path;
	TypeID					m_resourceType;
	std::string				m_loaderName;

public:
	explicit		LoaderException				( std::string loaderName, std::string error, LoadPath path, TypeID assetType );
	virtual			~LoaderException			() = default;

	std::string		ErrorMessage				() const override;

private:

	std::string		LoaderHeader				() const;
	std::string		ResourceInfo				() const;

public:

	static LoaderExceptionPtr		Create		( std::string loaderName, std::string error, LoadPath path, TypeID assetType );
};


}	// sw




