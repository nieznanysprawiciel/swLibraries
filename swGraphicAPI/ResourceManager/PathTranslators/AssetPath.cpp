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


namespace impl
{
	std::regex		sAssetPathRegex( "^(.*?)(?:::(.*))?$" );
}


// ================================ //
//
Nullable< AssetPath >			AssetPath::FromString		( const std::string& assetPath )
{
	std::smatch match;

	if( std::regex_search( assetPath, match, impl::sAssetPathRegex ) )
	{
		// Ignore first match, it represents full match, that is full string.
		return AssetPath( match[ 1 ], match[ 2 ] );
	}

	return std::make_shared< RuntimeException >( "String can't be converted to AssetPath." );
}


}	// sw

