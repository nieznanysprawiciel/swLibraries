#pragma once
/**
@file FileNotFoundException.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Exception.h"
#include "swCommonLib/System/Path.h"


namespace sw
{


/**@brief 
@ingroup Helpers*/
class FileNotFoundException : public Exception
{
	RTTR_ENABLE( Exception );
private:
protected:

	filesystem::Path		m_path;

public:
	explicit		FileNotFoundException		( filesystem::Path filePath );
	virtual			~FileNotFoundException		() = default;

public:

	virtual std::string			ErrorMessage		() const;

	const filesystem::Path&		GetFilePath			() const { return m_path; }
};




}	// sw

