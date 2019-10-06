#pragma once
/**
@file LoadPath.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "PathsManager.h"
#include "AssetPath.h"

#include "swCommonLib/Common/Macros/DefineFmtFormatter.h"


namespace sw
{


/**@brief Represents path provided for @ref IAssetLoader.

This class stores both original AssetPath with aliases and translated path.
It need to make translation from @ref IAssetLoader.*/
class LoadPath
{
private:

    AssetPath			m_originalPath;
    AssetPath			m_translatedPath;

protected:
public:
    explicit		LoadPath		( AssetPath original, AssetPath translated );
    explicit		LoadPath		( AssetPath original, const PathsManager* pm );
    ~LoadPath		() = default;

public:

    /**@brief Gets file path ready to loading.
    Note that this path don't have aliases. If you want to build paths, better use not translated version.*/
    const filesystem::Path& GetFile				() const { return m_translatedPath.GetFile(); }

    const filesystem::Path& GetInternalPath		() const { return m_originalPath.GetInternalPath(); }
    const filesystem::Path& GetFileTranslated	() const { return m_translatedPath.GetFile(); }
    const filesystem::Path& GetFileOriginal		() const { return m_originalPath.GetFile(); }

    const AssetPath& GetOriginalPath		    () const { return m_originalPath; }
    const AssetPath& GetTranslatedPath	        () const { return m_translatedPath; }

public:

    /**@brief Extends internal path and returns new object.*/
    LoadPath						operator/			( const filesystem::Path& path ) const;

public:

    std::string						Print				() const;

public:

    static filesystem::Path			Translate			( const filesystem::Path& path, const PathsManager* pm );
    static AssetPath				Translate			( const AssetPath& name, const PathsManager* pm );
};

}   // sw

DEFINE_FMT_FORMATTER( sw::LoadPath, "Path: [{}] translated to: [{}]", GetOriginalPath(), GetTranslatedPath() );


namespace sw
{

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline LoadPath::LoadPath		( AssetPath original, AssetPath translated )
	:	m_originalPath( std::move( original ) )
	,	m_translatedPath( std::move( translated ) )
{}

// ================================ //
//
inline LoadPath::LoadPath		( AssetPath original, const PathsManager* pm )
	:	m_originalPath( std::move( original ) )
	,	m_translatedPath( LoadPath::Translate( original, pm ) )
{}

// ================================ //
//
inline LoadPath					LoadPath::operator/			( const filesystem::Path& path ) const
{
	auto newInternalPath = GetInternalPath() / path;
	return LoadPath( AssetPath( GetFileOriginal(), newInternalPath ), AssetPath( GetFileTranslated(), newInternalPath ) );
}

// ================================ //
//
inline std::string				LoadPath::Print				() const
{
	return fmt::format( "{}", *this );
}

// ================================ //
//
inline filesystem::Path			LoadPath::Translate			( const filesystem::Path& path, const PathsManager* pm )
{
	auto translated = pm->Translate( path );

	// @todo If working directory changes this code translates to another path.
	// Is this expected behavior in this case?
	if( translated.IsRelative() )
		translated = filesystem::Path::WorkingDirectory() / translated;

	translated.Normalize();

	return translated;
}

// ================================ //
//
inline AssetPath				LoadPath::Translate			( const AssetPath& name, const PathsManager* pm )
{
	auto systemPath = Translate( name.GetFile(), pm );
	return AssetPath( systemPath, name.GetInternalPath() );
}


}	// sw


