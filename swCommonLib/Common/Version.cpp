#include "Version.h"
/**
@file Version.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Version.h"

#include "swCommonLib/Common/fmt.h"

#include <regex>


namespace sw
{




/**@brief Creates Version from string.*/
Nullable< Version >         Version::From       ( const std::string& versionStr )
{
    static const std::regex sVersionRegex( "^([[:digit:]]{1,9}).([[:digit:]]{1,9}).([[:digit:]]{1,9}).([[:digit:]]{1,9})$" );

    std::smatch match;

    if( std::regex_match( versionStr, match, sVersionRegex ) )
    {
        // If it already matched regex, it should be convertible to uint32.
        return Version( Convert::FromString< uint32 >( match[ 1 ].str(), 0 ),
                        Convert::FromString< uint32 >( match[ 2 ].str(), 0 ),
                        Convert::FromString< uint32 >( match[ 3 ].str(), 0 ),
                        Convert::FromString< uint32 >( match[ 4 ].str(), 0 ) );
    }
    else
    {
        return fmt::format( "Can't convert string [{}] to Version type.", versionStr );
    }
}

// ================================ //
//
bool                        Version::IsBackwardCompatibileWith  ( const Version& olderVersion ) const
{
    // If one of versions is below zero, we can't count
    // on compatibility between versions if they aren't equal.
    if( olderVersion.Major == 0 ||
        Major == 0 )
    {
        if( olderVersion.Major == Major &&
            olderVersion.Minor == Minor )
            return true;
        return false;
    }

    // Major version change breaks compatibility.
    if( olderVersion.Major != Major )
        return false;

    if( olderVersion.Minor > Minor )
        return false;

    return true;
}

// ================================ //
//
std::string                 Version::ToString   () const
{
    return fmt::format( "{}.{}.{}.{}", Major, Minor, Patch, Build );
}

// ================================ //
//
bool                    Version::operator<      ( const Version& other ) const
{
    if( Major < other.Major )
        return true;
    else if( Major == other.Major )
    {
        if( Minor < other.Minor )
            return true;
        else if( Minor == other.Minor )
        {
            if( Patch < other.Patch )
                return true;
            else if( Build == other.Build && Build < other.Build )
                return true;
        }
    }

    return false;
}

// ================================ //
//
bool                    Version::operator==     ( const Version& other ) const
{
    return Major == other.Major
        && Minor == other.Minor
        && Patch == other.Patch
        && Build == other.Build;
}

// ================================ //
//
std::ostream&           operator<<		        ( std::ostream& stream, const Version& ver )
{
    stream << ver.ToString();
    return stream;
}

}	// sw


