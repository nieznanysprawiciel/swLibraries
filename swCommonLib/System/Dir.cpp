/**
@file Dir.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Dir.h"

#include <filesystem>


namespace filesystem
{


// ================================ //
//
bool			Dir::CreateDirectory		( const filesystem::Path& path )
{
	if( path.HasFileName() )
		return std::filesystem::create_directories( path.GetParent().String() );
	else
		return std::filesystem::create_directories( path.String() );
}

// ================================ //

std::vector< Path >			Dir::ListFiles( const filesystem::Path& path )
{
	if( std::filesystem::exists( path.String() ) )
	{
        std::vector< Path > files;
		for( auto const& dir_entry : std::filesystem::directory_iterator{ path.GetStdPath() } )
		{
            if( dir_entry.is_regular_file() )
                files.push_back( filesystem::Path( dir_entry.path() ) );
        }
        return files;
	}
    return std::vector< Path >();
}

}
