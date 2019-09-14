#pragma once
/**
@file Version.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"

#include <string>


namespace sw
{


/**@brief Standard version structure.

Version follows semantic versioning guidlines:
https://semver.org/

* Major changes when you make incompatibile API changes.
* Minor changes whne functionalities are added with backward compatibility.
* Patch changes when bug fixes are made without changes to API.
* Build is optional number that you can add to identify your builds, releases or whatever you want.

The exception from above rules are versions with Major equal to zero. This means
that library is still in development process, API is unstable and everything can change between version.

*/
struct Version
{
    uint32			Major;
    uint32			Minor;
    uint32			Patch;
    uint32			Build;

    // ================================ //
    //
        /**@brief Contructs Lowest version.*/
    explicit Version    ()
    {
        Major = 0;
        Minor = 1;
        Patch = 0;
        Build = 0;
    }

    // ================================ //
    //
    explicit Version    ( uint32 major, uint32 minor, uint32 patch, uint32 build )
        : Major( major )
        , Minor( minor )
        , Patch( patch )
        , Build( build )
    {}

    /**@brief */
    Version				( const std::string& version )
    {
        std::sscanf( version.c_str(), "%d.%d.%d.%d", &Major, &Minor, &Patch, &Build );
        if( Major < 0 ) Major = 0;
        if( Minor < 0 ) Minor = 0;
        if( Patch < 0 ) Patch = 0;
        if( Build < 0 ) Build = 0;
    }

    /**@brief Creates Version from string.*/
    static Nullable< Version >      From        ( const std::string& versionStr );

    /**@brief Version comparision.*/
    bool                            operator<   ( const Version& other );

    /**@brief Version comparision.*/
    bool                            operator==  ( const Version& other );

    /**@brief Conversts to string.
    String has the same fromat as Version::From function expects as input.*/
    std::string                     ToString     () const;

    /**@brief */
    friend std::ostream& operator<<		( std::ostream& stream, const Version& ver );
};


}	// sw

