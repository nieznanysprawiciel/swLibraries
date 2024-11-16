#pragma once
/**
@file Path.h
@author nieznanysprawiciel
@copyright This file is part of the SWEngine graphics engine.

Implementation of the Path class. Since Path is not yet part of the C++ standard,
but will be included with C++17, this wrapper is needed.
Currently, implementations for different compilers place this class in different namespaces,
so it cannot be implemented fully portably.*/


// Supress deprecation warning. We nned to remember to use
// replacement in future when it will be introduced in standard.
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING


#include <filesystem>


#include <string>
#include <codecvt>

#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Macros/DefineFmtFormatter.h"


namespace sw {
namespace fs
{


/**@brief Wrapper for std path.*/
class Path
{
private:
    std::filesystem::path m_path;

public:

	explicit				Path			();
							Path			( const Path& path )			= default;
							Path			( Path&& path )					= default;
							Path			( const std::wstring& path );

	template< class Source >
							Path			( const Source& source );


	Path&					operator=		( const Path& other );
	Path&					operator=		( Path&& other );

	Path&					operator/=		( const Path& other );
	bool					operator==		( const Path& other ) const;
	bool					operator!=		( const Path& other ) const;
	bool					operator<		( const Path& other ) const;
	bool					operator<=		( const Path& other ) const;
	bool					operator>		( const Path& other ) const;
	bool					operator>=		( const Path& other ) const;

	friend Path				operator/		( const Path& path1, const Path& path2 );

	std::string				String			() const;
	std::wstring			WString			() const;


	std::string				GetFileName		() const;
	std::string				GetExtension	() const;
	Path					GetParent		() const;
	Path					GetDirectory	() const;

	Path					Normalize		() const;
	Path					MakeAbsolute	() const;
    Path				    ChangeExtension	( const std::string& extension ) const;
    Path                    RelativeTo		( const Path& base ) const;

	//bool					HasRoot			() const;
	bool					HasFileName		() const;
	bool					HasExtension	() const;

	bool					IsRelative		() const;
	bool					IsAbsolut		() const;
    bool                    IsEmpty         () const;

	/**@brief Checks if file or directory exists on filesystem.*/
	bool					Exists			() const;

	static Path				WorkingDirectory();

public:
	std::filesystem::path	GetStdPath		() const;

public:

	///@note This function may change or disapear in future.
	std::vector< std::string >		GetTokens			() const;
};


// ================================ //
//
template< class Source >
inline		Path::Path		( const Source& source )
	:	m_path( std::filesystem::path( source ) )
{}

// ================================ //
//
inline		Path::Path()
{}

// ================================ //
//
inline		Path::Path		( const std::wstring& path )
{
	m_path = std::filesystem::path( Convert::ToString( path ) );
}

// ================================ //
//
inline Path&	Path::operator=		( const Path& other )
{
	m_path = other.m_path;
	return *this;
}

// ================================ //
//
inline Path&	Path::operator=		( Path&& other )
{
	m_path = std::move( other.m_path );
	return *this;
}

// ================================ //
//
inline Path&	Path::operator/=	( const Path& other )
{
	m_path = m_path / other.m_path;
	return *this;
}

// ================================ //
//
inline bool		Path::operator==	( const Path& other ) const
{
	return m_path == other.m_path;
}

// ================================ //
//
inline bool		Path::operator!=	( const Path& other ) const
{
	return m_path != other.m_path;
}

// ================================ //
//
inline bool		Path::operator<		( const Path& other ) const
{
	return m_path < other.m_path;
}

// ================================ //
//
inline bool		Path::operator<=	( const Path& other ) const
{
	return m_path <= other.m_path;
}

// ================================ //
//
inline bool		Path::operator>		( const Path& other ) const
{
	return m_path > other.m_path;
}

// ================================ //
//
inline bool		Path::operator>=	( const Path& other ) const
{
	return m_path >= other.m_path;
}

// ================================ //

inline std::ostream&	operator<<( std::ostream& os, const Path& value )
{
    os << value.String();
    return os;
}

/**@brief */
inline std::string		Path::String() const
{
	return m_path.string();
}

/**@brief */
inline std::wstring		Path::WString() const
{
    return m_path.wstring();
}

/**@brief */
inline std::string		Path::GetFileName() const
{
	return m_path.filename().string();
}

/**@brief */
inline std::string		Path::GetExtension() const
{
	return m_path.extension().string();
}

/**@brief */
inline Path				Path::GetParent() const
{
	return m_path.parent_path();
}

/**@brief */
inline Path				Path::GetDirectory() const
{
	if( HasFileName() )
		return GetParent();
	else
		return Path( *this );
}

/**@brief Normalizes path.
@attention Current implementation might not work fully.*/
inline Path				Path::Normalize() const
{
    return m_path.lexically_normal();
}

// ================================ //
//
inline Path				Path::MakeAbsolute	() const
{
    return std::filesystem::absolute( m_path );
}

// ================================ //
//
inline Path				Path::ChangeExtension( const std::string& extension ) const
{
    auto ext = m_path.extension();
    auto filename = m_path.filename().string();

    if( filename == "." || filename == ".." )
        return Path( *this );

    return std::filesystem::path( m_path ).replace_extension( std::filesystem::path( extension ) );
}

// ================================ //

inline Path				Path::RelativeTo( const Path& base ) const
{
    return m_path.lexically_relative( base.m_path );
}

///**@brief */
//inline bool				Path::HasRoot() const
//{
//	return m_path.has_root_directory();
//}

/**@brief */
inline bool				Path::HasFileName() const
{
	return !m_path.empty();
}

/**@brief */
inline bool				Path::HasExtension() const
{
	return !GetExtension().empty();
}

/**@brief */
inline bool				Path::IsRelative() const
{
	return !IsAbsolut();
}

/**@brief */
inline bool				Path::IsEmpty() const
{
    return m_path.empty();
}

/**@brief */
inline bool				Path::IsAbsolut() const
{
	return m_path.is_absolute();
}

/**@brief Check if file exists.*/
inline bool				Path::Exists() const
{
    return std::filesystem::exists( m_path );
}

// ================================ //
//
inline Path				Path::WorkingDirectory()
{
    return std::filesystem::current_path();
}

/**@brief */
inline Path				operator/( const Path& path1, const Path& path2 )
{
	Path newPath = path1;
	newPath /= path2;
	return newPath;
}

// ================================ //
//
inline std::vector< std::string >	Path::GetTokens	() const
{
    std::vector< std::string > tokens;
    for( auto it = m_path.begin(); it != m_path.end(); ++it )
        tokens.push_back( it->string() );

    return tokens;
}

}
}

DEFINE_FMT_FORMATTER( sw::fs::Path, "{}", String() );

