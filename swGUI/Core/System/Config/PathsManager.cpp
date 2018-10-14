/**
@file PathsManager.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "PathsManager.h"

#include <regex>

namespace sw {
namespace gui
{


std::wregex gAliasFormat( L"\\$\\([_\\-.[:alnum:]]+\\)$" );

// ================================ //
//
ReturnResult		PathsManager::RegisterAlias			( const std::wstring& alias, const filesystem::Path& path )
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
bool				PathsManager::IsValidAlias			( const std::wstring& alias ) const
{
	return std::regex_match( alias, gAliasFormat );
}

}	// gui
}	// sw



