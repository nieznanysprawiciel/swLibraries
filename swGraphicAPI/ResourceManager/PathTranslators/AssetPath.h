#pragma once
/**
@file AssetPath.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/System/Path.h"


#include <tuple>


namespace sw
{


/**@brief Represents asset path.

Asset path consists of two parts:
- file path - which is normal path to file on user filesystem
- internal path - which points to specific asset inside file

Each file can contain multiple assets, for example mesh file contains vertex and index
buffers and materials. To load asset and assing it to enitity someone must provide it's full path.
Internal path can mean different things in different assets.
- It can be asset name inside file as in our example materials need to have different names, so 
we can distinguish between them
- Sometimes file could contain scene represented as tree and scene elements would have names after
their position in tree.
- Files can have their internal filesystem.*/
class AssetPath
{
private:

	filesystem::Path			m_filePath;			///< Path in filesystem.
	filesystem::Path			m_internalPath;		///< Internal path in asset file or simply asset name.

protected:
public:

	explicit		AssetPath		() = default;
	explicit		AssetPath		( filesystem::Path file, filesystem::Path internalPath );
					~AssetPath		() = default;

public:

	const filesystem::Path&			GetFile				() const { return m_filePath; }
	const filesystem::Path&			GetInternalPath		() const { return m_internalPath; }

public:

	bool					operator==		( const AssetPath& other ) const;
	bool					operator!=		( const AssetPath& other ) const;
	bool					operator<		( const AssetPath& other ) const;
	bool					operator<=		( const AssetPath& other ) const;
	bool					operator>		( const AssetPath& other ) const;
	bool					operator>=		( const AssetPath& other ) const;
};


//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
AssetPath::AssetPath		( filesystem::Path file, filesystem::Path internalPath )
	:	m_filePath( file )
	,	m_internalPath( internalPath )
{}

// ================================ //
//
inline bool			AssetPath::operator==		( const AssetPath& other ) const
{
	return std::tie( m_filePath, m_internalPath ) == std::tie( other.GetFile(), other.GetInternalPath() );
}

// ================================ //
//
inline bool			AssetPath::operator!=		( const AssetPath& other ) const
{
	return std::tie( m_filePath, m_internalPath ) != std::tie( other.GetFile(), other.GetInternalPath() );
}

// ================================ //
//
inline bool			AssetPath::operator<		( const AssetPath& other ) const
{
	return std::tie( m_filePath, m_internalPath ) < std::tie( other.GetFile(), other.GetInternalPath() );
}

// ================================ //
//
inline bool			AssetPath::operator<=		( const AssetPath& other ) const
{
	return std::tie( m_filePath, m_internalPath ) <= std::tie( other.GetFile(), other.GetInternalPath() );
}

// ================================ //
//
inline bool			AssetPath::operator>		( const AssetPath& other ) const
{
	return std::tie( m_filePath, m_internalPath ) > std::tie( other.GetFile(), other.GetInternalPath() );
}

// ================================ //
//
inline bool			AssetPath::operator>=		( const AssetPath& other ) const
{
	return std::tie( m_filePath, m_internalPath ) >= std::tie( other.GetFile(), other.GetInternalPath() );
}


}	// sw


