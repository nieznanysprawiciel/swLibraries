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


namespace sw {
namespace fs
{

// ================================ //
//
std::filesystem::path GetStdPath( const Path& path )
{
    return std::filesystem::path( path.WString() );
}

// ================================ //
//
File::File( const Path& path ) : m_filePath( path ) {}

// ================================ //
//
File::File( Path&& path ) : m_filePath( std::move( path ) ) {}

/**@brief */
bool            File::Exists() const
{
    return m_filePath.Exists();
}

/**@brief */
Size            File::FileSize() const
{
    return std::filesystem::file_size( GetStdPath( m_filePath ) );
}

/**@brief */
bool            File::Remove()
{
    return std::filesystem::remove( GetStdPath( m_filePath ) );
}

/**@brief */
bool            File::Move( const Path& newPath )
{
    std::error_code error;
    std::filesystem::rename( GetStdPath( m_filePath ), GetStdPath( newPath ), error );

    if( error )
        return false;
    return true;
}

/**@brief */
bool            File::Copy( const Path& newPath )
{
    return std::filesystem::copy_file( GetStdPath( m_filePath ), GetStdPath( newPath ) );
}

// ================================ //
//
std::string     File::Load( const Path& path )
{
    std::ifstream     file( path.String() );
    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

// ================================ //
//
bool            File::Save( const Path& path, const std::string& content )
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

}  // fs
}  // namespace sw
