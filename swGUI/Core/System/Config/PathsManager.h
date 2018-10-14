#pragma once

#include "swCommonLib/System/Path.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"

#include <string>
#include <map>


namespace sw {
namespace gui
{


/**@brief Translates paths.

PathsManager stores paths aliases and can translate them to absolute paths during programm execution.
Example alias $(APP_DIR) would be resolved to absolut path.

@todo This class could be placed inside ResourceManager. This would allow us to use paths relative
to aliases in whole invironement and translate them only while loading assets.*/
class PathsManager
{
private:
protected:

	std::map< std::string, filesystem::Path >		m_aliases;

public:
	explicit		PathsManager		() = default;
					~PathsManager		() = default;

public:

	filesystem::Path		Translate			( const filesystem::Path& path ) const;

public:

	///@name Aliases registration API
	///@{

	/**@brief Adds new alias.
	Alias must have valid format $(ALIAS_NAME). If alias already existed it won't be overwritten.
	@return If user provides existing or invalid alias, function returns false.*/
	ReturnResult			RegisterAlias		( const std::string& alias, const filesystem::Path& path );

	///@}


protected:

	bool					IsValidAlias		( const std::string& alias ) const;
};





}	// gui
}	// sw

