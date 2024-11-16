/**
@file Dir.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Dir.h"

#include <filesystem>

namespace sw {
namespace fs
{


// ================================ //
//
bool			Dir::CreateDirectory		( const fs::Path& path )
{
	if( path.HasFileName() )
		return std::filesystem::create_directories( path.GetParent().String() );
	else
		return std::filesystem::create_directories( path.String() );
}

// ================================ //

std::vector< Path >			Dir::ListFiles( const fs::Path& path )
{
	if( std::filesystem::exists( path.String() ) )
	{
        std::vector< Path > files;
		for( auto const& dir_entry : std::filesystem::directory_iterator{ path.GetStdPath() } )
		{
            if( dir_entry.is_regular_file() )
                files.push_back( fs::Path( dir_entry.path() ) );
        }
        return files;
	}
    return std::vector< Path >();
}

/**@brief Returns standard library path.
Use only if you must.*/
std::filesystem::path		Path::GetStdPath() const
{
    return std::filesystem::path( m_path.str() );
}

}

}
