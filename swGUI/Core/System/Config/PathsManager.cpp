/**
@file PathsManager.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "PathsManager.h"

#include <filesystem>
#include <regex>

namespace sw {
namespace gui
{


std::regex gAliasFormat( "^\\$\\([_\\-.[:alnum:]]+\\)$" );


// ================================ //
//
filesystem::Path	PathsManager::Translate				( const filesystem::Path& path ) const
{
	// Absolut paths don't need translation.
	if( path.IsRelative() )
	{
		const auto& segments = path.GetTokens();
		if( segments.size() > 0 )
		{
			const auto& alias = segments[ 0 ];
			if( IsValidAlias( alias ) )
			{
				auto iter = m_aliases.find( alias );
				if( iter != m_aliases.end() )
				{
					filesystem::Path relativePart = path.ClipFromRoot( 1 );
					return iter->second / relativePart;
				}
			}
		}
	}

	return path;
}

// ================================ //
//
ReturnResult		PathsManager::RegisterAlias			( const std::string& alias, const filesystem::Path& path )
{
	if( IsValidAlias( alias ) )
	{
		auto iter = m_aliases.find( alias );

		if( iter != m_aliases.end() )
			return Result::Error;

		m_aliases[ alias ] = path;

		return Result::Success;
	}

	return Result::Error;
}

// ================================ //
//
bool				PathsManager::IsValidAlias			( const std::string& alias ) const
{
	return std::regex_match( alias, gAliasFormat );
}

}	// gui
}	// sw



