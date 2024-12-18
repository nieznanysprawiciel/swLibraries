#pragma once
/**
@file PathsManager.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/System/Path.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"

#include <string>
#include <map>


namespace sw
{


/**@brief Translates paths.

PathsManager stores paths aliases and can translate them to absolute paths during programm execution.
Example alias $(APP_DIR) would be resolved to absolut path.*/
class PathsManager
{
private:
protected:

	std::map< std::string, fs::Path >		m_aliases;

public:
	explicit		PathsManager		() = default;
					~PathsManager		() = default;

public:

	fs::Path				Translate			( const fs::Path& path ) const;
	Nullable< fs::Path >	FindAlias			( const std::string& alias ) const;

public:

	///@name Aliases registration API
	///@{

	/**@brief Adds new alias.
	Alias must have valid format $(ALIAS_NAME). If alias already existed it won't be overwritten.
	@return If user provides existing or invalid alias, function returns false.*/
	ReturnResult			RegisterAlias		( const std::string& alias, const fs::Path& path );

	///@}

	///@name API for TestFramework. Don't use in normal applications.
	///@{
	ReturnResult			OverrideAlias		( const std::string& alias, const fs::Path& path );

	///@}


public:

	static bool				IsValidAlias		( const std::string& alias );
};

DEFINE_OPTR_TYPE( PathsManager )
DEFINE_UPTR_TYPE( PathsManager )
DEFINE_PTR_TYPE( PathsManager )


}	// sw

