/**
@file PrototyperUtils.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "PrototyperUtils.h"


namespace sw {
namespace gui
{

// ================================ //
// CoreGUI path should have swGUI in path. We look for this string in binaryPath.
filesystem::Path		FindCoreGUISourcePath			( const filesystem::Path& binaryPath )
{
	auto path = binaryPath;
	auto fileName = path.GetFileName();

	while( !fileName.empty() )
	{
		if( fileName == "swGUI" )
		{
			return path;
		}

		path = path.GetParent();
		fileName = path.GetFileName();
	}

	return filesystem::Path();
}

}	// gui
}	// sw

