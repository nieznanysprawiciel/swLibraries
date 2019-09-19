#include "Version.h"
/**
@file Version.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Version.h"

#include <regex>


namespace sw
{



namespace impl
{
    std::regex		sVersionRegex( "^([[:digit:]]{1,9}).([[:digit:]]{1,9}).([[:digit:]]{1,9}).([[:digit:]]{1,9})$" );
}



/**@brief Creates Version from string.*/
Nullable< Version >         Version::From       ( const std::string& versionStr )
{
    std::smatch match;

    if( std::regex_match( versionStr, match, impl::sVersionRegex ) )
    {
        // If it already matched regex, it should be convertible to uint32.
        return Version( Convert::FromString< uint32 >( match[ 1 ], 0 ),
                        Convert::FromString< uint32 >( match[ 2 ], 0 ),
                        Convert::FromString< uint32 >( match[ 3 ], 0 ),
                        Convert::FromString< uint32 >( match[ 4 ], 0 ) );
    }
    else
    {
        return "Can't convert string [" + versionStr + "] to Version type.";
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
    return  Convert::ToString( Major ) + "." +
            Convert::ToString( Minor ) + "." +
            Convert::ToString( Patch ) + "." +
            Convert::ToString( Build );
}

// ================================ //
//
bool                    Version::operator<      ( const Version& other )
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
bool                    Version::operator==     ( const Version& other )
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
    stream << ver.Major;
    stream << '.';
    stream << ver.Minor;
    stream << '.';
    stream << ver.Patch;
    stream << '.';
    stream << ver.Build;
    return stream;
}

}	// sw


