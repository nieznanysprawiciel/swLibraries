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
#include "Filesystem/filesystem/path.h"


#include <string>
#include <codecvt>

#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Macros/DefineFmtFormatter.h"


namespace sw {
namespace fs
{


/**@brief Wrapper for Path.
Class can't use std::filesystem::path, because in some places library use Resources names
that contain illigal signs.*/
class Path
{
private:
	::filesystem::path_impl		m_path;

public:

	explicit				Path			();
							Path			( const Path& path )			= default;
							Path			( Path&& path )					= default;
							Path			( const std::wstring& path );
							Path			( const std::filesystem::path& path );

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
	const std::vector< std::string >&		GetTokens			() const;

	Path									ClipFromRoot		( int num ) const;
};


// ================================ //
//
template< class Source >
inline		Path::Path		( const Source& source )
	:	m_path( ::filesystem::path_impl( source ) )
{}

// ================================ //
//
inline		Path::Path()
{}

// ================================ //
//
inline		Path::Path		( const std::wstring& path )
{
	m_path = ::filesystem::path_impl( Convert::ToString( path ) );
}

// ================================ //

inline		Path::Path		( const std::filesystem::path& path )
{
    m_path = ::filesystem::path_impl( path.string() );
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
	return m_path.str() < other.m_path.str();
}

// ================================ //
//
inline bool		Path::operator<=	( const Path& other ) const
{
	return m_path.str() <= other.m_path.str();
}

// ================================ //
//
inline bool		Path::operator>		( const Path& other ) const
{
	return m_path.str() > other.m_path.str();
}

// ================================ //
//
inline bool		Path::operator>=	( const Path& other ) const
{
	return m_path.str() >= other.m_path.str();
}

///**@brief Por�wnuje �cie�ki. Przed por�wnaniem �cie�ki s� normalizowane.
//Paths must exist on file system.*/
//inline bool		Path::Compare		( const Path& path1, const Path& path2 )
//{
//	return experimental::equivalent( path1.m_path, path2.m_path );
//}

// ================================ //

inline std::ostream&	operator<<( std::ostream& os, const Path& value )
{
    os << value.String();
    return os;
}

/**@brief */
inline std::string		Path::String() const
{
	return m_path.str();
}

/**@brief */
inline std::wstring		Path::WString() const
{
	return Convert::FromString< std::wstring >( m_path.str() );
}

/**@brief */
inline std::string		Path::GetFileName() const
{
	return m_path.filename();
}

/**@brief */
inline std::string		Path::GetExtension() const
{
    if( !HasFileName() )
        return "";
	return m_path.extension();
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
	auto& tokens = m_path.get_tokens();
	std::string normalized = "";

	// Avoid reallocating string all the time.
	size_t maxLen = 0;
	for( auto& token : tokens )
		maxLen += token.size();

	normalized.reserve( maxLen );
	normalized = *tokens.crbegin();

	size_t tokensToOmit = 0;
	for( auto i = ++tokens.crbegin(); i != tokens.crend(); ++i )
	{
		if( *i == ".." )
		{
			tokensToOmit++;
		}
		else
		{
			if( tokensToOmit == 0 )
			{
				// Add token to path from back to beginning.
				normalized = *i + "/" + normalized;
			}
			else
			{
				tokensToOmit--;
			}
		}
	}

	// Add all .. signs that remained to the beginning.
	while( tokensToOmit > 0 )
	{
		normalized = "../" + normalized;
		tokensToOmit--;
	}

	return ::filesystem::path_impl( normalized );
}

// ================================ //
//
inline Path				Path::MakeAbsolute	() const
{
	return m_path.make_absolute();
}

// ================================ //
//
inline Path				Path::ChangeExtension( const std::string& extension ) const
{
    auto ext = m_path.extension();
	auto filename = m_path.filename();

    if( filename == "." || filename == ".." )
        return Path( *this );

	auto startPos = filename.rfind( ext );
	if( startPos != std::string::npos )
	{
		filename.replace( startPos, filename.length(), extension );
		return m_path.parent_path() / filename;
	}
    return Path( *this );
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
	return m_path.exists();
}

// ================================ //
//
inline Path				Path::WorkingDirectory()
{
    return ::filesystem::path_impl::getcwd();
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
inline const std::vector< std::string >&		Path::GetTokens	() const
{
	return m_path.get_tokens();
}

// ================================ //
//
inline Path										Path::ClipFromRoot		( int num ) const
{
	return Path( m_path.clip_from_root( num ) );
}

}
}

DEFINE_FMT_FORMATTER( sw::fs::Path, "{}", String() );

