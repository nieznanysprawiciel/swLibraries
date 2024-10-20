/**
@file File.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "File.h"

#include "Dir.h"

#include <fstream>
#include <sstream>
#include <string>

#include <filesystem>

namespace fs = std::filesystem;


// ================================ //
//
fs::path		        GetStdPath( const filesystem::Path& path )
{
	return fs::path( path.WString() );
}


// ================================ //
//
filesystem::File::File		( const Path& path )
	:	m_filePath( path )
{ }

// ================================ //
//
filesystem::File::File		( Path&& path )
	:	m_filePath( std::move( path ) )
{}

/**@brief */
bool		filesystem::File::Exists	() const
{
	return m_filePath.Exists();
}

/**@brief */
Size		filesystem::File::FileSize	() const
{
	return fs::file_size( GetStdPath( m_filePath ) );
}

/**@brief */
bool		filesystem::File::Remove	()
{
	return fs::remove( GetStdPath( m_filePath ) );
}

/**@brief */
bool		filesystem::File::Move		( const Path& newPath )
{
	std::error_code error;
	fs::rename( GetStdPath( m_filePath ), GetStdPath( newPath ), error );
	
	if( error )
		return false;
	return true;
}

/**@brief */
bool		filesystem::File::Copy		( const Path& newPath )
{
	return fs::copy_file( GetStdPath( m_filePath ), GetStdPath( newPath ) );
}

// ================================ //
//
std::string			filesystem::File::Load		( const Path& path )
{
	std::ifstream file( path.String() );
	std::stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}

// ================================ //
//
bool				filesystem::File::Save		( const Path& path, const std::string& content )
{
	Dir::CreateDirectory( path );

	std::ofstream file( path.String() );
	if( file.is_open() )
	{
		file << content;
		return true;
	}

	return false;
}
