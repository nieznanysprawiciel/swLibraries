/**
@file PathsManager.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "PathsManager.h"

#include <filesystem>
#include <regex>



namespace sw
{


std::regex gAliasFormat( "^\\$\\([_\\-.[:alnum:]]+\\)$" );


// ================================ //
//
fs::Path			PathsManager::Translate				( const fs::Path& path ) const
{
	// Absolut paths don't need translation.
	if( path.IsRelative() )
	{
		const auto segments = path.GetTokens();
		if( segments.size() > 0 )
		{
			const auto& alias = segments[ 0 ];
			if( IsValidAlias( alias ) )
			{
				auto iter = m_aliases.find( alias );
				if( iter != m_aliases.end() )
				{
                    fs::Path relativePart = path.ClipFromRoot( 1 );
					return iter->second / relativePart;
				}
			}
		}
	}

	return path;
}

// ================================ //
//
Nullable< fs::Path >	PathsManager::FindAlias		( const std::string& alias ) const
{
	auto iter = m_aliases.find( alias );

	if( iter == m_aliases.end() )
		return std::make_shared< RuntimeException >( "Alias " + alias + " is not registered." );

	return iter->second;
}

// ================================ //
//
ReturnResult		PathsManager::RegisterAlias			( const std::string& alias, const fs::Path& path )
{
	if( IsValidAlias( alias ) )
	{
		auto iter = m_aliases.find( alias );

		if( iter != m_aliases.end() )
			return Success::False;

		m_aliases[ alias ] = Translate( path );

		return Success::True;
	}

	return Success::False;
}

// ================================ //
//
bool				PathsManager::IsValidAlias			( const std::string& alias )
{
	return std::regex_match( alias, gAliasFormat );
}


//====================================================================================//
//			API for TestFramework	
//====================================================================================//

// ================================ //
//
ReturnResult		PathsManager::OverrideAlias			( const std::string& alias, const fs::Path& path )
{
	if( IsValidAlias( alias ) )
	{
		auto iter = m_aliases.find( alias );

		if( iter == m_aliases.end() )
			return Success::False;

		m_aliases[ alias ] = Translate( path );

		return Success::True;
	}

	return Success::False;
}


}	// sw



