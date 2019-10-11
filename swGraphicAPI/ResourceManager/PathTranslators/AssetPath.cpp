/**
@file AssetPath.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"


#include "swCommonLib/Common/Exceptions/Exception.h"
#include "AssetPath.h"

#include <regex>


namespace sw
{

// ================================ //
//
Nullable< AssetPath >			AssetPath::FromString		( const std::string& assetPath )
{
    static std::regex sAssetPathRegex( "^(.*?)(?:::(.*))?$" );

	std::smatch match;

	if( std::regex_match( assetPath, match, sAssetPathRegex ) )
	{
		// Ignore first match, it represents full match, that is full string.
		return AssetPath( match[ 1 ], match[ 2 ] );
	}

	return std::make_shared< RuntimeException >( "String can't be converted to AssetPath." );
}


}	// sw

