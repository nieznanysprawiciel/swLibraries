#pragma once
/**
@file Version.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Converters.h"

#include <string>


/**@brief Standard version structure.*/
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
        :   Major( major )
        ,   Minor( minor )
        ,   Patch( patch )
        ,   Build( build )
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

	/**@brief Version comparision.*/
	bool operator<		( const Version& other )
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

	/**@brief Version comparision.*/
	bool operator==		( const Version& other )
	{
		return Major == other.Major
			&& Minor == other.Minor
			&& Patch == other.Patch
			&& Build == other.Build;
	}

    std::string            ToString     () const
    {
        return  Convert::ToString( Major ) + "." +
                Convert::ToString( Minor ) + "." +
                Convert::ToString( Patch ) + "." +
                Convert::ToString( Build );
    }

	/**@brief */
	friend std::ostream& operator<<		( std::ostream& stream, const Version& ver )
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
};

