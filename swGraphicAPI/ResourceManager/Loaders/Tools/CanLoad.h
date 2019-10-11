#pragma once
/**
@file CanLoad.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <string>
#include <algorithm>

#include "swCommonLib/Common/RTTR.h"
#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"




namespace sw
{

// ================================ //
//
template< size_t N >
bool            CanLoadExtension     ( const AssetPath& filePath, std::string (&allowedExtensions)[ N ] )
{
    // Get extension in lowercase. Note that we deal with multibytes character and something can be wrong with this.
    auto extension = filePath.GetFile().GetExtension();
    std::transform( extension.begin(), extension.end(), extension.begin(), ::tolower );

    if( std::find( std::begin( allowedExtensions ), std::end( allowedExtensions ), extension ) == std::end( allowedExtensions ) )
        return false;

    return true;
}

// ================================ //
//
template< size_t N >
bool            CanLoadType         ( TypeID resourceType, TypeID (&allowedTypes)[ N ] )
{
    if( std::find( std::begin( allowedTypes ), std::end( allowedTypes ), resourceType ) == std::end( allowedTypes ) )
        return false;

    return true;
}

// ================================ //
//
template< size_t N, size_t M >
bool            DefaultCanLoad      ( const AssetPath& filePath, TypeID resourceType, std::string (&allowedExtensions)[ N ], TypeID (&allowedTypes)[ M ] )
{
    if( !CanLoadExtension( filePath, allowedExtensions ) )
        return false;

    if( !CanLoadType( resourceType, allowedTypes ) )
        return false;

    return true;
}


}	// sw

